/*
 *  DContainers.h
 *  ribparser
 *
 *  Created by Davide Pasca on 08/12/17.
 *  Copyright 2008 Davide Pasca. All rights reserved.
 *
 */

#ifndef DCONTAINERS_H
#define DCONTAINERS_H

#include "DTypes.h"
#include "DUtils.h"

//==================================================================
static const size_t	NPOS = (size_t)-1;

#if 0
//==================================================================
template <class T>
class DVec
{
	T		*mpData;
	size_t	mSize;
	size_t	mSizeAlloc;
	
public:
	DVec() :
		mpData(NULL),
		mSize(0),
		mSizeAlloc(0)
	{
	}

	DVec( const DVec &from )
	{
		copyFrom( from );
	}
	
	virtual ~DVec()
	{
		freeAll();
	}
	
	const DVec& operator=(const DVec& rhs)
	{
		freeAll();
		copyFrom( rhs );
		return *this;
	}

private:
	void copyFrom( const DVec& from )
	{
		mSize		= from.mSize;
		mSizeAlloc	= from.mSize;
		
		mpData = (T *)new u_char [ sizeof(T) * mSizeAlloc ];

		for (size_t i=0; i < mSize; ++i)
			mpData[i] = from.mpData[i];
	}
	
	void freeAll()
	{
		clear();
		mSizeAlloc = 0;
		if ( mpData )
			delete [] (u_char *)mpData;
		mpData = NULL;
	}

public:
	size_t size() const { return mSize; }

	void clear()
	{
		resize( 0 );
	}

	void resize( size_t newSize )
	{
		if ( newSize == mSize )
			return;
		
		if ( newSize > mSizeAlloc )
		{
			size_t newSizeAlloc = mSizeAlloc * 2;
			if ( newSizeAlloc < newSize )
				newSizeAlloc = newSize;

			T *newPData = (T *)new u_char [ sizeof(T) * newSizeAlloc ];
			
			if ( mpData )
			{
				memcpy( newPData, mpData, mSize * sizeof(T) );

				delete [] (u_char *)mpData;
			}
			
			mpData = newPData;
			mSizeAlloc = newSizeAlloc;
		}
		
		if ( newSize < mSize )
		{
			for (size_t i=newSize; i < mSize; ++i)
				mpData[i].~T();
		}
		else
		{
			for (size_t i=mSize; i < newSize; ++i)
				new (&mpData[i]) T();
		}
		
		mSize = newSize;
		
	}

	T *grow( size_t n=1 )
	{
		size_t	fromIdx = this->size();
		this->resize( fromIdx + n );
		return &(*this)[fromIdx];
	}
	
	void push_back( const T &val )
	{
		T *pDest = grow();
		*pDest = val;
	}

	void pop_back()
	{
		DASSERT( mSize >= 1 );
		resize( mSize - 1 );
	}

	const	T &back() const { DASSERT( mSize >= 1 ); return mpData[mSize-1]; }
			T &back()		{ DASSERT( mSize >= 1 ); return mpData[mSize-1]; }

	const T &operator[]( size_t idx ) const { DASSERT( idx < mSize ); return mpData[ idx ]; }
		  T &operator[]( size_t idx )		{ DASSERT( idx < mSize ); return mpData[ idx ]; }
};
#else
//==================================================================
template<class T>
class DVec : public std::vector<T>
{
public:
	T *grow( size_t n=1 )
	{
		size_t	fromIdx = this->size();
		this->resize( fromIdx + n );
		return &(*this)[fromIdx];
	}
};
#endif

//==================================================================
template <class T>
class Stack
{
	DVec<T>	mVec;

public:
	void push( const T &val )
	{
		mVec.push_back( val );
	}
	
	void pop()
	{
		mVec.pop_back();
	}
	
	const T &top() const
	{
		return mVec.back();
	}

	T &top()
	{
		return mVec.back();
	}
	
	void clear()
	{
		mVec.clear();
	}
};

//==================================================================
template <class T>
class CopyStack
{
	DVec<T>	mVec;

public:
	CopyStack()
	{
		mVec.resize(1);
	}
	void push()
	{
		mVec.push_back( top() );
	}
	
	void pop()
	{
		mVec.pop_back();
	}
	
	const T &top() const
	{
		return mVec.back();
	}

	T &top()
	{
		return mVec.back();
	}

	void clear()
	{
		mVec.clear();
	}
};

//==================================================================
template <class T, size_t MAX>
class CopyStackMax
{
	U8		mVec[ sizeof(T) * MAX ];
	size_t	mSize;

public:
	CopyStackMax()
	{
		T	*p = (T *)&mVec[0];
		new ( p ) T;
		mSize = 1;
	}

	void push()
	{
		DASSTHROW( mSize < MAX, ("Out of bounds !") );

		*(T *)&mVec[mSize * sizeof(T)] = top();
		
		mSize += 1;
	}
	
	void pop()
	{
		DASSTHROW( mSize >= 0, ("Out of bounds !") );
		mSize -= 1;
	}

	const T &top() const
	{
		return *(const T *)&mVec[(mSize-1) * sizeof(T)];
	}

	T &top()
	{
		return *(T *)&mVec[(mSize-1) * sizeof(T)];
	}
	
	void clear()
	{
		for (size_t i=0; i < mSize; ++i)
			mVec[i].~T();

		mSize = 0;
	}
};

#endif