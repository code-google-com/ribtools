/*
 *  RI_HiderBase.h
 *  RibTools
 *
 *  Created by Davide Pasca on 09/02/08.
 *  Copyright 2009 Davide Pasca. All rights reserved.
 *
 */

#ifndef RI_HIDERBASE_H
#define RI_HIDERBASE_H

#include "RI_Base.h"
#include "DMath.h"
#include "RI_MicroPolygonGrid.h"

//==================================================================
namespace RI
{

class Options;
class Attributes;
class Transform;
class Primitive;

//==================================================================
/// HiderBase
//==================================================================
class HiderBase
{
public:
	Matrix44	mMtxWorldCamera;
	Matrix44	mMtxCameraProj;
	float		mHalfXRes;
	float		mHalfYRes;

public:
	HiderBase()				{}
	virtual ~HiderBase()	{}

	virtual void WorldBegin(
					const Options &opt,
					const Matrix44 &mtxWorldCamera
				) = 0;

	virtual void Insert(
				Primitive			*pPrim,
				 const Attributes	&attr,
				 const Transform	&xform ) = 0;

	virtual void InsertSplitted(	
						Primitive			*pSplitPrim,
						Primitive			&srcPrim
						) = 0;

	virtual void Remove( Primitive *pPrim ) = 0;

	virtual void WorldEnd() = 0;
	
	virtual float RasterEstimate( const Bound &b ) const = 0;

	virtual void Hide( MicroPolygonGrid &g ) = 0;
	
	virtual u_int		GetOutputDataWd() const = 0;
	virtual u_int		GetOutputDataHe() const = 0;
	virtual const float *GetOutputData() const = 0;

	virtual DVec<Primitive *>	&GetPrimList() = 0;
};

//==================================================================
}

#endif