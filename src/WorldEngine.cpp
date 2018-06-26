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

//#include "WorldEngine.hpp"
//#include "Collision.hpp"
//
//
//// WorldEngine
//WorldEngine::WorldEngine( const BezierPatchGrid* floor,
//		const Grid2D<E_ELECTRICCOLOUR>* floorColours,
//		const Grid2D<E_ELECTRICCOLOUR>* painterColours,
//		const Vector3D& endPosition,
//		double painterHeight, double painterRadius, double endRadius,
//		double headRadius, double waterLevel,
//		LagrangianRacer* lagrangianRacer, E_ELECTRICCOLOUR racerColour )
//		: mBezierPatchGrid( floor )
//		, mFloorColours( floorColours )
//		, mPainterColours( painterColours )
//		, mEndPosition( endPosition )
//		, mPainterHeight( painterHeight )
//		, mPainterRadius( painterRadius )
//		, mEndRadius( endRadius )
//		, mHeadRadius( headRadius )
//		, mWaterLevel( waterLevel )
//		, mInitialLagrangianRacer( new LagrangianRacer( *lagrangianRacer ) )
//		, mLagrangianRacer( lagrangianRacer )
//		, mRacerState( RACINGSTATE_RACING )
//		, mInitialRacerColour( racerColour )
//		, mRacerColour( racerColour )
//{
//}
//WorldEngine::~WorldEngine()
//{
//}
//LagrangianRacer* WorldEngine::getLagrangianRacer()
//{
//	return mLagrangianRacer;
//}
//void WorldEngine::step( double seconds )
//{
//	Vector3D toppos = mLagrangianRacer->getTopPosition();
//	// Step in the lagrangian model and update the state
//	switch( mRacerState )
//	{
//	case RACINGSTATE_RACING:
//		mLagrangianRacer->stepRacing( seconds );
//		// Check if you fell off the track
//		if ( ! ElectricColour::match( mRacerColour, mFloorColours->getValue( mLagrangianRacer->getX(), mLagrangianRacer->getY(), ELECTRICCOLOUR_BLACK ) ) ) {
//			mRacerState = RACINGSTATE_FLYING;
//		}
//		// Check if you smashed your head
//		if ( ElectricColour::match( mRacerColour, mFloorColours->getValue( toppos[0], toppos[1], ELECTRICCOLOUR_BLACK ) ) &&
//				(toppos[2] - mHeadRadius) <= mBezierPatchGrid->computeFOnly( toppos[0], toppos[1] ) ) {
//			reset();
//		}
//		break;
//	case RACINGSTATE_FLYING:
//		mLagrangianRacer->stepFlying( seconds );
//		// Check if you drowned
//		if ( toppos[2] <= mWaterLevel || mLagrangianRacer->getZ() <= mWaterLevel ) {
//			reset();
//		}
//		// Check if you smashed your head
//		if ( ElectricColour::match( mRacerColour, mFloorColours->getValue( toppos[0], toppos[1], ELECTRICCOLOUR_BLACK ) ) &&
//				(toppos[2] - mHeadRadius) <= mBezierPatchGrid->computeFOnly( toppos[0], toppos[1] ) ) {
//			reset();
//		}
//		break;
//	case RACINGSTATE_HEADSMASH:
//		reset();
//		break;
//	}
//	// Check if you need to be painted
//	double paintI = floor(toppos[0]/mPainterColours->getGridHX()) + 0.5;
//	double paintJ = floor(toppos[1]/mPainterColours->getGridHY()) + 0.5;
//	double paintX = paintI*mPainterColours->getGridHX();
//	double paintY = paintJ*mPainterColours->getGridHY();
//	if ( Collision::overlapSpheres( mHeadRadius, mPainterRadius, toppos, Vector3D( paintX, paintY, mPainterHeight ) ) ) {
//		E_ELECTRICCOLOUR paintColour = mPainterColours->getValue( toppos[0], toppos[1], ELECTRICCOLOUR_BLACK );
//		if (paintColour!=ELECTRICCOLOUR_BLACK) mRacerColour = paintColour;
//	}
//	// Check if you finished the level
//	if ( Collision::overlapSpheres( mHeadRadius, mEndRadius, toppos, mEndPosition ) ) {
//		reset();
//	}
//}
//void WorldEngine::reset()
//{
//	delete mLagrangianRacer;
//	mLagrangianRacer = new LagrangianRacer( *mInitialLagrangianRacer );
//	mRacerState = RACINGSTATE_RACING;
//}