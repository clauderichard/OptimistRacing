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
#include "Bezier.hpp"

namespace Lagrange {

	// These are used for LagrangianRacerWrapper
	#define RACER_MASS_DEFAULT 1.0
	#define RACER_RADIUS_DEFAULT 1.0
	#define RACER_LENGTH 1.0
	#define RACER_FORWARD_FORCE 25.0
	#define RACER_SKID_FORCE 100.0
	#define RACER_TORQUE_FACTOR 1.0 // Torque = leftforce*factor*radius
	#define RACER_XDOT_MAX 10.0
	#define RACER_YDOT_MAX 10.0
	#define RACER_ZDOT_MAX 10.0
	#define RACER_THETADOT_MAX 10.0
	#define RACER_PHIDOT_MAX 10.0
	#define FLYER_ZCDOT_MAX 10.0
	#define FLYER_THETADOT_MAX 10.0
	#define FLYER_PHIDOT_MAX 10.0


	// TODO: use LagrangianModel as a base class for the racing and flying model
	//class LagrangianModel
	//{
	//	// Returns A and b and Q such that
	//	// A*Xdotdot + b = Q
	//	virtual MatrixMxN getA() const = 0;
	//	virtual VectorND getB() const = 0;
	//	virtual VectorND getQ() const = 0;
	//	// Returns positions of objects as functions of generalized coordinates
	//	VectorFunction getCenterOfMassPositionFunction( int obji ) const;
	//	VectorFunction getEulerAnglesFunction( int obji ) const;
	//	// After doing one timestep, do this.
	//	virtual void adjustAfterStep();
	//	// Generalized coordinates
	//	VectorND getGeneralizedPosition() const;
	//	VectorND getGeneralizedVelocity() const;
	//	VectorND getGeneralizedAcceleration() const; // compute using A*Xdotdot+b=Q
	//	// Get properties of each object
	//	double getMass( int obji ) const;
	//	Matrix3x3 getMomentOfInertiaTensorModel( int obji ) const;
	//	Matrix3x3 getMomentOfInertiaTensorWorld( int obji ) const;
	//	Vector3D getCenterOfMassPosition( int obji ) const;
	//	Vector3D getEulerAnglesPosition( int obji ) const;
	//	Vector3D getCenterOfMassVelocity( int obji ) const;
	//	Vector3D getEulerAnglesVelocity( int obji ) const;
	//	// Set forces, which will set Q
	//	void clearForces();
	//	void setForceWorld( int obji, const Vector3D& force );
	//	void setForceModel( int obji, const Vector3D& force );
	//	void setTorqueModel( int obji, const Vector3D& torque );
	//	void setTorqueWorld( int obji, const Vector3D& torque );
	//	void addForceWorld( int obji, const Vector3D& force );
	//	void addForceModel( int obji, const Vector3D& force );
	//	void addTorqueModel( int obji, const Vector3D& torque );
	//	void addTorqueWorld( int obji, const Vector3D& torque );
	//	// Apply an impulse such that afterwards, Xdot.dot(N)=0
	//	void applyConstraintImpulse( const VectorND& N ); // use stored Q for direction of impulse
	//	void applyConstraintImpulse( const VectorND& N, const Vector3D& Q );
	//	// Step
	//	void step( double seconds );
	//	void step( double totalSeconds, int numIterations ); // do numIterations timesteps
	//protected:
	//	int				mNumObjects;
	//	VectorFunction*	mCenterOfMassPositionFunctions;
	//	VectorFunction*	mEulerAnglesFunctions;
	//	VectorND		mGeneralizedPosition;
	//	VectorND		mGeneralizedVelocity;
	//};


	class LagrangianCoordinates
	{
	public:
		LagrangianCoordinates( int n );
		~LagrangianCoordinates();
	};


	class LagrangianObject
	{
	public:
		LagrangianObject();
		~LagrangianObject();
		// Get the position and Euler angles
		double getX();
		double getY();
		double getZ();
		double getAlpha();
		double getBeta();
		double getGamma();
		// Compute the velocity
	private:

	};



