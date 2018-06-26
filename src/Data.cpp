/*	Copyright (C) 2012  Claude Richard
 *
 *	Optimist Racing is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	CLaM-Physics is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Optimist Racing.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Data.hpp"
#include <fstream>
#include <iostream>
#include <direct.h>
#include "FileLocator.hpp"


// GenericData
void GenericData::writeFile( const std::string filepath ) const
{
	// Open the file.
	std::ofstream openfile;
	openfile.open( filepath.c_str() );
	if ( ! openfile.is_open() )
	{
		std::string ff = filepath;
		std::string err = "Could not open file for writing: " + ff;
		std::cerr << err.c_str();
		throw -1;
	}
	// Write to the file
	openfile << (*this) << std::endl;
	// Close the file.
	openfile.close();
}
void GenericData::readFile( const std::string filepath )
{
	// Open the file
	std::ifstream openfile(filepath.c_str(), std::ios::in );
	if ( ! openfile.is_open() )
	{
		std::string ff = filepath;
		std::string err = "Could not open file for reading: " + ff;
		std::cerr << err.c_str();
		throw -1;
	}
	// Read from the file
	openfile >> (*this);
	// Close the file.
	openfile.close();
}
std::ostream& operator<< ( std::ostream &out, const GenericData &data )
{
	data.write(out);
	return out;
}
std::istream& operator>> ( std::istream &in, GenericData &data )
{
	data.read(in);
	return in;
}


// MaterialData
OldElectricMaterialData::OldElectricMaterialData( std::string filename )
{
	readFile( filename );
}
OldElectricMaterialData::OldElectricMaterialData()
{
	mEmissionOn = 1;
	mEmissionOff = 0;
	mAmbientOn = 1;
	mAmbientOff = 0;
	mDiffuseOn = 1;
	mDiffuseOff = 0;
	mSpecularOn = 1;
	mSpecularOff = 0;
	mShininess = 0;
}
OldElectricMaterialData::~OldElectricMaterialData()
{
}
Material** OldElectricMaterialData::create8Materials()
{
	Material** ret = new Material*[ELECTRICCOLOUR_NUM];
	ret[ELECTRICCOLOUR_BLACK] = new Material( Colour(mEmissionOff,mEmissionOff,mEmissionOff),
											  Colour(mAmbientOff,mAmbientOff,mAmbientOff),
											  Colour(mDiffuseOff,mDiffuseOff,mDiffuseOff),
											  Colour(mSpecularOff,mSpecularOff,mSpecularOff),
											  mShininess );
	ret[ELECTRICCOLOUR_RED] = new Material( Colour(mEmissionOn,mEmissionOff,mEmissionOff),
											Colour(mAmbientOn,mAmbientOff,mAmbientOff),
											Colour(mDiffuseOn,mDiffuseOff,mDiffuseOff),
											Colour(mSpecularOn,mSpecularOff,mSpecularOff),
											mShininess );
	ret[ELECTRICCOLOUR_GREEN] = new Material( Colour(mEmissionOff,mEmissionOn,mEmissionOff),
											  Colour(mAmbientOff,mAmbientOn,mAmbientOff),
											  Colour(mDiffuseOff,mDiffuseOn,mDiffuseOff),
											  Colour(mSpecularOff,mSpecularOn,mSpecularOff),
											  mShininess );
	ret[ELECTRICCOLOUR_BLUE] = new Material( Colour(mEmissionOff,mEmissionOff,mEmissionOn),
											 Colour(mAmbientOff,mAmbientOff,mAmbientOn),
											 Colour(mDiffuseOff,mDiffuseOff,mDiffuseOn),
											 Colour(mSpecularOff,mSpecularOff,mSpecularOn),
											 mShininess );
	ret[ELECTRICCOLOUR_YELLOW] = new Material( Colour(mEmissionOn,mEmissionOn,mEmissionOff),
											   Colour(mAmbientOn,mAmbientOn,mAmbientOff),
											   Colour(mDiffuseOn,mDiffuseOn,mDiffuseOff),
											   Colour(mSpecularOn,mSpecularOn,mSpecularOff),
											   mShininess );
	ret[ELECTRICCOLOUR_MAGENTA] = new Material( Colour(mEmissionOn,mEmissionOff,mEmissionOn),
												Colour(mAmbientOn,mAmbientOff,mAmbientOn),
												Colour(mDiffuseOn,mDiffuseOff,mDiffuseOn),
												Colour(mSpecularOn,mSpecularOff,mSpecularOn),
												mShininess );
	ret[ELECTRICCOLOUR_CYAN] = new Material( Colour(mEmissionOff,mEmissionOn,mEmissionOn),
											 Colour(mAmbientOff,mAmbientOn,mAmbientOn),
											 Colour(mDiffuseOff,mDiffuseOn,mDiffuseOn),
											 Colour(mSpecularOff,mSpecularOn,mSpecularOn),
											 mShininess );
	ret[ELECTRICCOLOUR_WHITE] = new Material( Colour(mEmissionOn,mEmissionOn,mEmissionOn),
											  Colour(mAmbientOn,mAmbientOn,mAmbientOn),
											  Colour(mDiffuseOn,mDiffuseOn,mDiffuseOn),
											  Colour(mSpecularOn,mSpecularOn,mSpecularOn),
											  mShininess );
	return ret;
}
void OldElectricMaterialData::write( std::ostream &out ) const
{
	out << mEmissionOn << " " << mEmissionOff << " " << mAmbientOn << " " << mAmbientOff << " " <<
		mDiffuseOn << " " << mDiffuseOff << " " << mSpecularOn << " " << mSpecularOff << " " << mShininess;
}
void OldElectricMaterialData::read( std::istream &in )
{
	in >> mEmissionOn >> mEmissionOff >> mAmbientOn >> mAmbientOff >>
		mDiffuseOn >> mDiffuseOff >> mSpecularOn >> mSpecularOff >> mShininess;
}


// FloorData
// Reads the data from a file
FloorData::FloorData( std::string filename )
{
	initializeDefault();
	readFile( filename );
}
FloorData::FloorData()
{
	initializeDefault();
}
FloorData::~FloorData()
{
	deleteArrays();
}
void FloorData::initializeDefault()
{
	mFloorBezierHX = 1;
	mFloorBezierHY = 1;
	mFloorBezierNumCellsX = 1;
	mFloorBezierNumCellsY = 1;
	mFloorBezierFs = new MatrixMxN*[4];
	mFloorBezierFs[0] = new MatrixMxN(3,3);
	mFloorBezierFs[1] = new MatrixMxN(3,3);
	mFloorBezierFs[2] = new MatrixMxN(3,3);
	mFloorBezierFs[3] = new MatrixMxN(3,3);
	mFloorColours = new E_ELECTRICCOLOUR[1];
	mFloorColours[0] = ELECTRICCOLOUR_WHITE;
}
void FloorData::deleteArrays()
{
	double Fsize = (mFloorBezierNumCellsX+1)*(mFloorBezierNumCellsY+1);
	for(int i=0; i<Fsize; i++) {
		delete mFloorBezierFs[i];
	}
	delete[] mFloorBezierFs;
	delete[] mFloorColours;
}
void FloorData::write( std::ostream &out ) const
{
	out << mFloorBezierHX << " " << mFloorBezierHY << " " <<
		  mFloorBezierNumCellsX << " " << mFloorBezierNumCellsY << " ";
	int numMatrices = (mFloorBezierNumCellsX+1)*(mFloorBezierNumCellsY+1);
	int numCells = mFloorBezierNumCellsX*mFloorBezierNumCellsY;
	for (int i=0; i<numMatrices; i++) {
		for (int j=0; j<3; j++) {
			for (int k=0; k<3; k++) {
				out << mFloorBezierFs[i][j][k] << " ";
			}
		}
	}
	for (int i=0; i<numCells; i++) {
		out << mFloorColours[i];
		if ( i != numCells-1 ) out << " ";
	}
}
void FloorData::read( std::istream &in )
{
	deleteArrays();
	in >> mFloorBezierHX >> mFloorBezierHY >>
		  mFloorBezierNumCellsX >> mFloorBezierNumCellsY;
	int numMatrices = (mFloorBezierNumCellsX+1)*(mFloorBezierNumCellsY+1);
	int numCells = mFloorBezierNumCellsX*mFloorBezierNumCellsY;
	mFloorBezierFs = new MatrixMxN*[numMatrices];
	mFloorColours = new E_ELECTRICCOLOUR[numCells];
	double d[9];
	for (int i=0; i<numMatrices; i++) {
		for (int j=0; j<9; j++) {
			in >> d[j];
		}
		mFloorBezierFs[i] = new MatrixMxN(3,3,d);
	}
	for (int i=0; i<numCells; i++) {
		in >> mFloorColours[i];
	}
}

// FloorRenderData
FloorRenderData::FloorRenderData( std::string filename )
{
	readFile( filename );
}
FloorRenderData::FloorRenderData()
{
}
FloorRenderData::~FloorRenderData()
{
}
void FloorRenderData::write( std::ostream &out ) const
{
	out << mFloorRenderCellsPerPatchX << " " << mFloorRenderCellsPerPatchY << " " << mFloorRenderTextureFilename << " " <<
		   mFloorRenderTexturesPerPatchX << " " << mFloorRenderTexturesPerPatchY << " " << mFloorMaterial;
}
void FloorRenderData::read( std::istream &in )
{
	in >> mFloorRenderCellsPerPatchX >> mFloorRenderCellsPerPatchY >> mFloorRenderTextureFilename >>
		  mFloorRenderTexturesPerPatchX >> mFloorRenderTexturesPerPatchY >> mFloorMaterial;
}

// LagrangianRacerData
LagrangianRacerData::LagrangianRacerData( std::string filename )
{
	readFile( filename );
}
LagrangianRacerData::LagrangianRacerData()
{
	mGravity = 1;
	mLength = 1;
	mHeadRadius = 1;
	mBodyRadius = 1;
	mBottomRadius = 1;
	mHeadMass = 1;
	mBodyMass = 1;
	mBottomMass = 1;
	mXYZDotMax = 1;
	mThetaDotMax = 1;
	mPhiDotMax = 1;
	mStartX = 0;
	mStartY = 0;
	mStartTheta = 0;
	mStartPhi = 0;
	mStartXDot = 0;
	mStartYDot = 0;
	mStartThetaDot = 0;
	mStartPhiDot = 0;
	mColour = ELECTRICCOLOUR_WHITE;
	mForceMultiplierRight = 1;
	mForceMultiplierUp = 1;
	mTorqueMultiplier = 1;
}
LagrangianRacerData::~LagrangianRacerData()
{
}
void LagrangianRacerData::write( std::ostream &out ) const
{
	out << mGravity << " " << mLength << " " << mHeadRadius << " " << mBodyRadius << " " << mBottomRadius << " " <<
			mHeadMass << " " << mBodyMass << " " << mBottomMass << " " <<
			mXYZDotMax << " " << mThetaDotMax << " " << mPhiDotMax << " " <<
			mStartX << " " << mStartY << " " << mStartTheta << " " << mStartPhi << " " <<
			mStartXDot << " " << mStartYDot << " " << mStartThetaDot << " " << mStartPhiDot << " " <<
			mColour << " " << mForceMultiplierRight << " " << mForceMultiplierUp << " " << mTorqueMultiplier;
}
void LagrangianRacerData::read( std::istream &in )
{
	in >> mGravity >> mLength >> mHeadRadius >> mBodyRadius >> mBottomRadius >>
			mHeadMass >> mBodyMass >> mBottomMass >>
			mXYZDotMax >> mThetaDotMax >> mPhiDotMax >>
			mStartX >> mStartY >> mStartTheta >> mStartPhi >>
			mStartXDot >> mStartYDot >> mStartThetaDot >> mStartPhiDot >>
			mColour >> mForceMultiplierRight >> mForceMultiplierUp >> mTorqueMultiplier;
}


// LagrangianRacerRenderData
LagrangianRacerRenderData::LagrangianRacerRenderData( std::string filename )
{
	readFile( filename );
}
LagrangianRacerRenderData::LagrangianRacerRenderData()
{
	mHatNumTexturesTheta = 0;
	mHatNumTexturesZ = 0;
	mHeadNumTexturesTheta = 0;
	mHeadNumTexturesPhi = 0;
	mBodyNumTexturesTheta = 0;
	mBodyNumTexturesZ = 0;
	mBottomNumTexturesTheta = 0;
	mBottomNumTexturesPhi = 0;
	mHatTextureFilename = "hattex.txt";
	mHeadTextureFilename = "headtex.txt";
	mBodyTextureFilename = "bodytex.txt";
	mBottomTextureFilename = "bottomtex.txt";
}
LagrangianRacerRenderData::~LagrangianRacerRenderData()
{
}
void LagrangianRacerRenderData::write( std::ostream &out ) const
{
	out << mHatNumTexturesTheta << " " << mHatNumTexturesZ << " " <<
		   mHeadNumTexturesTheta << " " << mHeadNumTexturesPhi << " " <<
		   mBodyNumTexturesTheta << " " << mBodyNumTexturesZ << " " <<
		   mBottomNumTexturesTheta << " " << mBottomNumTexturesPhi << " " <<
		   mHatTextureFilename << " " << mHeadTextureFilename << " " <<
		   mBodyTextureFilename << " " << mBottomTextureFilename << " " <<
		   mHatMaterial << " " << mHeadMaterial << " " << mBodyMaterial << " " << mBottomMaterial;
}
void LagrangianRacerRenderData::read( std::istream &in )
{
	in >> mHatNumTexturesTheta >> mHatNumTexturesZ >>
		  mHeadNumTexturesTheta >> mHeadNumTexturesPhi >>
		  mBodyNumTexturesTheta >> mBodyNumTexturesZ >>
		  mBottomNumTexturesTheta >> mBottomNumTexturesPhi >>
		  mHatTextureFilename >> mHeadTextureFilename >>
		  mBodyTextureFilename >> mBottomTextureFilename >>
		  mHatMaterial >> mHeadMaterial >> mBodyMaterial >> mBottomMaterial;
}


// AmbienceRenderData
AmbienceRenderData::AmbienceRenderData( std::string filename )
{
	readFile( filename );
}
	AmbienceRenderData::AmbienceRenderData()
	{

	}
AmbienceRenderData::~AmbienceRenderData()
{
}
void AmbienceRenderData::write( std::ostream &out ) const
{
	out << mSkyboxSize << " " <<
			mSkyboxFilename << " " << mTerrainTextureFilename << " " <<
			mTerrainMetersPerImageX << " " << mTerrainMetersPerImageY << " " <<
			mTerrainSpeedX << " " << mTerrainSpeedY << " " <<
			mTerrainDepth;
}
void AmbienceRenderData::read( std::istream &in )
{
	in >> mSkyboxSize >> mSkyboxFilename >>
		  mTerrainTextureFilename >>
	      mTerrainMetersPerImageX >> mTerrainMetersPerImageY >>
		  mTerrainSpeedX >> mTerrainSpeedY >>
		  mTerrainDepth;
}


// ItemData
ItemData::ItemData( std::string filename )
{
	initializeDefault();
	readFile( filename );
}
ItemData::ItemData()
{
	initializeDefault();
}
ItemData::~ItemData()
{
	deleteArrays();
}
void ItemData::initializeDefault()
{
	mPainterNum = 1;
	mPainterPositions = new Vector3D[mPainterNum];
	mPainterColours = new E_ELECTRICCOLOUR[mPainterNum];
	mPainterColours[0] = ELECTRICCOLOUR_WHITE;
	mPainterRadius = 1;
	mEndPosition = Vector3D(0,0,0);
	mEndRadius = 1;
}
void ItemData::deleteArrays()
{
	delete[] mPainterPositions;
	delete[] mPainterColours;
}
void ItemData::write( std::ostream &out ) const
{
	out << mPainterNum << " ";
	for (int i=0; i<mPainterNum; i++) {
		out << mPainterPositions[i][0] << " " << mPainterPositions[i][1] << " " << mPainterPositions[i][2] << " " <<
				mPainterColours[i] << " ";
	}
	out << mPainterRadius << " " <<
			mEndPosition[0] << " " << mEndPosition[1] << " " << mEndPosition[2] << " " << mEndRadius;
}
void ItemData::read( std::istream &in )
{
	deleteArrays();
	in >> mPainterNum;
	mPainterPositions = new Vector3D[mPainterNum];
	mPainterColours = new E_ELECTRICCOLOUR[mPainterNum];
	double x;
	double y;
	double z;
	for (int i=0; i<mPainterNum; i++) {
		in >> x >> y >> z;
		mPainterPositions[i] = Vector3D(x,y,z);
		in >> mPainterColours[i];
	}
	in >> mPainterRadius >> x >> y >> z >> mEndRadius;
	mEndPosition = Vector3D(x,y,z);
}


// ItemRenderData
ItemRenderData::ItemRenderData( std::string filename )
{
	readFile( filename );
}
ItemRenderData::ItemRenderData()
{
	mPainterRadius1 = 1;
	mPainterRadius2 = 1;
	mPainterThetaDot = 1;
	mEndRadius1 = 1;
	mEndRadius2 = 1;
	mEndThetaDot = 1;
}
ItemRenderData::~ItemRenderData()
{
}
void ItemRenderData::write( std::ostream &out ) const
{
	out << mPainterRadius1 << " " << mPainterRadius2 << " " << mPainterThetaDot << " " << mPainterMaterial << " " <<
			mEndRadius1 << " " << mEndRadius2 << " " << mEndThetaDot << " " << mEndMaterial;
}
void ItemRenderData::read( std::istream &in )
{
	in >> mPainterRadius1 >> mPainterRadius2 >> mPainterThetaDot >> mPainterMaterial >>
			mEndRadius1 >> mEndRadius2 >> mEndThetaDot >> mEndMaterial;
}


// OldWorldData
OldWorldData::OldWorldData( std::string filename )
{
	readFile( filename );
}
OldWorldData::OldWorldData()
{
}
OldWorldData::~OldWorldData()
{
}
void OldWorldData::write( std::ostream &out ) const
{
	out << mAmbienceRenderData << " " <<
		   mFloorData << " " << mFloorRenderData << " " <<
		   mItemData << " " << mItemRenderData << " " <<
		   mLagrangianRacerData << " " << mLagrangianRacerRenderData;

}
void OldWorldData::read( std::istream &in )
{
	in >> mAmbienceRenderData >>
		  mFloorData >> mFloorRenderData >>
		  mItemData >> mItemRenderData >>
		  mLagrangianRacerData >> mLagrangianRacerRenderData;
}



UniverseData::UniverseData()
{
}

UniverseData::~UniverseData()
{
}

WorldData::WorldData()
{
}

WorldData::~WorldData()
{
}

LevelData::LevelData()
{
	mFloorBezierFs = NULL;
	mFloorColours = NULL;
}

LevelData::~LevelData()
{
	if ( mFloorBezierFs != NULL ) {
		for (int i=0; i<(mFloorBezierNumCellsX+1)*(mFloorBezierNumCellsY+1); i++) {
			delete mFloorBezierFs[i];
		}
		delete[] mFloorBezierFs;
	}
	if ( mFloorColours != NULL ) delete[] mFloorColours;
}

ElectricMaterialData::ElectricMaterialData()
{
}

ElectricMaterialData::~ElectricMaterialData()
{
}

Material** ElectricMaterialData::create8Materials()
{
	Material** ret = new Material*[ELECTRICCOLOUR_NUM];
	ret[ELECTRICCOLOUR_BLACK] = new Material( Colour(mEmissionOff,mEmissionOff,mEmissionOff),
											  Colour(mAmbientOff,mAmbientOff,mAmbientOff),
											  Colour(mDiffuseOff,mDiffuseOff,mDiffuseOff),
											  Colour(mSpecularOff,mSpecularOff,mSpecularOff),
											  mShininess );
	ret[ELECTRICCOLOUR_RED] = new Material( Colour(mEmissionOn,mEmissionOff,mEmissionOff),
											Colour(mAmbientOn,mAmbientOff,mAmbientOff),
											Colour(mDiffuseOn,mDiffuseOff,mDiffuseOff),
											Colour(mSpecularOn,mSpecularOff,mSpecularOff),
											mShininess );
	ret[ELECTRICCOLOUR_GREEN] = new Material( Colour(mEmissionOff,mEmissionOn,mEmissionOff),
											  Colour(mAmbientOff,mAmbientOn,mAmbientOff),
											  Colour(mDiffuseOff,mDiffuseOn,mDiffuseOff),
											  Colour(mSpecularOff,mSpecularOn,mSpecularOff),
											  mShininess );
	ret[ELECTRICCOLOUR_BLUE] = new Material( Colour(mEmissionOff,mEmissionOff,mEmissionOn),
											 Colour(mAmbientOff,mAmbientOff,mAmbientOn),
											 Colour(mDiffuseOff,mDiffuseOff,mDiffuseOn),
											 Colour(mSpecularOff,mSpecularOff,mSpecularOn),
											 mShininess );
	ret[ELECTRICCOLOUR_YELLOW] = new Material( Colour(mEmissionOn,mEmissionOn,mEmissionOff),
											   Colour(mAmbientOn,mAmbientOn,mAmbientOff),
											   Colour(mDiffuseOn,mDiffuseOn,mDiffuseOff),
											   Colour(mSpecularOn,mSpecularOn,mSpecularOff),
											   mShininess );
	ret[ELECTRICCOLOUR_MAGENTA] = new Material( Colour(mEmissionOn,mEmissionOff,mEmissionOn),
												Colour(mAmbientOn,mAmbientOff,mAmbientOn),
												Colour(mDiffuseOn,mDiffuseOff,mDiffuseOn),
												Colour(mSpecularOn,mSpecularOff,mSpecularOn),
												mShininess );
	ret[ELECTRICCOLOUR_CYAN] = new Material( Colour(mEmissionOff,mEmissionOn,mEmissionOn),
											 Colour(mAmbientOff,mAmbientOn,mAmbientOn),
											 Colour(mDiffuseOff,mDiffuseOn,mDiffuseOn),
											 Colour(mSpecularOff,mSpecularOn,mSpecularOn),
											 mShininess );
	ret[ELECTRICCOLOUR_WHITE] = new Material( Colour(mEmissionOn,mEmissionOn,mEmissionOn),
											  Colour(mAmbientOn,mAmbientOn,mAmbientOn),
											  Colour(mDiffuseOn,mDiffuseOn,mDiffuseOn),
											  Colour(mSpecularOn,mSpecularOn,mSpecularOn),
											  mShininess );
	return ret;
}


ProgressRequirementsData::ProgressRequirementsData( UniverseData* univ )
{
	mNumWorlds = univ->mNamesWorlds.size();
	mNumLevelsPerWorld = new int[ mNumWorlds ];
	mNumCoinsPerLevel = new int*[ mNumWorlds ];
	mWorldPrices = new int[ mNumWorlds ];
	mNumLevelsInUniverse = 0;
	mNumCoinsInUniverse = 0;

	int iWorld = 0;
	for (std::vector<std::string>::const_iterator it=univ->mNamesWorlds.begin(); it!=univ->mNamesWorlds.end(); it++) {
		WorldData* wor = loadWorldData( *it );
		mNumLevelsPerWorld[ iWorld ] = wor->mNamesLevels.size();
		mNumLevelsInUniverse += mNumLevelsPerWorld[ iWorld ];
		mNumCoinsPerLevel[ iWorld ] = new int[ mNumLevelsPerWorld[ iWorld ] ];
		mWorldPrices[ iWorld ] = wor->mNumCoinsRequired;
		int iLevel = 0;
		for (std::vector<std::string>::const_iterator it=wor->mNamesLevels.begin(); it!=wor->mNamesLevels.end(); it++) {
			LevelData* lev = loadLevelData( *it );
			mNumCoinsPerLevel[ iWorld ][ iLevel ] = lev->mPositionsCoins.size();
			mNumCoinsInUniverse += mNumCoinsPerLevel[ iWorld ][ iLevel ];
			iLevel ++;
			delete lev;
		}
		delete wor;
		iWorld ++;
	}
}

ProgressRequirementsData::~ProgressRequirementsData()
{
	delete mNumLevelsPerWorld;
	delete mNumCoinsPerLevel;
	delete mWorldPrices;
}


SaveData::SaveData( const ProgressRequirementsData* reqData )
	: mProgressRequirementsData( reqData )
{
	mLastWorldCompleted = 0;
	mLastLevelCompleted = 0;
	mStoryCompleted = false;
	mNumCoinsCaught = new int*[ reqData->mNumWorlds ];
	mNumCoinsCaughtTotal = 0;
	mChallengeCompleted = false;
	mChallengeWorldUnlocked = new bool[ reqData->mNumWorlds ];
	for (int i=0; i<reqData->mNumWorlds; i++) {
		mNumCoinsCaught[ i ] = new int[ reqData->mNumLevelsPerWorld[ i ] ];
		for (int j=0; j<reqData->mNumLevelsPerWorld[i]; j++) {
			mNumCoinsCaught[ i ][ j ] = 0;
		}
		mChallengeWorldUnlocked[i] = false;
	}
}

SaveData::~SaveData()
{
	for (int i=0; i<mProgressRequirementsData->mNumWorlds; i++) {
		delete mNumCoinsCaught[ i ];
	}
	delete mNumCoinsCaught;
	delete mChallengeWorldUnlocked;
}

void SaveData::completeLevel( int world, int level )
{
	if ( world>=mLastWorldCompleted && level>=mLastLevelCompleted ) {
		mLastWorldCompleted = world;
		mLastLevelCompleted = level;
		// complete the story if applicable
		if ( mLastWorldCompleted == mProgressRequirementsData->mNumWorlds-1 &&
			mLastLevelCompleted == mProgressRequirementsData->mNumLevelsPerWorld[mLastWorldCompleted]-1 ) {
			mStoryCompleted = true;
		}
	}
}

void SaveData::catchCoins( int world, int level, int n )
{
	if ( mNumCoinsCaught[world][level] <= n ) {
		mNumCoinsCaughtTotal += n - mNumCoinsCaught[world][level];
		mNumCoinsCaught[world][level] = n;
		// unlock worlds
		for (int i=0; i<mProgressRequirementsData->mNumWorlds; i++) {
			if ( mNumCoinsCaughtTotal >= mProgressRequirementsData->mWorldPrices[i] ) {
				mChallengeWorldUnlocked[i] = true;
			}
		}
		// complete challenge if applicable
		if ( mNumCoinsCaughtTotal == mProgressRequirementsData->mNumCoinsInUniverse ) {
			mChallengeCompleted = true;
		}
	}
}
