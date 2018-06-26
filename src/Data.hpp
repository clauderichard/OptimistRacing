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

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Algebra.hpp"
#include "ElectricColour.hpp"
#include "Material.hpp"

class GenericData
{
public:
	GenericData() {};
	~GenericData() {};
	// Writes this object to out
	virtual void write( std::ostream &out ) const = 0;
	// Modifies this object with data read from in
	virtual void read( std::istream &in ) = 0;
	// Writes this object to the file filepath
	void writeFile( const std::string filepath ) const;
	// Reads this object from the file filepath
	void readFile( const std::string filepath );
};
std::ostream& operator<< ( std::ostream &out, const GenericData &data );
std::istream& operator>> ( std::istream &in, GenericData &data );

class OldElectricMaterialData : public GenericData
{
public:
	OldElectricMaterialData( std::string filename );
	OldElectricMaterialData();
	~OldElectricMaterialData();
	Material** create8Materials();
	virtual void write( std::ostream &out ) const;
	virtual void read( std::istream &in );
// public members
	double mEmissionOn;
	double mEmissionOff;
	double mAmbientOn;
	double mAmbientOff;
	double mDiffuseOn;
	double mDiffuseOff;
	double mSpecularOn;
	double mSpecularOff;
	double mShininess;
};


class FloorData : public GenericData
{
public:
	// Reads the data from a file
	FloorData( std::string filename );
	FloorData();
	~FloorData();
	void initializeDefault();
	void deleteArrays();
	// Writes this object to out
	virtual void write( std::ostream &out ) const;
	// Modifies this object with data read from in
	virtual void read( std::istream &in );
// Public members
	double					mFloorBezierHX;
	double					mFloorBezierHY;
	int						mFloorBezierNumCellsX;
	int						mFloorBezierNumCellsY;
	MatrixMxN**				mFloorBezierFs; // f, fx, fy, etc.
	E_ELECTRICCOLOUR*		mFloorColours;
};


class FloorRenderData : public GenericData
{
public:
	// Reads the data from a file
	FloorRenderData( std::string filename );
	FloorRenderData();
	~FloorRenderData();
	// Writes this object to out
	virtual void write( std::ostream &out ) const;
	// Modifies this object with data read from in
	virtual void read( std::istream &in );
// Public members
	int						mFloorRenderCellsPerPatchX;
	int						mFloorRenderCellsPerPatchY;
	std::string				mFloorRenderTextureFilename;
	double					mFloorRenderTexturesPerPatchX;
	double					mFloorRenderTexturesPerPatchY;
	OldElectricMaterialData	mFloorMaterial;
};


class LagrangianRacerData : public GenericData
{
public:
	// Reads the data from a file
	LagrangianRacerData( std::string filename );
	LagrangianRacerData();
	~LagrangianRacerData();
	// Writes this object to out
	virtual void write( std::ostream &out ) const;
	// Modifies this object with data read from in
	virtual void read( std::istream &in );
// Public members
	double					mGravity;
	double					mLength;
	double					mHeadRadius;
	double					mBodyRadius;
	double					mBottomRadius;
	double					mHeadMass;
	double					mBodyMass;
	double					mBottomMass;
	double					mXYZDotMax;
	double					mThetaDotMax;
	double					mPhiDotMax;
	double					mStartX;
	double					mStartY;
	double					mStartTheta;
	double					mStartPhi;
	double					mStartXDot;
	double					mStartYDot;
	double					mStartThetaDot;
	double					mStartPhiDot;
	// colour
	E_ELECTRICCOLOUR		mColour;
	// controls
	double					mForceMultiplierRight;
	double					mForceMultiplierUp;
	double					mTorqueMultiplier;
};


class LagrangianRacerRenderData : public GenericData
{
public:
	// Reads the data from a file
	LagrangianRacerRenderData( std::string filename );
	LagrangianRacerRenderData();
	~LagrangianRacerRenderData();
	// Writes this object to out
	virtual void write( std::ostream &out ) const;
	// Modifies this object with data read from in
	virtual void read( std::istream &in );
// Public members
	double					mHatNumTexturesTheta;
	double					mHatNumTexturesZ;
	double					mHeadNumTexturesTheta;
	double					mHeadNumTexturesPhi;
	double					mBodyNumTexturesTheta;
	double					mBodyNumTexturesZ;
	double					mBottomNumTexturesTheta;
	double					mBottomNumTexturesPhi;
	std::string				mHatTextureFilename;
	std::string				mHeadTextureFilename;
	std::string				mBodyTextureFilename;
	std::string				mBottomTextureFilename;
	OldElectricMaterialData	mHatMaterial;
	OldElectricMaterialData	mHeadMaterial;
	OldElectricMaterialData	mBodyMaterial;
	OldElectricMaterialData	mBottomMaterial;
};


