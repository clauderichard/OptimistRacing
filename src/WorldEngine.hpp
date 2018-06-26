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

//#pragma once
//
//#include "Bezier.hpp"
//#include "Grid.hpp"
//#include "ElectricColour.hpp"
//#include "Lagrange.hpp"
//
//enum E_RACINGSTATE {
//	RACINGSTATE_RACING,
//	RACINGSTATE_FLYING,
//	RACINGSTATE_HEADSMASH,
//	RACINGSTATE_NUM
//};
//
//class WorldEngine
//{
//public:
//	WorldEngine( const BezierPatchGrid* floor,
//		    const Grid2D<E_ELECTRICCOLOUR>* floorColours,
//		    const Grid2D<E_ELECTRICCOLOUR>* painterColours,
//			const Vector3D& endPosition,
//			double painterHeight, double painterRadius, double endRadius,
//			double headRadius, double waterLevel,
//			LagrangianRacer* lagrangianRacer, E_ELECTRICCOLOUR racerColour );
//	~WorldEngine();
//	LagrangianRacer* getLagrangianRacer();
//	void step( double seconds );
//	void reset();
//private:
//	// Variables
//	const BezierPatchGrid* mBezierPatchGrid;
//	const Grid2D<E_ELECTRICCOLOUR>* mFloorColours;
//	const Grid2D<E_ELECTRICCOLOUR>* mPainterColours;
//	const Vector3D mEndPosition;
//	const double mPainterHeight;
//	const double mPainterRadius;
//	const double mEndRadius;
//	const double mHeadRadius;
//	const double mWaterLevel;
//	const LagrangianRacer* mInitialLagrangianRacer;
//	LagrangianRacer* mLagrangianRacer;
//	E_RACINGSTATE mRacerState;
//	const E_ELECTRICCOLOUR mInitialRacerColour;
//	E_ELECTRICCOLOUR mRacerColour;
//
//};