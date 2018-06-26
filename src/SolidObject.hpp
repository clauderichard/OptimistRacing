///*	Copyright (C) 2012  Claude Richard
// *
// *	Optimist Racing is free software: you can redistribute it and/or modify
// *	it under the terms of the GNU General Public License as published by
// *	the Free Software Foundation, either version 3 of the License, or
// *	(at your option) any later version.
// *
// *	Optimist Racing is distributed in the hope that it will be useful,
// *	but WITHOUT ANY WARRANTY; without even the implied warranty of
// *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *	GNU General Public License for more details.
// *
// *	You should have received a copy of the GNU General Public License
// *	along with Optimist Racing.  If not, see <http://www.gnu.org/licenses/>.
// */
//
//#pragma once
//
//#include "Algebra.hpp"
//
//// This class represents a solid object.
//// It stores information like its
////   mass, 
////   center-of-mass,
////   moment of inertia tensor about its c-o-m with frame parallel to origin frame
//class SolidObject
//{
//public:
//	// Create a "nothing" object
//	SolidObject();
//	// Set the object's properties
//	SolidObject( double mass, const Vector3D& centerOfMass, const Matrix3x3& momentOfInertiaTensor );
//	// Create an object out of a list of objects
//	//   that will be fused together.
//	SolidObject( int numObjects, SolidObject* objects );
//	~SolidObject();
//	double getMass();
//	void setMass( double mass );
//	// about origin frame
//	Vector3D getCenterOfMass();
//	void setCenterOfMass( const Vector3D& centerOfMass );
//	// about c-o-m, frame parallel to origin frame
//	Matrix3x3 getMomentOfInertiaTensor();
//	// about point, frame parallel to origin frame
//	Matrix3x3 getMomentOfInertiaTensor( Vector3D point );
//	// about a frame whose origin is point
//	// frame.1stcolumn is the x-axis, etc.
//	Matrix3x3 getMomentOfInertiaTensor( Vector3D point, Matrix3x3 frame );
//	// Create different shapes automatically
//	SolidObject createFullSphere( double mass, const Vector3D& centerOfMass );
//	SolidObject createHollowSphere( double mass, const Vector3D& centerOfMass );
//	// TODO: add more shapes
//private:
//	double mMass;
//	Vector3D mCenterOfMass;
//	// about the center-of-mass, frame parallel to origin frame
//	Matrix3x3 mMomentOfInertiaTensor;
//};