//==================================================================
/// RSLC_Defs_OpConvert.h
///
/// Created by Davide Pasca - 2009/7/16
/// See the file "license.txt" that comes with this project for
/// copyright info. 
//==================================================================

#ifndef RSLC_DEFS_OPCONVERT_H
#define RSLC_DEFS_OPCONVERT_H

//==================================================================
namespace RSLC
{

//==================================================================
struct BiOpConvertRule 
{
	TokenID	mOper;
	VarType	mResType;
	VarType	mLType;
	VarType	mRType;
};

//==================================================================
BiOpConvertRule	_gBiOpConvertRules[] =
{
	T_OP_ASSIGN		,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_ASSIGN		,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_ASSIGN		,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_ASSIGN		,	VT_FLOAT	,	VT_FLOAT	,	VT_FLOAT	,
	T_OP_ASSIGN		,	VT_MATRIX	,	VT_MATRIX	,	VT_MATRIX	,


	T_OP_PLUSASS	,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_PLUSASS	,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_PLUSASS	,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_PLUSASS	,	VT_COLOR	,	VT_COLOR	,	VT_FLOAT	,
	T_OP_PLUSASS	,	VT_FLOAT	,	VT_FLOAT	,	VT_FLOAT	,
	T_OP_PLUSASS	,	VT_MATRIX	,	VT_MATRIX	,	VT_MATRIX	,
	T_OP_PLUSASS	,	VT_MATRIX	,	VT_MATRIX	,	VT_FLOAT	,

	T_OP_PLUS		,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_PLUS		,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_PLUS		,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_PLUS		,	VT_COLOR	,	VT_COLOR	,	VT_FLOAT	,
	T_OP_PLUS		,	VT_FLOAT	,	VT_FLOAT	,	VT_FLOAT	,
	T_OP_PLUS		,	VT_MATRIX	,	VT_MATRIX	,	VT_MATRIX	,
	T_OP_PLUS		,	VT_MATRIX	,	VT_MATRIX	,	VT_FLOAT	,

	T_OP_MINUSASS	,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_MINUSASS	,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_MINUSASS	,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_MINUSASS	,	VT_COLOR	,	VT_COLOR	,	VT_FLOAT	,
	T_OP_MINUSASS	,	VT_FLOAT	,	VT_FLOAT	,	VT_FLOAT	,
	T_OP_MINUSASS	,	VT_MATRIX	,	VT_MATRIX	,	VT_MATRIX	,
	T_OP_MINUSASS	,	VT_MATRIX	,	VT_MATRIX	,	VT_FLOAT	,

	T_OP_MINUS		,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_MINUS		,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_MINUS		,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_MINUS		,	VT_COLOR	,	VT_COLOR	,	VT_FLOAT	,
	T_OP_MINUS		,	VT_FLOAT	,	VT_FLOAT	,	VT_FLOAT	,
	T_OP_MINUS		,	VT_MATRIX	,	VT_MATRIX	,	VT_MATRIX	,
	T_OP_MINUS		,	VT_MATRIX	,	VT_MATRIX	,	VT_FLOAT	,


	T_OP_MULASS		,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_MULASS		,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_MULASS		,	VT_COLOR	,	VT_COLOR	,	VT_FLOAT	,
	T_OP_MULASS		,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_MULASS		,	VT_MATRIX	,	VT_MATRIX	,	VT_FLOAT	,
	T_OP_MULASS		,	VT_MATRIX	,	VT_MATRIX	,	VT_VECTOR	,

	T_OP_MUL		,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_MUL		,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_MUL		,	VT_COLOR	,	VT_COLOR	,	VT_FLOAT	,
	T_OP_MUL		,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_MUL		,	VT_MATRIX	,	VT_MATRIX	,	VT_FLOAT	,
	T_OP_MUL		,	VT_MATRIX	,	VT_MATRIX	,	VT_VECTOR	,


	T_OP_DIVASS		,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_DIVASS		,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_DIVASS		,	VT_FLOAT	,	VT_FLOAT	,	VT_FLOAT	,
	T_OP_DIVASS		,	VT_COLOR	,	VT_COLOR	,	VT_FLOAT	,
	T_OP_DIVASS		,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_DIVASS		,	VT_MATRIX	,	VT_MATRIX	,	VT_FLOAT	,
//	T_OP_DIVASS		,	VT_MATRIX	,	VT_MATRIX	,	VT_VECTOR	,

	T_OP_DIV		,	VT_VECTOR	,	VT_VECTOR	,	VT_FLOAT	,
	T_OP_DIV		,	VT_VECTOR	,	VT_VECTOR	,	VT_VECTOR	,
	T_OP_DIV		,	VT_FLOAT	,	VT_FLOAT	,	VT_FLOAT	,
	T_OP_DIV		,	VT_COLOR	,	VT_COLOR	,	VT_FLOAT	,
	T_OP_DIV		,	VT_COLOR	,	VT_COLOR	,	VT_COLOR	,
	T_OP_DIV		,	VT_MATRIX	,	VT_MATRIX	,	VT_FLOAT	,
//	T_OP_DIV		,	VT_MATRIX	,	VT_MATRIX	,	VT_VECTOR	,

	T_OP_DOT		,	VT_FLOAT,	VT_VECTOR,	VT_VECTOR,

	T_OP_LOGIC_AND	,	VT_BOOL,	VT_BOOL,	VT_BOOL,
	T_OP_LOGIC_OR	,	VT_BOOL,	VT_BOOL,	VT_BOOL,
};

//==================================================================
}

#endif
