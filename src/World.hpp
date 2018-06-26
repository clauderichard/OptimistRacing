/*	Copyright (C) 2012  Claude Richard
 *
 *	Optimist Racing is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Optimist Racing is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Optimist Racing.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Data.hpp"
#include "Primitive.hpp"
#include "Camera.hpp"
#include "WorldEngine.hpp"
#include "Lagrange.hpp"


enum E_RACINGSTATE {
	RACINGSTATE_RACING,
	RACINGSTATE_FLYING,
	RACINGSTATE_HEADSMASH,
	RACINGSTATE_NUM
};


class World
{
public:
	World( const UniverseData* univ, const WorldData* wor, const LevelData* lev );
	~World();
	void setForceRight( int force );
	void setForceUp( int force );
	void step( double seconds );
	void reset();
	void glRender() const;
	// Returns true if you finished the level
	bool getFinished() const;
private:
	//   Every pointer member is created by constructor.
	//     So destroy every pointer member in the destructor.
	// Engine stuff
	//   floor
	BernsteinPolynomial*		mBernsteinPolynomial;
	BezierPatchGrid*			mBezierPatchGrid;
	Grid2D<E_ELECTRICCOLOUR>*	mFloorColours;
	//   racer parameters including start
	LagrangianRacer*			mInitialLagrangianRacer;
	LagrangianRacer*			mLagrangianRacer;
	double						mBottomRadius;
	double						mHeadRadius;
	E_ELECTRICCOLOUR			mInitialRacerColour;
	E_ELECTRICCOLOUR			mRacerColour;
	E_RACINGSTATE				mRacerState;
	//   items
	int							mNumPainters;
	Vector3D*					mPainterPositions;
	E_ELECTRICCOLOUR*			mPainterColours;
	double						mPainterRadius;
	Vector3D					mEndPosition;
	double						mEndRadius;
	double						mPainterAngularSpeed;
	double						mEndAngularSpeed;
	double						mPainterAngle;
	double						mEndAngle;
	double						mWaterLevel;
	//   force (can change each frame)
	int							mForceRight;
	int							mForceUp;
	double						mForceMultiplierRight;
	double						mForceMultiplierUp;
	double						mTorqueMultiplier;
	// Camera
	Camera*						mCamera;
	// Textures
	Texture*					mTextureHat;
	Texture*					mTextureHead;
	Texture*					mTextureBody;
	Texture*					mTextureBottom;
	Texture*					mTextureFloor;
	Texture*					mTextureSky;
	Texture*					mTextureTerrain;
	// Materials
	Material**					mFloorMaterials;
	Material**					mHatMaterials;
	Material**					mHeadMaterials;
	Material**					mBodyMaterials;
	Material**					mBottomMaterials;
	Material**					mPainterMaterials;
	Material**					mEndMaterials;
	// Primitives
	ImmobilePrimitive*			mHatPrimitive;
	ImmobilePrimitive*			mHeadPrimitive;
	ImmobilePrimitive*			mBodyPrimitive;
	ImmobilePrimitive*			mBottomPrimitive;
	ImmobilePrimitive*			mSkyPrimitive;
	MobilePrimitive*			mTerrainPrimitive;
	ImmobilePrimitive**			mPainterPrimitives;
	ImmobilePrimitive*			mEndPrimitive;
	TrackFloorRenderer*			mFloorPrimitive;
	// RacerRenderer
	RacerRenderer*				mRacerRenderer;
	// Finished the level
	bool						mFinished;
};