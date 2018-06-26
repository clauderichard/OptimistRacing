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

#include "Camera.hpp"
#include <GL\glew.h>
#include <GL\freeglut.h>

using namespace Lagrange;

Camera::Camera()
	: mFreeze( false )
	, mPosition( 0, 0, 0 )
	, mUp( 0, 0, 1 )
{
}
Camera::~Camera()
{
}
void Camera::freeze()
{
	mFreeze = true;
}
void Camera::unfreeze()
{
	mFreeze = false;
}

RacerCamera::RacerCamera( LagrangianRacer* racer, double focusLengthFactor, double positionLengthFactor,
						  double backupBase, double backupFactor, double rotationFactor )
	: mRacer( racer )
	, mFocusLengthFactor( focusLengthFactor )
	, mPositionLengthFactor( positionLengthFactor )
	, mBackupBase( backupBase )
	, mBackupFactor( backupFactor )
	, mRotationFactor( rotationFactor )
	, mLength( racer->getLength() )
	, mThetaOffset( 0 )
{
}
RacerCamera::~RacerCamera()
{
}
void RacerCamera::setLagrangianRacer( LagrangianRacer* racer )
{
	mRacer = racer;
}
void RacerCamera::glApply()
{
	if ( mFreeze ) {
		double x = mRacer->getX();
		double y = mRacer->getY();
		double z = mRacer->getZ();
		double theta = mRacer->getTheta();
		double phi = mRacer->getPhi();
		double sinphi = sin(phi);
		double sintheta = sin(theta);
		double costheta = cos(theta);
		double xtopp = mLength*costheta*sinphi;
		double ytopp = mLength*sintheta*sinphi;
		double ztopp = mLength*cos(phi);
		double xfoc = x + mFocusLengthFactor*xtopp;
		double yfoc = y + mFocusLengthFactor*ytopp;
		double zfoc = z + mFocusLengthFactor*ztopp;
		gluLookAt( mPosition[0], mPosition[1], mPosition[2],
			   xfoc, yfoc, zfoc, mUp[0], mUp[1], mUp[2] );
		return;
	}
	double x = mRacer->getX();
	double y = mRacer->getY();
	double z = mRacer->getZ();
	double theta = mRacer->getTheta();
	double phi = mRacer->getPhi();
	double xdot = mRacer->getXDot();
	double ydot = mRacer->getYDot();
	double thetadot = mRacer->getThetaDot();
	double sinphi = sin(phi);
	double sintheta = sin(theta);
	double costheta = cos(theta);
	double xtopp = mLength*costheta*sinphi;
	double ytopp = mLength*sintheta*sinphi;
	double ztopp = mLength*cos(phi);
	double xfoc = x + mFocusLengthFactor*xtopp;
	double yfoc = y + mFocusLengthFactor*ytopp;
	double zfoc = z + mFocusLengthFactor*ztopp;
	double xpos = x + mPositionLengthFactor*xtopp;
	double ypos = y + mPositionLengthFactor*ytopp;
	double zpos = z + mPositionLengthFactor*ztopp;
	double fordot = ydot*costheta - xdot*sintheta;
	double dist = mBackupBase + fordot*mBackupFactor;
	mThetaOffset += thetadot*0.01;
	mThetaOffset *= mRotationFactor;
	double thetapos = theta + mThetaOffset;
	double phifac = 0.0;
	double upz = cos(phi*phifac);
	double upx = sin(phi*phifac)*cos(theta);
	double upy = sin(phi*phifac)*sin(theta);
	mPosition[0] = xpos + dist*sin(thetapos);
	mPosition[1] = ypos - dist*cos(thetapos);
	mPosition[2] = z+mLength*mPositionLengthFactor;
	mUp = Vector3D( upx, upy, upz );
	gluLookAt( mPosition[0], mPosition[1], mPosition[2],
			   xfoc, yfoc, zfoc, upx, upy, upz );
}