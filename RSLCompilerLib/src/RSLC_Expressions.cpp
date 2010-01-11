//==================================================================
/// RSLC_Expressions.cpp
///
/// Created by Davide Pasca - 2009/11/1
/// See the file "license.txt" that comes with this project for
/// copyright info. 
//==================================================================

#include "RSLC_Tree.h"
#include "RSLC_Exceptions.h"
#include "RSLC_Operators.h"
#include "RSLC_Expressions.h"

//==================================================================
namespace RSLC
{

/*
About varying ...

	// strings are always uniform !!!
	DASSERT( pOperand1->IsVarying() == false );
	DASSERT( pOperand2->IsVarying() == false );

	
	// is this an assignment ?
	if ( pNode->mpToken->IsAssignOp() )
	{
		// ..are we dealing with varying data at all ?
		if ( opResIsVarying )
		{
			Variable	*pOp1Var = pOperand1->mVarLink.GetVarPtr();

			// is the destination not varying ?
			if NOT( pOp1Var->IsVarying() )
			{
				if ( pOp1Var->IsForcedDetail() )
				{
					// this is the end of it..
					throw Exception( "Cannot assign a varying variable to an 'uniform' destination", pNode );
				}
				else
				{
					pOp1Var->SetVarying( opResIsVarying );
				}
			}
		}			
	}
*/

//==================================================================
static void solveExpressions_sub_BiOp( TokNode *pNode, const DVec<Function> &funcs )
{
	TokNode *pOperands[2];
	VarType	vtypes[2] = { VT_UNKNOWN, VT_UNKNOWN };

	for (size_t opIdx=0; opIdx < 2; ++opIdx)
	{
		for (pOperands[opIdx] = pNode->GetChildTry( opIdx );
				true;
			pOperands[opIdx] = pOperands[opIdx]->GetChildTry( 0 ))
		{
			if NOT( pOperands[opIdx] )
				throw Exception( "Unknown operand", pNode );

			VarType	vtype = pOperands[opIdx]->GetVarType();
			if ( vtype != VT_UNKNOWN )
			{
				vtypes[opIdx] = vtype;
				break;
			}
		}
	}

	VarType	opResVarType;

	SolveBiOpType(	pNode,
					vtypes[0],
					vtypes[1],
					opResVarType );

	if ( !pNode->mpToken->IsAssignOp() && pNode->mpToken->idType != T_TYPE_VALUE )
	{
		// if it's not an assignment nor an immediate value
		AddSelfVariable( pNode, opResVarType, false, false );
	}
}

//==================================================================
static void solveExpressions_sub( TokNode *pNode, const DVec<Function> &funcs )
{
	for (size_t i=0; i < pNode->mpChilds.size(); ++i)
		solveExpressions_sub( pNode->mpChilds[i], funcs );

	if NOT( pNode->mpToken )
		return;

	if ( pNode->mNodeType == TokNode::TYPE_FUNCCALL )
	{
		const Function	*pFunc = MatchFunctionByParams( pNode, funcs );

		if ( pFunc )
		{
			pNode->mFuncCall.mpFunc = pFunc;
		}
	}
	else
	if ( pNode->mpToken->IsBiOp() )
	{
		solveExpressions_sub_BiOp( pNode, funcs );
	}
}

//==================================================================
void SolveExpressions( TokNode *pRoot, bool processShaderOnly )
{
	const DVec<Function> &funcs = pRoot->GetFuncs();

	if ( processShaderOnly )
	{
		for (size_t i=0; i < funcs.size(); ++i)
		{
			const Function	&func = funcs[i];

			// pre-pass ?
			if ( processShaderOnly )
				if NOT( func.IsShader() )
					continue;

			if ( func.mpParamsNode )
				solveExpressions_sub( func.mpParamsNode, funcs );
			else
				solveExpressions_sub( func.mpCodeBlkNode, funcs );
		}
	}
	else
	{
		solveExpressions_sub( pRoot, funcs );
	}
}

//==================================================================
static bool isBranchVarying( TokNode *pNode )
{
	for (size_t i=0; i < pNode->mpChilds.size(); ++i)
		if ( isBranchVarying( pNode->mpChilds[i] ) )
			return true;

	return pNode->IsVarying();
}

//==================================================================
static void solveVariablesDetail_sub( TokNode *pNode )
{
	for (size_t i=0; i < pNode->mpChilds.size(); ++i)
		solveVariablesDetail_sub( pNode->mpChilds[i] );

	if ( pNode->mpToken->IsBiOp() )
	{
		TokNode	*pLNode	= pNode->GetChildTry( 0 );
		TokNode	*pRNode	= pNode->GetChildTry( 1 );

		bool rIsVarying = isBranchVarying( pRNode );

		if ( pNode->mpToken->IsAssignOp() )
		{
			/*
			=		// assignment operators don't have corresponding virtual destinations (variables)
				L
				R

			- Try to propagate R detail to L and '='
			- If R is varying, then L must be..
			*/

			bool lSetSuccess = pLNode->TrySetVarying_AndForceIfTrue( rIsVarying );

			// cannot make L varying ? that's an error
			// (..otherwise it is fine.. e.g. left is forced varying and right is uniform..)
			if ( !lSetSuccess && rIsVarying )
			{				
				throw Exception( "l-value must be varying in this expression.", pLNode );
			}
		}
		else
		{
			/*
			+		// non-assignment operators have a virtual destination (variable)
				L
				R

			- Try to propagate R and L detail '+'
			  (if L and R are uniform, set to uniform, otherwise to varying)
			*/

			bool lIsVarying = isBranchVarying( pLNode );

			bool opSetSuccess;

			if ( !lIsVarying && !rIsVarying )
			{
				// both operands are uniform.. so we try to make the '+' uniform as well
				opSetSuccess = pNode->TrySetVarying_AndForceIfTrue( false );
			}
			else
			{
				// if either is varying, then so must be the operator
				opSetSuccess = pNode->TrySetVarying_AndForceIfTrue( true );

			}

			// should always succeed, because an operator is a virtual variable
			// generated by the previous passes.. and it's not forced to any specific
			// detail setting
			DASSERT( opSetSuccess );
		}
	}
}

//==================================================================
void SolveVariablesDetail( TokNode *pRoot )
{
	const DVec<Function> &funcs = pRoot->GetFuncs();

	for (size_t i=0; i < funcs.size(); ++i)
	{
		const Function	&func = funcs[i];

		if NOT( func.IsShader() )
			continue;

		if ( func.mpParamsNode )
			solveVariablesDetail_sub( func.mpParamsNode );
		else
			solveVariablesDetail_sub( func.mpCodeBlkNode );
	}
}

//==================================================================
}