class AmbienceRenderData : public GenericData
{
public:
	// Reads the data from a file
	AmbienceRenderData( std::string filename );
	AmbienceRenderData();
	~AmbienceRenderData();
	// Writes this object to out
	virtual void write( std::ostream &out ) const;
	// Modifies this object with data read from in
	virtual void read( std::istream &in );
// Public members
	// Skybox
	double					mSkyboxSize;
	std::string				mSkyboxFilename;
	// Terrain
	std::string				mTerrainTextureFilename;
	double					mTerrainMetersPerImageX;
	double					mTerrainMetersPerImageY;
	double					mTerrainSpeedX;
	double					mTerrainSpeedY;
	double					mTerrainDepth;
};


class ItemData : public GenericData
{
public:
	// Reads the data from a file
	ItemData( std::string filename );
	ItemData();
	~ItemData();
	void initializeDefault();
	void deleteArrays();
	// Writes this object to out
	virtual void write( std::ostream &out ) const;
	// Modifies this object with data read from in
	virtual void read( std::istream &in );
// Public members
	// Painters
	int						mPainterNum;
	Vector3D*				mPainterPositions;
	E_ELECTRICCOLOUR*		mPainterColours;
	double					mPainterRadius;
	// End
	Vector3D				mEndPosition;
	double					mEndRadius;
	// Coins (for challenge)
	int						mCoinNum;
	Vector3D*				mCoinPositions;
	E_ELECTRICCOLOUR*		mCoinColours;
	double					mCoinRadius;
};


class ItemRenderData : public GenericData
{
public:
	// Reads the data from a file
	ItemRenderData( std::string filename );
	ItemRenderData();
	~ItemRenderData();
	// Writes this object to out
	virtual void write( std::ostream &out ) const;
	// Modifies this object with data read from in
	virtual void read( std::istream &in );
// Public members
	// Painters (physics & graphics)
	double					mPainterRadius1;
	double					mPainterRadius2;
	double					mPainterThetaDot;
	OldElectricMaterialData	mPainterMaterial;
	// End (physics & graphics)
	double					mEndRadius1;
	double					mEndRadius2;
	double					mEndThetaDot;
	OldElectricMaterialData	mEndMaterial;
};


class OldWorldData : public GenericData
{
public:
	// Reads the data from a file
	OldWorldData( std::string filename );
	OldWorldData();
	~OldWorldData();
	// Writes this object to out
	virtual void write( std::ostream &out ) const;
	// Modifies this object with data read from in
	virtual void read( std::istream &in );
// Public members
	AmbienceRenderData			mAmbienceRenderData;
	FloorData					mFloorData;
	FloorRenderData				mFloorRenderData;
	ItemData					mItemData;
	ItemRenderData				mItemRenderData;
	LagrangianRacerData			mLagrangianRacerData;
	LagrangianRacerRenderData	mLagrangianRacerRenderData;
};


class ElectricMaterialData
{
public:
	ElectricMaterialData();
	~ElectricMaterialData();
	Material** create8Materials();
// public members
	double mEmissionOn;
	double mEmissionOff;
	double mAmbientOn;
	double mAmbientOff;
	double mDiffuseOn;
	double mDiffuseOff;
	double mSpecularOn;
	double mSpecularOff;
	double mShininess;
};


