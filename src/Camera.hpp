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

#include "Algebra.hpp"
#include "Lagrange.hpp"
using namespace Lagrange;


/// This class is meant to store the position of a camera that doesn't interact physically with the world.
/// Can store position while frozen in space.
class Camera
{

public:

	/**
	 * Basic constructor, begins unfrozen, at the origin, with a standard orientation.
	 */
	Camera();

	/**
	 * Destructor, does not do anything since it doesn't have to.
	 */
	~Camera();

	/**
	 * Sets up the camera in OpenGL according to the camera's position and orientation.
	 * I.e. multiplies the transformation matrix in OpenGL by the right translations and rotations.
	 * You should usually call this in ModelView mode before drawing anything.
	 */
	virtual void glApply() = 0;

	/**
	 * Freezes the position of the camera, but not its orientation,
	 * so that if the point of focus moves, the camera doesn't move with it anymore.
	 */
	void freeze();
	
	/**
	 * Undoes the effect of the freeze method, so that the camera moves as usual again.
	 */
	void unfreeze();

protected:
	bool mFreeze;
	Vector3D mPosition;
	Vector3D mUp;

};


/// This camera will follow a racer from behind.
class RacerCamera : public Camera
{

public:
	
	/**
	 * Sets up the camera to follow racer.
	 */
	RacerCamera( LagrangianRacer* racer, double focusLengthFactor, double positionLengthFactor,
				 double backupBase, double backupFactor, double rotationFactor );

	/**
	 * Doesn't do anything. The racer pointer is not destroyed.
	 */
	~RacerCamera();
	
	/**
	 * Starts following another racer.
	 */
	void setLagrangianRacer( LagrangianRacer* racer );
	
	/**
	 * Implements Camera::glApply
	 */
	virtual void glApply();

private:
	LagrangianRacer* mRacer;
	// focus will be = bottom + factor*(head-bottom)
	double mFocusLengthFactor;
	double mPositionLengthFactor;
	double mBackupBase;
	double mBackupFactor;
	double mRotationFactor;
	double mLength;
	double mThetaOffset;

};