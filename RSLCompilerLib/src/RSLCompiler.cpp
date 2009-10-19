//==================================================================
/// RSLCompiler.cpp
///
/// Created by Davide Pasca - 2009/5/21
/// See the file "license.txt" that comes with this project for
/// copyright info.
//==================================================================

#include <time.h>
#include "DSystem/include/DSafeCrt.h"
#include "DSystem/include/DUtils.h"
#include "DSystem/include/DContainers.h"
#include "DSystem/include/DUtils_Files.h"
#include "RSLC_Token.h"
#include "RSLC_Tree.h"
#include "RSLC_Variables.h"
#include "RSLC_Functions.h"
#include "RSLC_Operators.h"
#include "RSLC_Registers.h"
#include "RSLC_Builtins.h"
#include "RSLC_Constants.h"
#include "RSLCompiler.h"

//==================================================================
using namespace	RSLC;

//==================================================================
const char	*RSLCompiler::mpsVersionString = "0.2a";

//==================================================================
RSLCompiler::RSLCompiler(
		const char *pSource,
		size_t sourceSize,
		const char *pBaseInclude,
		const Params &params )
{
	DVec<U8>	sourceInc;

	if NOT( DUT::GrabFile( pBaseInclude, sourceInc ) )
	{
		std::string	msg = DUT::SSPrintFS( "Failed to open %s", pBaseInclude );
		throw Exception( msg );
	}

	sourceInc.append_array( (const U8 *)pSource, sourceSize );

	Tokenizer( mTokens, (const char *)&sourceInc[0], sourceInc.size() );

#if 0	// useful to debug the tokenizer
	for (size_t i=0; i < mTokens.size(); ++i)
	{
		printf( "%3i) %i - %-12s - %s\n",
				i,
				mTokens[i].isPrecededByWS,
				GetTokenTypeStr( mTokens[i].idType ),
				mTokens[i].str.c_str() );
	}
#endif

	mpRoot = DNEW TokNode( (Token *)NULL );

	// make the basic tree with nested blocks based on brackets
	MakeTree( mpRoot, mTokens );

	// discover variables declarations
	DiscoverVariablesDeclarations( mpRoot );

	// discover functions declarations and usage
	DiscoverFunctions( mpRoot );

	// remove closing brackets as they serve no additional purpose
	// ..since the tree has already been defined at this point
	RemoveClosingBrackets( mpRoot );

	// discover if, while, solar, etc..
	DiscoverFuncopsUsage( mpRoot );

	// remove semicolons as they serve no additional purpose
	RemoveSemicolons( mpRoot );

	// develop the tree based on operators with the proper precedence
	ReparentOperators( mpRoot );

	// reparent the funcops (e.g. the statement becomes a childen in cases as
	// "solar(expr) stmt"
	ReparentFuncopsStatements( mpRoot );

	// discover variables usage
	DiscoverVariablesUsage( mpRoot );

	RealizeConstants( mpRoot );

	SolveExpressions( mpRoot, false, false );

	ResolveFunctionCalls( mpRoot );

	SolveExpressions( mpRoot, true, true );

	AssignRegisters( mpRoot, 0 );

	MarkUsedGlobals( mpRoot );

	// produce some debug info in the output file
	if ( params.mDbgOutputTree )
		TraverseTree( mpRoot, 0 );
}

//==================================================================
RSLCompiler::~RSLCompiler()
{
	DSAFE_DELETE( mpRoot );
}

//==================================================================
void RSLCompiler::SaveASM( const char *pFName, const char *pRefSourceName )
{
	FILE	*pFile;

	if ( fopen_s( &pFile, pFName, "wb" ) )
	{
		DASSTHROW( 0, ("Failed to save %s", pFName) );
	}

	char dateStr[256];
	char timeStr[256];
	numstrdate( dateStr);
	_strtime_s( timeStr );

	fprintf_s( pFile, ";==========================================================\n" );
	fprintf_s( pFile, ";= %s\n", pFName );
	fprintf_s( pFile, ";= Source file %s\n", pRefSourceName );
	fprintf_s( pFile, ";= Creation date %s - %s\n", dateStr, timeStr );
	fprintf_s( pFile, ";= File automatically generated by RSLCompilerCmd %s\n", mpsVersionString );
	fprintf_s( pFile, ";=========================================================\n\n" );

	fprintf_s( pFile, "\n.data\n" );

	WriteVariables( pFile, mpRoot );

	fprintf_s( pFile, "\n.code\n" );

	WriteFunctions( pFile, mpRoot );

	fclose( pFile );
}
