//==================================================================
/// RSLC_Exceptions.h
///
/// Created by Davide Pasca - 2009/5/27
/// See the file "license.txt" that comes with this project for
/// copyright info. 
//==================================================================

#ifndef RSLC_EXCEPTIONS_H
#define RSLC_EXCEPTIONS_H

#include <string>

//==================================================================
namespace RSLC
{

//==================================================================
class Token;
class TokNode;
class FatBase;
class Fat8;

//==================================================================
class Exception
{
	std::string	mMsg;

public:
	Exception( const std::string &msg, const Token *pTok=NULL );
	Exception( const std::string &msg, const TokNode *pTokNode );
	Exception( const TokNode *pTokNode, const char *pFmt, ... );

	Exception( const FatBase &fatBase, const Fat8 &ch, const char *pFmt, ...  );

	~Exception()
	{
	}

	const std::string &GetMessage() const	{	return mMsg;	}
};

//==================================================================
void Warning( const TokNode *pTokNode, const char *pFmt, ... );

//==================================================================
}

#endif