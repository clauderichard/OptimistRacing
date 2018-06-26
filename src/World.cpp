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

#include "World.hpp"
#include "Globals.hpp"
#include "Algebra.hpp"
#include "Collision.hpp"
using namespace Lagrange;

World::World( const UniverseData* univ, const WorldData* wor, const LevelData* lev )
{
	// Floor
	mBernsteinPolynomial = new BernsteinPolynomial( 5 );
	mBezierPatchGrid = new BezierPatchGrid( mBernsteinPolynomial,
		lev->mFloorBezierHX, lev->mFloorBezierHY,
		lev->mFloorBezierNumCellsX, lev->mFloorBezierNumCellsY,
		lev->mFloorBezierFs );
	mFloorColours = new Grid2D<E_ELECTRICCOLOUR>( 0, 0, lev->mFloorBezierNumCellsX, lev->mFloorBezierNumCellsY,
		lev->mFloorBezierHX, lev->mFloorBezierHY, lev->mFloorColours );

	// Racer including start
	double topmass = univ->mMassHead + univ->mMassBody;
	double ibottomz = 2 * univ->mMassBottom * univ->mRadiusBottom * univ->mRadiusBottom / 3;
	double iheadxyz = 2 * univ->mMassHead * univ->mRadiusHead * univ->mRadiusHead / 3;
	double ibodyz = univ->mMassBody * univ->mRadiusBody * univ->mRadiusBody;
	double ibodyxy = univ->mMassBody *
		( 3 * univ->mRadiusBody * univ->mRadiusBody +
			 univ->mLengthBody * univ->mLengthBody );
	double m1plusm2 = univ->mMassBody + univ->mMassHead;
	double l1 = univ->mLengthBody * univ->mMassHead / 2 / m1plusm2;
	double l2 = univ->mLengthBody * univ->mMassBody / 2 / m1plusm2;
	double itopxy = ibodyxy + univ->mMassBody*l1*l1 + iheadxyz + univ->mMassHead*l2*l2;
	double itopz = ibodyz + iheadxyz;
	mInitialLagrangianRacer = new LagrangianRacer( mBezierPatchGrid, wor->mGravity, univ->mLengthBody,
		univ->mMassBottom, topmass, ibottomz, itopxy, itopxy, itopz,
		univ->mXYZDotMax, univ->mXYZDotMax, univ->mXYZDotMax, univ->mThetaDotMax, univ->mPhiDotMax,
		lev->mStartX, lev->mStartY, lev->mStartTheta, lev->mStartPhi,
		lev->mStartXDot, lev->mStartYDot, lev->mStartThetaDot, lev->mStartPhiDot );
	mLagrangianRacer = new LagrangianRacer( *mInitialLagrangianRacer );
	mBottomRadius = univ->mRadiusBottom;
	mHeadRadius = univ->mRadiusHead;
	mInitialRacerColour = lev->mColourRacer;
	mRacerColour = mInitialRacerColour;
	mRacerState = RACINGSTATE_RACING;
	// Items
	mNumPainters = lev->mPositionsPainters.size();
	mPainterPositions = new Vector3D[ mNumPainters ];
	mPainterColours = new E_ELECTRICCOLOUR[ mNumPainters ];
	for (int i=0; i<mNumPainters; i++) {
		mPainterPositions[i] = lev->mPositionsPainters[i];
		mPainterColours[i] = lev->mColoursPainters[i];
	}
	mPainterRadius = univ->mRadiusPainter;
	mEndPosition = lev->mPositionEnd;
	mEndRadius = univ->mRadiusEnd;
	mPainterAngularSpeed = univ->mThetaDotPainter;
	mEndAngularSpeed = univ->mThetaDotEnd;
	mPainterAngle = 0;
	mEndAngle = 0;
	mWaterLevel = 0;
	// Force
	mForceRight = 0;
	mForceUp = 0;
	mForceMultiplierRight = univ->mForceMultiplierRight;
	mForceMultiplierUp = univ->mForceMultiplierUp;
	mTorqueMultiplier = univ->mTorqueMultiplier;
	// Camera
	mCamera = new RacerCamera( mLagrangianRacer, 0.7, 0.9, 1.5, 0.0, 0.0 );
	// Textures
	Image img;
	img.readPngFile( "images/" + univ->mImageHat + ".png" );
	mTextureHat = new Texture( &img, true );
	img.readPngFile( "images/" + univ->mImageHead + ".png" );
	mTextureHead = new Texture( &img, true );
	img.readPngFile( "images/" + univ->mImageBody + ".png" );
	mTextureBody = new Texture( &img, true );
	img.readPngFile( "images/" + univ->mImageBottom + ".png" );
	mTextureBottom = new Texture( &img, true );
	img.readPngFile( "images/" + wor->mImageTrack + ".png" );
	mTextureFloor = new Texture( &img, true );
	img.readPngFile( "images/" + wor->mImageSkybox + ".png" );
	mTextureSky = new Texture( &img, true );
	img.readPngFile( "images/" + wor->mImageTerrain + ".png" );
	mTextureTerrain = new Texture( &img, true );
	// Materials
	mFloorMaterials = wor->mMaterialTrack->create8Materials();
	mHatMaterials = univ->mMaterialHat->create8Materials();
	mHeadMaterials = univ->mMaterialHead->create8Materials();
	mBodyMaterials = univ->mMaterialBody->create8Materials();
	mBottomMaterials = univ->mMaterialBottom->create8Materials();
	mPainterMaterials = univ->mMaterialPainter->create8Materials();
	mEndMaterials = univ->mMaterialEnd->create8Materials();
	// Primitives
	mHatPrimitive = new ConeTextured( mHeadRadius, mHeadRadius*3, 0, univ->mSphereSlices, univ->mSphereStacks, mTextureHat, 1, 1 );
	mHeadPrimitive = new SphereTextured( mHeadRadius, univ->mSphereSlices, univ->mSphereStacks, mTextureHead, 1, 1 );
	mBodyPrimitive = new CylinderTextured( univ->mRadiusBody, univ->mLengthBody, 40, mTextureBody, 1, 1 );
	mBottomPrimitive = new SphereTextured( univ->mRadiusBottom, univ->mSphereSlices, univ->mSphereStacks, mTextureBottom, 1, 1 );
	mSkyPrimitive = new Skybox( mTextureSky, univ->mSizeSkybox, 0 );
	mTerrainPrimitive = new Terrain( mTextureTerrain, univ->mSizeSkybox, 0,
		wor->mSizeTerrainX, wor->mSizeTerrainY,
		wor->mVelocityTerrainX, wor->mVelocityTerrainY );
	mPainterPrimitives = new ImmobilePrimitive*[ ELECTRICCOLOUR_NUM ];
	for (int i=0; i<ELECTRICCOLOUR_NUM; i++) {
		mPainterPrimitives[i] = new Tetrahedron2( univ->mRadiusPainter, univ->mRadiusPainterInner,
			mPainterMaterials[i], mPainterMaterials[i], mPainterMaterials[i], mPainterMaterials[i] );
	}
	mEndPrimitive = new Octahedron2( univ->mRadiusEndInner, univ->mRadiusEnd,
		mEndMaterials[ELECTRICCOLOUR_WHITE], mEndMaterials[ELECTRICCOLOUR_RED],
		mEndMaterials[ELECTRICCOLOUR_MAGENTA], mEndMaterials[ELECTRICCOLOUR_BLUE],
		mEndMaterials[ELECTRICCOLOUR_CYAN], mEndMaterials[ELECTRICCOLOUR_GREEN],
		mEndMaterials[ELECTRICCOLOUR_YELLOW], mEndMaterials[ELECTRICCOLOUR_BLACK] );
	mFloorPrimitive = new TrackFloorRenderer( mBezierPatchGrid, mFloorColours,
		lev->mQuadsPerCellX, lev->mQuadsPerCellY,
		mFloorMaterials, mTextureFloor, lev->mFloorBezierHX/wor->mSizeImageTrackX, lev->mFloorBezierHY/wor->mSizeImageTrackY );
	// RacerRenderer
	mRacerRenderer = new RacerRenderer( mLagrangianRacer, mHeadPrimitive, mBottomPrimitive, mBodyPrimitive, mHatPrimitive );
	mFinished = false;
}
World::~World()
{
	// floor
	delete mBernsteinPolynomial;
	delete mBezierPatchGrid;
	delete mFloorColours;
	// racer parameters including start
	delete mInitialLagrangianRacer;
	delete mLagrangianRacer;
	// items
	int							mNumPainters;
	delete[] mPainterPositions;
	delete[] mPainterColours;
	delete mCamera;
	// Textures
	delete mTextureHat;
	delete mTextureHead;
	delete mTextureBody;
	delete mTextureBottom;
	delete mTextureFloor;
	delete mTextureSky;
	delete mTextureTerrain;
	// Materials & Primitives
	for( int i=0; i<ELECTRICCOLOUR_NUM; i++) {
		delete mFloorMaterials[i];
		delete mHatMaterials[i];
		delete mHeadMaterials[i];
		delete mBodyMaterials[i];
		delete mBottomMaterials[i];
		delete mPainterMaterials[i];
		delete mEndMaterials[i];
		delete mPainterPrimitives[i];
	}
	delete[] mFloorMaterials;
	delete[] mHatMaterials;
	delete[] mHeadMaterials;
	delete[] mBodyMaterials;
	delete[] mBottomMaterials;
	delete[] mPainterMaterials;
	delete[] mEndMaterials;
	delete[] mPainterPrimitives;
	delete mHatPrimitive;
	delete mHeadPrimitive;
	delete mBodyPrimitive;
	delete mBottomPrimitive;
	delete mSkyPrimitive;
	delete mTerrainPrimitive;
	delete mEndPrimitive;
	delete mFloorPrimitive;
	// RacerRenderer
	delete mRacerRenderer;
}
void World::setForceRight( int force )
{
	mForceRight = force;
}
void World::setForceUp( int force )
{
	mForceUp = force;
}
void World::step( double seconds )
{
	// Step the terrain and items
	mTerrainPrimitive->step( seconds );
	mPainterAngle += seconds*mPainterAngularSpeed*180/M_PI;
	mEndAngle += seconds*mEndAngularSpeed*180/M_PI;

	// Set up the Lagrangian model's forces
	mLagrangianRacer->clearForces();
	mLagrangianRacer->setForceBottomModel(
		Vector3D(mForceMultiplierRight*mForceRight,mForceMultiplierUp*mForceUp,0) );
	mLagrangianRacer->setTorqueBottomModelZ( -mTorqueMultiplier*mForceRight );
	Vector3D toppos = mLagrangianRacer->getTopPosition();
	Vector3D bottompos = mLagrangianRacer->getBottomPosition();
	bool aboveground;
	// Step in the lagrangian model and update the state
	switch( mRacerState )
	{
	case RACINGSTATE_RACING:
		mLagrangianRacer->stepRacing( seconds );
		bottompos = mLagrangianRacer->getBottomPosition();
		// Check if you fell off the track
		if ( ! ( mRacerColour && mFloorColours->getValue( bottompos[0], bottompos[1], ELECTRICCOLOUR_BLACK ) ) ) {
			mRacerState = RACINGSTATE_FLYING;
			mCamera->freeze();
			gAudio->play_sfx( SFX_JUMP, true );
		}
		// Check if you smashed your head
		if ( ( mRacerColour && mFloorColours->getValue( toppos[0], toppos[1], ELECTRICCOLOUR_BLACK ) ) &&
				(toppos[2] - mHeadRadius) <= mBezierPatchGrid->computeFOnly( toppos[0], toppos[1] ) ) {
			reset();
			gAudio->play_sfx( SFX_SPIKE, true );
		}
		break;
	case RACINGSTATE_FLYING:
		aboveground = mLagrangianRacer->getZ() >= mBezierPatchGrid->computeFOnly( bottompos[0], bottompos[1] );
		mLagrangianRacer->stepFlying( seconds );
		bottompos = mLagrangianRacer->getBottomPosition();
		// Check if you drowned
		if ( toppos[2] <= mWaterLevel || bottompos[2] <= mWaterLevel ) {
			reset();
		}
		// Check if you smashed your head
		else if ( ( mRacerColour && mFloorColours->getValue( toppos[0], toppos[1], ELECTRICCOLOUR_BLACK ) ) &&
				(toppos[2] - mHeadRadius) <= mBezierPatchGrid->computeFOnly( toppos[0], toppos[1] ) ) {
			reset();
		}
		// Check if you're landing
		else if ( aboveground && ( mRacerColour && mFloorColours->getValue( bottompos[0], bottompos[1], ELECTRICCOLOUR_BLACK ) ) &&
				bottompos[2] <= mBezierPatchGrid->computeFOnly( bottompos[0], bottompos[1] ) ) {
			mLagrangianRacer->land();
			mRacerState = RACINGSTATE_RACING;
			mCamera->unfreeze();
		}
		break;
	case RACINGSTATE_HEADSMASH:
		reset();
		break;
	}
	// Check if you need to be painted
	for (int i=0; i<mNumPainters; i++) {
		if ( Collision::overlapSpheres( mHeadRadius, mPainterRadius, toppos, mPainterPositions[i] ) ) {
			if ( mRacerColour != mPainterColours[i] ) gAudio->play_sfx( SFX_GET_UPGRADE, true );
			mRacerColour = mPainterColours[i];
		}
	}
	// Check if you finished the level
	if ( Collision::overlapSpheres( mHeadRadius, mEndRadius, toppos, mEndPosition ) ||
		 Collision::overlapSpheres( mBottomRadius, mEndRadius, bottompos, mEndPosition ) ) {
		mFinished = true;
		gAudio->play_sfx( SFX_TELEPORT, true );
		//reset();
	}
}
void World::reset()
{
	mLagrangianRacer->resetState( *mInitialLagrangianRacer );
	static_cast<RacerCamera*>(mCamera)->setLagrangianRacer( mLagrangianRacer );
	mRacerState = RACINGSTATE_RACING;
	mRacerColour = mInitialRacerColour;
	mCamera->unfreeze();
}
void World::glRender() const
{

	glEnable( GL_DEPTH );
	glEnable( GL_DEPTH_TEST );
	glFrontFace( GL_CCW );
	glDisable( GL_CULL_FACE );
	//glCullFace( GL_BACK );
	glColor3d( 1,1,1 );
	
	//double brightness = 1.9;
	//if( brightness > 1 )
	//{
	//	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	//	glColor3f( brightness-1, brightness-1, brightness-1 );
	//}
	//else
	//{
	//	glBlendFunc( GL_ZERO, GL_SRC_COLOR );
	//	glColor3f( brightness, brightness, brightness );
	//}
	//glEnable( GL_BLEND );

	//glEnable(GL_COLOR_MATERIAL);
	glShadeModel( GL_SMOOTH );
	
	// Set up the perspective
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 90, 1.0*400/400, 0.01, 50000 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// Lighting before camera = light position relative to camera
	// Lighting after camera = light position relative to world

	// Set up the camera
	mCamera->glApply();

	// Set up the lighting
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	GLfloat light0pos[4];
	light0pos[0] = 4.0;
	light0pos[1] = 4.0;
	light0pos[2] = 200.0;
	light0pos[3] = 1;
	glLightfv( GL_LIGHT0, GL_POSITION, light0pos );
	light0pos[0] = 1.0;
	light0pos[1] = 1.0;
	light0pos[2] = 1.0;
	light0pos[3] = 1;
	glLightfv( GL_LIGHT0, GL_AMBIENT, light0pos );
	GLfloat light0spot[3];
	light0spot[0] = 0.0;
	light0spot[1] = 0.0;
	light0spot[2] = -1.0;
	glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, light0spot );
	//glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 45.0 );
	//glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 11.0 );
	glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0 );
	glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0 );
	glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0 );
	glEnable( GL_LIGHT0 );

	//glEnable( GL_LIGHT1 );
	//light0pos[0] = 0.0;
	//light0pos[1] = 0.0;
	//light0pos[2] = -100.0;
	//light0pos[3] = 1;
	//glLightfv( GL_LIGHT1, GL_POSITION, light0pos );
	//light0pos[0] = 1.0;
	//light0pos[1] = 1.0;
	//light0pos[2] = 1.0;
	//light0pos[3] = 1;
	//glLightfv( GL_LIGHT1, GL_AMBIENT, light0pos );
	//light0spot[0] = 0.0;
	//light0spot[1] = 0.0;
	//light0spot[2] = 1.0;
	//glLightfv( GL_LIGHT1, GL_SPOT_DIRECTION, light0spot );
	////glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 45.0 );
	////glLightf( GL_LIGHT1, GL_SPOT_EXPONENT, 11.0 );
	//glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0 );
	//glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0 );
	//glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0 );
	//glEnable( GL_LIGHT1 );
	
	// Render the sky
	glDisable( GL_LIGHTING );
	mSkyPrimitive->glRender();
	
	// Render the terrain
	glDisable( GL_LIGHTING );
	mTerrainPrimitive->glRender();
	glEnable( GL_LIGHTING );

	// Render the floor
	mFloorPrimitive->glRender();

	// Render the racer
	//glColor3d(1,1,1);
	mHatMaterials[mRacerColour]->glApply( GL_FRONT_AND_BACK );
	mHeadMaterials[mRacerColour]->glApply( GL_FRONT_AND_BACK );
	mBodyMaterials[mRacerColour]->glApply( GL_FRONT_AND_BACK );
	mBottomMaterials[mRacerColour]->glApply( GL_FRONT_AND_BACK );
	mRacerRenderer->glRender();

	// Render the items
	for (int i=0; i<mNumPainters; i++) {
		glPushMatrix();
		Vector3D painterpos = mPainterPositions[i];
		glTranslated( painterpos[0], painterpos[1], painterpos[2] );
		glRotated( mPainterAngle, 0.0, 0.0, 1.0 );
		mPainterPrimitives[ mPainterColours[i] ]->glRender();
		glPopMatrix();
	}
	glPushMatrix();
	glTranslated( mEndPosition[0], mEndPosition[1], mEndPosition[2] );
	glRotated( mEndAngle, 0.0, 0.0, 1.0 );
	mEndPrimitive->glRender();
	glPopMatrix();
}
bool World::getFinished() const
{
	return mFinished;
}