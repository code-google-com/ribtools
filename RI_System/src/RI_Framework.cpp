/*
 *  RI_Framework.cpp
 *  RibTools
 *
 *  Created by Davide Pasca on 08/12/17.
 *  Copyright 2008 Davide Pasca. All rights reserved.
 *
 */

#include "RI_Base.h"
#include "RI_Framework.h"
#include "RI_State.h"

#include <GLUT/glut.h>

//==================================================================
namespace RI
{

//==================================================================
/// Framework
//==================================================================
void Framework::SetOutput( u_int width, u_int height )
{
	glutReshapeWindow( width, height );
}

//==================================================================
void Framework::WorldBegin()
{
	for (size_t i=0; i < mpPrims.size(); ++i)
		delete mpPrims[i];
	mpPrims.clear();
}

//==================================================================
void Framework::Insert(	Primitive			*pPrim,
						const Options		&opt,
						const Attributes	&attr,
						const Transform		&xform,
						const Matrix44		&mtxWorldCamera )
{
	mpPrims.push_back( pPrim );
	
	GState	gstate( opt, attr, xform, mtxWorldCamera );

	pPrim->Render( gstate );
}

//==================================================================
void Framework::WorldEnd()
{
/*
	for (size_t i=0; i < mpPrims.size(); ++i)
	{
	}
*/

	for (size_t i=0; i < mpPrims.size(); ++i)
		delete mpPrims[i];
	mpPrims.clear();
}



//==================================================================
}