	class LagrangianRacer
	{
	public:
		LagrangianRacer( const BezierPatchGrid* bezierPatchGrid,
						 double gravity, double length, double massBottom, double massTop,
						 double IBottom, double ITopX, double ITopY, double ITopZ,
						 double xdotmax, double ydotmax, double zdotmax, double thetadotmax, double phidotmax,
						 double x, double y, double theta, double phi,
						 double xdot, double ydot, double thetadot, double phidot );
		~LagrangianRacer();
		LagrangianRacer* create( const BezierPatchGrid* bezierPatchGrid, double gravity, double size,
						 double x, double y, double theta, double phi,
						 double xdot, double ydot, double thetadot, double phidot );
		// Get methods
		//   floor grid
		const BezierPatchGrid* getBezierPatchGrid() const;
		//   parameters
		double getGravity() const;
		double getLength() const;
		double getMassBottom() const;
		double getMassTop() const;
		double getIBottom() const;
		double getITopX() const;
		double getITopY() const;
		double getITopZ() const;
		//   state
		double getX() const;
		double getY() const;
		double getZ() const;
		double getTheta() const;
		double getPhi() const;
		double getXDot() const;
		double getYDot() const;
		double getZDot() const;
		double getThetaDot() const;
		double getPhiDot() const;
		Vector3D getBottomPosition() const;
		Vector3D getTopPosition() const;
		// Set forces
		void clearForces();
		void setForceBottomWorld( const Vector3D& force );
		void setForceTopWorld( const Vector3D& force );
		void setForceBottomModel( const Vector3D& force );
		void setForceTopModel( const Vector3D& force );
		void setTorqueBottomModelZ( double torque ); // torque is the z-value of torque vector
		void setTorqueBottomModel( const Vector3D& torque );
		void setTorqueTopModel( const Vector3D& torque );
		void setTorqueTopWorld( const Vector3D& torque );
		void addForceBottomWorld( const Vector3D& force );
		void addForceTopWorld( const Vector3D& force );
		void addForceBottomModel( const Vector3D& force );
		void addForceTopModel( const Vector3D& force );
		void addTorqueBottomModelZ( double torque ); // torque is the z-value of torque vector
		void addTorqueBottomModel( const Vector3D& torque );
		void addTorqueTopModel( const Vector3D& torque );
		void addTorqueTopWorld( const Vector3D& torque );
		// Compute the next timestep.
		void stepRacing( double seconds );
		void stepFlying( double seconds );
		void land();
		// Reset
		void resetState( const LagrangianRacer& templateRacer );
	private:
		const BezierPatchGrid* mBezierPatchGrid;
		// parameters
		double mGravity;
		double mLength;
		double mMassBottom;
		double mMassTop;
		double mIBottom;
		double mITopX;
		double mITopY;
		double mITopZ;
		// max velocity
		double mXDotMax;
		double mYDotMax;
		double mZDotMax;
		double mThetaDotMax;
		double mPhiDotMax;
		// convenient values
		double mAlpha; // 2 masses added together
		double mBeta; // mt*l^2 + I1
		double mGamma; // mt*l^2 + I2
		double mDelta; // mt*l
		double mEpsilon; // mt*l^2 + I1 - I3
		double mLength1;
		double mLength2;
		double mZeta; // m1*l1^2 + m2*l2^2 + Ix
		double mEta; // m1*l1^2 + m2*l2^2 + Ix - Iz
		double mIota; // (m1*l1^2 + m2*l2^2 + Ix - Iz) / (m1*l1^2 + m2*l2^2 + ITopY)
		// state
		double mX;
		double mY;
		double mZ;
		double mTheta;
		double mPhi;
		double mXDot;
		double mYDot;
		double mZDot;
		double mThetaDot;
		double mPhiDot;
		// Forces
		Vector3D mForceBottomWorld;
		Vector3D mForceTopWorld;
		double mTorqueBottomModelZ;
		Vector3D mTorqueTopModel;
	};

}