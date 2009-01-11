/*
 *  RI_Base.cpp
 *  ribparser
 *
 *  Created by Davide Pasca on 08/12/17.
 *  Copyright 2008 Davide Pasca. All rights reserved.
 *
 */

#include "RI_Base.h"

//==================================================================
namespace RI
{
	
//==================================================================
const char *ErrorToString( Error errCode )
{
	switch ( errCode )
	{
	case E_OK				:	return "E_OK";
	case E_NESTING			:	return "E_NESTING";
	case E_NOTOPTIONS		:	return "E_NOTOPTION";
	case E_NOTATTRIBS		:	return "E_NOTATTRIB";
	case E_NOTPRIMS			:	return "E_NOTPRIMS";
	case E_NOTSTARTED		:	return "E_NOTSTARTE";
	case E_ILLSTATE			:	return "E_ILLSTATE";
	case E_ARRAYTOOBIG		:	return "insufﬁcient memory to construct array";
	case E_BADARGUMENT		:	return "incorrect parameter value";
	case E_BADARRAY			:	return "invalid array speciﬁcation";
	case E_BADBASIS			:	return "undeﬁned basis matrix name";
	case E_BADCOLOR			:	return "invalid color speciﬁcation";
	case E_BADHANDLE		:	return "invalid light or object handle";
	case E_BADPARAMLIST		:	return "parameter list type mismatch";
	case E_BADRIPCODE		:	return "invalid encoded RIB request code";
	case E_BADSTRINGTOKEN	:	return "undeﬁned encoded string token";
	case E_BADTOKEN			:	return "invalid binary token";
	case E_BADVERSION		:	return "protocol version number mismatch";
	case E_LIMITCHECK		:	return "overﬂowing an internal limit";
	case E_OUTOFMEMORY		:	return "generic instance of insufﬁcient memory";
	case E_PROTOCOLBOTCH	:	return "malformed binary encoding";
	case E_STRINGTOOBIG		:	return "insufﬁcient memory to read string";
	case E_SYNTAXERROR		:	return "general syntactic error";
	case E_UNREGISTERED		:	return "undeﬁned RIB request";
	default					:	return "Unknown error !!!";
	}
}

//==================================================================
}