class UniverseData
{
public:
	UniverseData();
	~UniverseData();
// Public members
	double						mMassHead;
	double						mMassBody;
	double						mMassBottom;
	double						mRadiusHead;
	double						mRadiusBody;
	double						mRadiusBottom;
	double						mRadiusPainter;
	double						mRadiusPainterInner;
	double						mRadiusEnd;
	double						mRadiusEndInner;
	double						mRadiusCoin;
	double						mLengthBody; // bottom to head centers
	double						mXYZDotMax;
	double						mThetaDotMax;
	double						mPhiDotMax;
	double						mForceMultiplierRight;
	double						mForceMultiplierUp;
	double						mTorqueMultiplier;
	std::string					mImageHat;
	std::string					mImageHead;
	std::string					mImageBody;
	std::string					mImageBottom;
	std::vector<std::string>	mNamesWorlds; // includes info on the ordering of worlds.
	ElectricMaterialData*		mMaterialEnd;
	ElectricMaterialData*		mMaterialPainter;
	ElectricMaterialData*		mMaterialCoin;
	ElectricMaterialData*		mMaterialHat;
	ElectricMaterialData*		mMaterialHead;
	ElectricMaterialData*		mMaterialBody;
	ElectricMaterialData*		mMaterialBottom;
	double						mThetaDotPainter;
	double						mThetaDotEnd;
	double						mThetaDotCoin;
	int							mSphereStacks;
	int							mSphereSlices;
	double						mSizeSkybox;
};


class WorldData
{
public:
	WorldData();
	~WorldData();
// Public members
	double						mGravity;
	std::string					mImageSkybox;
	std::string					mImageTerrain;
	std::string					mImageTrack;
	std::string					mImageMenu; // the image representing this world in the menus
	std::string					mImageStory;
	std::string					mTextStory;
	double						mSizeImageTrackX; // number of meters per image
	double						mSizeImageTrackY; // number of meters per image
	double						mSizeTerrainX;
	double						mSizeTerrainY;
	double						mVelocityTerrainX;
	double						mVelocityTerrainY;
	std::string					mMusicNormal;
	std::string					mMusicChallenge;
	std::vector<std::string>	mNamesLevels; // includes info on the ordering of worlds.
	ElectricMaterialData*		mMaterialTrack;
	int							mNumCoinsRequired;
};


class LevelData
{
public:
	LevelData();
	~LevelData();
// Public members
	// Floor
	double							mFloorHeight;
	double							mFloorBezierHX; // cell width x
	double							mFloorBezierHY; // cell width y
	int								mFloorBezierNumCellsX;
	int								mFloorBezierNumCellsY;
	MatrixMxN**						mFloorBezierFs; // f, fx, fy, etc. 3x3 matrices
	E_ELECTRICCOLOUR*				mFloorColours; // row-major
	int								mQuadsPerCellX;
	int								mQuadsPerCellY;
	// Items
	Vector3D						mPositionEnd;
	std::vector<Vector3D>			mPositionsPainters;
	std::vector<Vector3D>			mPositionsCoins;
	std::vector<E_ELECTRICCOLOUR>	mColoursPainters;
	std::vector<E_ELECTRICCOLOUR>	mColoursCoins;
	// Initial racer configuration
	E_ELECTRICCOLOUR				mColourRacer;
	double							mStartX;
	double							mStartY;
	double							mStartTheta;
	double							mStartPhi;
	double							mStartXDot;
	double							mStartYDot;
	double							mStartThetaDot;
	double							mStartPhiDot;
};


class ProgressRequirementsData
{

public:
	/// Warning: in here we load every world and every level (only the data from the lua files)
	ProgressRequirementsData( UniverseData* univ );
	~ProgressRequirementsData();

// public members
	/// number of worlds
	int mNumWorlds;
	/// number of levels in each world
	int* mNumLevelsPerWorld;
	/// number of coins in each level
	int** mNumCoinsPerLevel;
	/// total number of coins required to unlock a world in challenge-mode
	int* mWorldPrices;
	/// total number of levels in the universe
	int mNumLevelsInUniverse;
	/// total number of coins in the universe
	int mNumCoinsInUniverse;
};


class SaveData
{

public:
	SaveData( const ProgressRequirementsData* reqData );
	~SaveData();

	void completeLevel( int world, int level );
	void catchCoins( int world, int level, int n );
	
// public members
	const ProgressRequirementsData* mProgressRequirementsData;
	
	// To include in the save file
	/// Last world that was completed in story
	int		mLastWorldCompleted;
	/// Last level (in last world completed) that was completed in story
	int		mLastLevelCompleted;
	/// Number of coins caught in each level of the universe
	int**	mNumCoinsCaught;

	// derived from the stuff above
	bool	mStoryCompleted;
	bool*	mChallengeWorldUnlocked;
	int		mNumCoinsCaughtTotal;
	bool	mChallengeCompleted;

};