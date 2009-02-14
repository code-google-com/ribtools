/*
 *  RI_HiderREYES.cpp
 *  RibTools
 *
 *  Created by Davide Pasca on 09/02/08.
 *  Copyright 2009 Davide Pasca. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>
#include "RI_Primitive.h"
#include "RI_HiderREYES.h"

//==================================================================
namespace RI
{

//==================================================================
/// HiderREYES
//==================================================================
HiderREYES::HiderREYES()
{
}

//==================================================================
HiderREYES::~HiderREYES()
{
}

//==================================================================
void HiderREYES::WorldBegin(
					const Options &opt,
					const Matrix44 &mtxWorldCamera )
{
	for (size_t i=0; i < mpPrims.size(); ++i)
		delete mpPrims[i];
	mpPrims.clear();

	mOptions = opt;

	mMtxWorldCamera	= mtxWorldCamera;
	mMtxCameraProj	= opt.mMtxViewHomo;
	
	mDestBuff.Setup( opt.mXRes, opt.mYRes );
	mDestBuff.Clear();
}

//==================================================================
void HiderREYES::Insert(
			Primitive			*pPrim,
			const Attributes	&attr,
			const Transform		&xform )
{
	mpPrims.push_back( pPrim );
}

//==================================================================
void HiderREYES::InsertSplitted(	
					Primitive	*pSplitPrim,
					Primitive	&srcPrim
					)
{
	pSplitPrim->CopyStates( srcPrim );

	mpPrims.push_back( pSplitPrim );
}

//==================================================================
void HiderREYES::Remove( Primitive *pPrim )
{
}

//==================================================================
void HiderREYES::WorldEnd()
{
	for (size_t i=0; i < mpPrims.size(); ++i)
		delete mpPrims[i];

	mpPrims.clear();
}

//==================================================================
float HiderREYES::RasterEstimate( const Bound &b ) const
{
	if NOT( b.IsValid() )
	{
		return 10 * 10;
	}

	Vector3	boxVerts[8]=
	{
		Vector3( b.mBox[0].x, b.mBox[0].y, b.mBox[0].z ),
		Vector3( b.mBox[1].x, b.mBox[0].y, b.mBox[0].z ),
		Vector3( b.mBox[0].x, b.mBox[1].y, b.mBox[0].z ),
		Vector3( b.mBox[1].x, b.mBox[1].y, b.mBox[0].z ),
		Vector3( b.mBox[0].x, b.mBox[0].y, b.mBox[1].z ),
		Vector3( b.mBox[1].x, b.mBox[0].y, b.mBox[1].z ),
		Vector3( b.mBox[0].x, b.mBox[1].y, b.mBox[1].z ),
		Vector3( b.mBox[1].x, b.mBox[1].y, b.mBox[1].z ),
	};

	float destHalfWd	= (float)mDestBuff.mWd * 0.5f;
	float destHalfHe	= (float)mDestBuff.mHe * 0.5f;

	float minX =  FLT_MAX;
	float minY =  FLT_MAX;
	float maxX = -FLT_MAX;
	float maxY = -FLT_MAX;

	for (size_t i=0; i < 8; ++i)
	{
		Vector4	Pproj = boxVerts[i] * mMtxCameraProj;
		
		float	oow = 1.0f / Pproj.w;

		float	winX = destHalfWd + destHalfWd * Pproj.x * oow;
		float	winY = destHalfHe - destHalfHe * Pproj.y * oow;
		
		minX = DMIN( minX, winX );
		minY = DMIN( minY, winY );
		maxX = DMAX( maxX, winX );
		maxY = DMAX( maxY, winY );
	}
	
	float	squareArea = (maxY - minY) * (maxX - minX);

	return squareArea;
}

//==================================================================
void HiderREYES::pointsTo2D( Point2 *pDes, const Point3 *pSrc, u_int n )
{
	float destHalfWd	= (float)mDestBuff.mWd * 0.5f;
	float destHalfHe	= (float)mDestBuff.mHe * 0.5f;

	for (size_t i=0; i < n; ++i)
	{
		Vector4	Pproj = pSrc[i] * mMtxCameraProj;
		
		float	oow = 1.0f / Pproj.w;
		
		pDes[i].Set( 
				destHalfWd + destHalfWd * Pproj.x * oow,
				destHalfHe - destHalfHe * Pproj.y * oow
				);
	}
}

//==================================================================
void HiderREYES::Hide( MicroPolygonGrid &g )
{
	float du = 1.0f / g.mXDim;
	float dv = 1.0f / g.mYDim;
	
	float destHalfWd	= (float)mDestBuff.mWd * 0.5f;
	float destHalfHe	= (float)mDestBuff.mHe * 0.5f;

	const Point3	*pRuns = g.mpPoints;

	for (u_int iv=0; iv < g.mYDim; ++iv)
	{
		float	v = iv * dv;
		
		for (u_int iu=0; iu < g.mXDim; ++iu)
		{
			float	u = iu * du;
			
			Vector4	Pproj = *pRuns++ * mMtxCameraProj;
			
			float	oow = 1.0f / Pproj.w;

			int	winX = (int)(destHalfWd + destHalfWd * Pproj.x * oow);
			int	winY = (int)(destHalfHe - destHalfHe * Pproj.y * oow);

			float	destCol[3] =
			{
				u,
				v,
				0
			};

			mDestBuff.SetSample( winX, winY, destCol );
		}
	}

}

//==================================================================
}