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

#include "Lagrange.hpp"
#include <algorithm>
#include <cmath>

/**
 * \file This file deals with a specific model of Lagrangian Mechanics for the game.
 */

namespace Lagrange {

LagrangianRacer::LagrangianRacer( const BezierPatchGrid* bezierPatchGrid,
								  double gravity, double length, double massBottom, double massTop,
								  double IBottom, double ITopX, double ITopY, double ITopZ,
								  double xdotmax, double ydotmax, double zdotmax, double thetadotmax, double phidotmax,
								  double x, double y, double theta, double phi,
								  double xdot, double ydot, double thetadot, double phidot )
	: mBezierPatchGrid( bezierPatchGrid )
	, mGravity( gravity )
	, mLength( length )
	, mMassBottom( massBottom )
	, mMassTop( massTop )
	, mIBottom( IBottom )
	, mITopX( ITopX )
	, mITopY( ITopY )
	, mITopZ( ITopZ )
	, mXDotMax( xdotmax )
	, mYDotMax( ydotmax )
	, mZDotMax( zdotmax )
	, mThetaDotMax( thetadotmax )
	, mPhiDotMax( phidotmax )
	, mAlpha( massBottom + massTop )
	, mBeta( massTop*length*length + ITopX )
	, mGamma( massTop*length*length + ITopY )
	, mDelta( massTop*length )
	, mEpsilon( massTop*length*length + ITopX - ITopZ )
	, mLength1( massBottom / (massBottom+massTop) )
	, mLength2( length - mLength1 )
	, mZeta( massTop*mLength1*mLength1 + massBottom*mLength2*mLength2 + ITopX )
	, mEta( mZeta - ITopZ )
	, mIota( mEta / ( massTop*mLength1*mLength1 + massBottom*mLength2*mLength2 + ITopY ) )
	, mX( x )
	, mY( y )
	, mZ( bezierPatchGrid->computeFOnly( x, y ) )
	, mTheta( theta )
	, mPhi( phi )
	, mXDot( xdot )
	, mYDot( ydot )
	, mThetaDot( thetadot )
	, mPhiDot( phidot )
	, mForceBottomWorld( 0.0, 0.0, 0.0 )
	, mForceTopWorld( 0.0, 0.0, 0.0 )
	, mTorqueBottomModelZ( 0.0 )
	, mTorqueTopModel( 0.0, 0.0, 0.0 )
{
	MatrixMxN comp = mBezierPatchGrid->compute( x, y );
	mZDot = comp[1][0]*mXDot + comp[0][1]*mYDot;
}
LagrangianRacer::~LagrangianRacer()
{
}
LagrangianRacer* LagrangianRacer::create( const BezierPatchGrid* bezierPatchGrid, double gravity, double size,
										 double x, double y, double theta, double phi,
										 double xdot, double ydot, double thetadot, double phidot )
{
	return new LagrangianRacer( bezierPatchGrid, gravity, RACER_LENGTH, RACER_MASS_DEFAULT*size, RACER_MASS_DEFAULT*size,
		2.0*RACER_MASS_DEFAULT*RACER_RADIUS_DEFAULT*RACER_RADIUS_DEFAULT*size*size*size/5,
		2.0*RACER_MASS_DEFAULT*RACER_RADIUS_DEFAULT*RACER_RADIUS_DEFAULT*size*size*size/5,
		2.0*RACER_MASS_DEFAULT*RACER_RADIUS_DEFAULT*RACER_RADIUS_DEFAULT*size*size*size/5,
		2.0*RACER_MASS_DEFAULT*RACER_RADIUS_DEFAULT*RACER_RADIUS_DEFAULT*size*size*size/5,
		RACER_XDOT_MAX, RACER_YDOT_MAX, RACER_ZDOT_MAX, RACER_THETADOT_MAX, RACER_PHIDOT_MAX,
		x, y, theta, phi, xdot, ydot, thetadot, phidot );
}
const BezierPatchGrid* LagrangianRacer::getBezierPatchGrid() const
{
	return mBezierPatchGrid;
}
double LagrangianRacer::getGravity() const
{
	return mGravity;
}
double LagrangianRacer::getLength() const
{
	return mLength;
}
double LagrangianRacer::getMassBottom() const
{
	return mMassBottom;
}
double LagrangianRacer::getMassTop() const
{
	return mMassTop;
}
double LagrangianRacer::getIBottom() const
{
	return mIBottom;
}
double LagrangianRacer::getITopX() const
{
	return mITopX;
}
double LagrangianRacer::getITopY() const
{
	return mITopY;
}
double LagrangianRacer::getITopZ() const
{
	return mITopZ;
}
double LagrangianRacer::getX() const
{
	return mX;
}
double LagrangianRacer::getY() const
{
	return mY;
}
double LagrangianRacer::getZ() const
{
	return mZ;
}
double LagrangianRacer::getTheta() const
{
	return mTheta;
}
double LagrangianRacer::getPhi() const
{
	return mPhi;
}
double LagrangianRacer::getXDot() const
{
	return mXDot;
}
double LagrangianRacer::getYDot() const
{
	return mYDot;
}
double LagrangianRacer::getZDot() const
{
	return mZDot;
}
double LagrangianRacer::getThetaDot() const
{
	return mThetaDot;
}
double LagrangianRacer::getPhiDot() const
{
	return mPhiDot;
}
Vector3D LagrangianRacer::getBottomPosition() const
{
	return Vector3D( mX, mY, mZ );
}
Vector3D LagrangianRacer::getTopPosition() const
{
	return Vector3D( mX, mY, mZ ) + mLength*Vector3D(cos(mTheta)*sin(mPhi), sin(mTheta)*sin(mPhi), cos(mPhi));
}
void LagrangianRacer::clearForces()
{
	mForceBottomWorld = Vector3D(0,0,0);
	mForceTopWorld = Vector3D(0,0,0);
	mTorqueTopModel = Vector3D(0,0,0);
	mTorqueBottomModelZ = 0;
}
void LagrangianRacer::setForceBottomWorld( const Vector3D& force )
{
	mForceBottomWorld = force;
}
void LagrangianRacer::setForceTopWorld( const Vector3D& force )
{
	mForceTopWorld = force;
}
void LagrangianRacer::setForceBottomModel( const Vector3D& force )
{
	double fx = force[0];
	double fy = force[1];
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	mForceBottomWorld[0] = fx*costheta - fy*sintheta;
	mForceBottomWorld[1] = fx*sintheta + fy*costheta;
	mForceBottomWorld[2] = force[2];
}
void LagrangianRacer::setForceTopModel( const Vector3D& force )
{
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	double cosphi = cos(mPhi);
	double sinphi = sin(mPhi);
	double fx = force[0];
	double fy = force[1];
	double fz = force[2];
	mForceTopWorld[0] = fx*costheta*cosphi - fy*sintheta + fz*costheta*sinphi;
	mForceTopWorld[1] = fx*sintheta*cosphi + fy*costheta + fz*sintheta*sinphi;
	mForceTopWorld[2] = fz*cosphi - fx*sinphi;
}
void LagrangianRacer::setTorqueBottomModelZ( double torque )
{
	mTorqueBottomModelZ = torque;
}
void LagrangianRacer::setTorqueBottomModel( const Vector3D& torque )
{
	mTorqueBottomModelZ = torque[2];
}
void LagrangianRacer::setTorqueTopModel( const Vector3D& torque )
{
	mTorqueTopModel = torque;
}
void LagrangianRacer::setTorqueTopWorld( const Vector3D& torque )
{
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	double cosphi = cos(mPhi);
	double sinphi = sin(mPhi);
	double tx = torque[0];
	double ty = torque[1];
	double tz = torque[2];
	mTorqueTopModel[0] = tx*costheta*cosphi + ty*sintheta*cosphi - tz*sinphi;
	mTorqueTopModel[1] = ty*costheta - tx*sintheta;
	mTorqueTopModel[2] = tx*costheta*sinphi + ty*sintheta*sinphi + tz*cosphi;
}
void LagrangianRacer::addForceBottomWorld( const Vector3D& force )
{
	mForceBottomWorld = mForceBottomWorld + force;
}
void LagrangianRacer::addForceTopWorld( const Vector3D& force )
{
	mForceTopWorld = mForceTopWorld + force;
}
void LagrangianRacer::addForceBottomModel( const Vector3D& force )
{
	double fx = force[0];
	double fy = force[1];
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	mForceBottomWorld[0] += fx*costheta - fy*sintheta;
	mForceBottomWorld[1] += fx*sintheta + fy*costheta;
	mForceBottomWorld[2] += force[2];
}
void LagrangianRacer::addForceTopModel( const Vector3D& force )
{
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	double cosphi = cos(mPhi);
	double sinphi = sin(mPhi);
	double fx = force[0];
	double fy = force[1];
	double fz = force[2];
	mForceTopWorld[0] += fx*costheta*cosphi - fy*sintheta + fz*costheta*sinphi;
	mForceTopWorld[1] += fx*sintheta*cosphi + fy*costheta + fz*sintheta*sinphi;
	mForceTopWorld[2] += fz*cosphi - fx*sinphi;
}
void LagrangianRacer::addTorqueBottomModelZ( double torque )
{
	mTorqueBottomModelZ += torque;
}
void LagrangianRacer::addTorqueBottomModel( const Vector3D& torque )
{
	mTorqueBottomModelZ += torque[2];
}
void LagrangianRacer::addTorqueTopModel( const Vector3D& torque )
{
	mTorqueTopModel = mTorqueTopModel + torque;
}
void LagrangianRacer::addTorqueTopWorld( const Vector3D& torque )
{
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	double cosphi = cos(mPhi);
	double sinphi = sin(mPhi);
	double tx = torque[0];
	double ty = torque[1];
	double tz = torque[2];
	mTorqueTopModel[0] += tx*costheta*cosphi + ty*sintheta*cosphi - tz*sinphi;
	mTorqueTopModel[1] += ty*costheta - tx*sintheta;
	mTorqueTopModel[2] += tx*costheta*sinphi + ty*sintheta*sinphi + tz*cosphi;
}
void LagrangianRacer::stepRacing( double seconds )
{
	MatrixMxN FBezier = mBezierPatchGrid->compute(mX, mY);
	double f = FBezier[0][0];
	double fx = FBezier[1][0];
	double fy = FBezier[0][1];
	double fxx = FBezier[2][0];
	double fxy = FBezier[1][1];
	double fyy = FBezier[0][2];
	double alphaFx = mAlpha*fx;
	double alphaFy = mAlpha*fy;
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	double cosphi = cos(mPhi);
	double sinphi = sin(mPhi);
	double xdot2 = mXDot*mXDot;
	double ydot2 = mYDot*mYDot;
	double thetadot2 = mThetaDot*mThetaDot;
	double phidot2 = mPhiDot*mPhiDot;
	double xydot = 2*mXDot*mYDot;
	double thetaphidot = 2*mThetaDot*mPhiDot;
	double a = xdot2*fxx + ydot2*fyy + xydot*fxy + mGravity;
	double mtlcossin = mDelta*costheta*sinphi;
	double epsilonsamesincos = mEpsilon*sinphi*cosphi;
	double thetadot2plusphidot2 = thetadot2 + phidot2;
	// vector b
	double b1 = alphaFx*a - mDelta*( costheta*sinphi*(thetadot2plusphidot2) + cosphi*(fx*phidot2 + sintheta*thetaphidot) );
	double b2 = alphaFy*a - mDelta*( sintheta*sinphi*(thetadot2plusphidot2) + cosphi*(fy*phidot2 - costheta*thetaphidot) );
	double b3 = mEpsilon*sinphi*cosphi*thetaphidot;
	double b4 = - sinphi*(mDelta*a + mEpsilon*cosphi*thetadot2);
	// generalized forces
	double qx = mForceBottomWorld[0] + mForceTopWorld[0] + fx*(mForceBottomWorld[2] + mForceTopWorld[2]);
	double qy = mForceBottomWorld[1] + mForceTopWorld[1] + fy*(mForceBottomWorld[2] + mForceTopWorld[2]);
	double qtheta = mLength*sinphi*(mForceTopWorld[1]*costheta - mForceTopWorld[0]*sintheta) +
		            mTorqueBottomModelZ + mTorqueTopModel[2]*cosphi - mTorqueTopModel[0]*sinphi;
	double qphi = mLength*( cosphi*(mForceTopWorld[0]*costheta+mForceTopWorld[1]*sintheta) - sinphi*mForceTopWorld[2]) +
		          mTorqueTopModel[1];
	// matrix A
	double a11 = mAlpha*(1+fx*fx);
	double a12 = mAlpha*fx*fy;
	double a22 = mAlpha*(1+fy*fy);
	double a13 = - mDelta*sintheta*sinphi;
	double a23 = mDelta*costheta*sinphi;
	double a33 = mBeta*sinphi*sinphi + mITopZ*cosphi*cosphi + mIBottom;
	double a14 = mDelta*(costheta*cosphi-fx*sinphi);
	double a24 = mDelta*(sintheta*cosphi-fy*sinphi);

	double avalues[16] = { a11, a12, a13, a14, a12, a22, a23, a24, a13, a23, a33, 0, a14, a24, 0, mGamma };
	double vecvalues[4] = { qx-b1, qy-b2, qtheta-b3, qphi-b4 };
	MatrixMxN XDotDot = MatrixMxN(4,4,avalues).invert() * MatrixMxN(4,1,vecvalues);
	// use XDotDot to update the state
	mX = mX + mXDot*seconds + seconds*seconds*XDotDot[0][0]/2;
	mY = mY + mYDot*seconds + seconds*seconds*XDotDot[1][0]/2;
	mZ = mBezierPatchGrid->computeFOnly(mX, mY);
	mTheta = mTheta + mThetaDot*seconds + seconds*seconds*XDotDot[2][0]/2;
	mPhi = mPhi + mPhiDot*seconds + seconds*seconds*XDotDot[3][0]/2;
	mXDot = mXDot + seconds*XDotDot[0][0];
	mYDot = mYDot + seconds*XDotDot[1][0];
	mThetaDot = mThetaDot + seconds*XDotDot[2][0];
	mPhiDot = mPhiDot + seconds*XDotDot[3][0];
	mXDot = std::min(mXDotMax, std::max(-mXDotMax,mXDot));
	mYDot = std::min(mYDotMax, std::max(-mYDotMax,mYDot));
	mZDot = fx*mXDot + fy*mYDot;
	mThetaDot = std::min(mThetaDotMax, std::max(-mThetaDotMax,mThetaDot));
	mPhiDot = std::min(mPhiDotMax, std::max(-mPhiDotMax,mPhiDot));
}
void LagrangianRacer::stepFlying( double seconds )
{
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	double cosphi = cos(mPhi);
	double sinphi = sin(mPhi);
	double xthetadot = mXDot*mThetaDot;
	double xphidot = mXDot*mPhiDot;
	double ythetadot = mYDot*mThetaDot;
	double yphidot = mYDot*mPhiDot;
	double zphidot = mZDot*mPhiDot;
	double thetadot2 = mThetaDot*mThetaDot;
	double phidot2 = mPhiDot*mPhiDot;
	double thetaphidot = 2*mThetaDot*mPhiDot;
	//double mtlcossin = mDelta*costheta*sinphi;
	//double epsilonsamesincos = mEpsilon*sinphi*cosphi;
	double thetadot2plusphidot2 = thetadot2 + phidot2;
	double sincosphi = sinphi*cosphi;
	double eps = mEpsilon*sincosphi;
	// vector b
	double b1 = -mDelta*(costheta*sinphi*thetadot2plusphidot2 - thetaphidot*sintheta*cosphi);
	double b2 = -mDelta*(sintheta*sinphi*thetadot2plusphidot2 + thetaphidot*costheta*cosphi);
	double b3 = mAlpha*mGravity - mDelta*cosphi*phidot2;
	double b4 = thetaphidot*eps - mDelta*(xthetadot*costheta*sinphi + ythetadot*sintheta*sinphi +
										  xphidot*sintheta*cosphi - yphidot*costheta*cosphi);
	double b5 = -thetadot2*eps - mDelta*mGravity*sinphi;
	// generalized forces
	double qx = mForceBottomWorld[0] + mForceTopWorld[0];
	double qy = mForceBottomWorld[1] + mForceTopWorld[1];
	double qz = mForceBottomWorld[2] + mForceTopWorld[2];
	double qtheta = mLength*sinphi*(mForceTopWorld[1]*costheta - mForceTopWorld[0]*sintheta) +
		            mTorqueBottomModelZ + mTorqueTopModel[2]*cosphi - mTorqueTopModel[0]*sinphi;
	double qphi = mLength*( cosphi*(mForceTopWorld[0]*costheta+mForceTopWorld[1]*sintheta) - sinphi*mForceTopWorld[2]) +
		          mTorqueTopModel[1];
	// matrix A
	double a14 = -mDelta*sintheta*sinphi;
	double a15 = mDelta*costheta*cosphi;
	double a24 = mDelta*costheta*sinphi;
	double a25 = mDelta*sintheta*cosphi;
	double a35 = -mDelta*sinphi;
	double a44 = mBeta*sinphi*sinphi + mITopZ*cosphi*cosphi + mIBottom;
	// find XDotDot vector
	double avalues[25] = { mAlpha, 0, 0, a14, a15, 0, mAlpha, 0, a24, a25, 0, 0, mAlpha, 0, a35, a14, a24, 0, a44, 0, a15, a25, a35, 0, mGamma };
	double vecvalues[5] = { qx-b1, qy-b2, qz-b3, qtheta-b4, qphi-b5 };
	MatrixMxN XDotDot = MatrixMxN(5,5,avalues).invert() * MatrixMxN(5,1,vecvalues);
	// use XDotDot to update the state
	mX += mXDot*seconds + seconds*seconds*XDotDot[0][0]/2;
	mY += mYDot*seconds + seconds*seconds*XDotDot[1][0]/2;
	mZ += mZDot*seconds + seconds*seconds*XDotDot[2][0]/2;
	mTheta += mThetaDot*seconds + seconds*seconds*XDotDot[3][0]/2;
	mPhi += mPhiDot*seconds + seconds*seconds*XDotDot[4][0]/2;
	mXDot = mXDot + seconds*XDotDot[0][0];
	mYDot = mYDot + seconds*XDotDot[1][0];
	mZDot = mZDot + seconds*XDotDot[2][0];
	mThetaDot = mThetaDot + seconds*XDotDot[3][0];
	mPhiDot = mPhiDot + seconds*XDotDot[4][0];
	mXDot = std::min(mXDotMax, std::max(-mXDotMax,mXDot));
	mYDot = std::min(mYDotMax, std::max(-mYDotMax,mYDot));
	mZDot = std::min(mZDotMax, std::max(-mZDotMax,mZDot));
	mThetaDot = std::min(mThetaDotMax, std::max(-mThetaDotMax,mThetaDot));
	mPhiDot = std::min(mPhiDotMax, std::max(-mPhiDotMax,mPhiDot));
}
void LagrangianRacer::land()
{
	double costheta = cos(mTheta);
	double sintheta = sin(mTheta);
	double cosphi = cos(mPhi);
	double sinphi = sin(mPhi);
	// matrix A
	double a14 = -mDelta*sintheta*sinphi;
	double a15 = mDelta*costheta*cosphi;
	double a24 = mDelta*costheta*sinphi;
	double a25 = mDelta*sintheta*cosphi;
	double a35 = -mDelta*sinphi;
	double a44 = mBeta*sinphi*sinphi + mITopZ*cosphi*cosphi + mIBottom;
	double avalues[25] = { mAlpha, 0, 0, a14, a15, 0, mAlpha, 0, a24, a25, 0, 0, mAlpha, 0, a35, a14, a24, 0, a44, 0, a15, a25, a35, 0, mGamma };
	MatrixMxN Ainv = MatrixMxN(5,5,avalues).invert();
	// compute f
	MatrixMxN FBezier = mBezierPatchGrid->compute(mX, mY);
	double f = FBezier[0][0];
	double fx = FBezier[1][0];
	double fy = FBezier[0][1];
	// vectors q and N
	double nval[5] = { -fx, -fy, 1, 0, 0 };
	VectorND N( 5, nval );
	VectorND q = N;
	double xdotval[5] = { mXDot, mYDot, mZDot, mThetaDot, mPhiDot };
	VectorND xdot( 5, xdotval );
	VectorND ydot = xdot - Ainv * ( ( xdot.dot(N) / (Ainv*q).dot(N) ) * q );
	mXDot = ydot[0];
	mYDot = ydot[1];
	mZDot = ydot[2];
	mThetaDot = ydot[3];
	mPhiDot = ydot[4];
	mZ = f;
};

void LagrangianRacer::resetState( const LagrangianRacer& templateRacer )
{
	mX = templateRacer.mX;
	mY = templateRacer.mY;
	mZ = templateRacer.mZ;
	mTheta = templateRacer.mTheta;
	mPhi = templateRacer.mPhi;
	mXDot = templateRacer.mXDot;
	mYDot = templateRacer.mYDot;
	mZDot = templateRacer.mZDot;
	mThetaDot = templateRacer.mThetaDot;
	mPhiDot = templateRacer.mPhiDot;
}

}