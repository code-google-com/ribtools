//==================================================================
/// RI_Render.h
///
/// Created by Davide Pasca - 2009/8/1
/// See the file "license.txt" that comes with this project for
/// copyright info. 
//==================================================================

#ifndef RI_RENDER_H
#define RI_RENDER_H

#include "DSystem/include/DUtils.h"
#include "DSystem/include/DUtils_FileManager.h"

//==================================================================
namespace RI
{

//==================================================================
class Machine;

//==================================================================
/// Render
//==================================================================
class Render
{

public:
	Render(
		const char			*pFileName,
		Machine				&machine,
		DUT::FileManager	&fileManager,
		bool				verbose=false );
};

//==================================================================
}

#endif
