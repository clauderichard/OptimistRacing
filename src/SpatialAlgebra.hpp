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
//
//class SpatialFrame2D
//{
//public:
//	SpatialFrame2D( const Vector2D& origin, const Matrix2x2& axes );
//	~SpatialFrame2D();
//	Vector2D getOrigin();
//	Matrix2x2 getAxes();
//	Vector2D getAxis( int axisNumber );
//	Vector2D getXAxis();
//	Vector2D getYAxis();
//	Vector2D getWorldVector( const Vector2D& modelVector );
//	Vector2D getModelVector( const Vector2D& worldVector );
//private:
//	Vector2D mOrigin;
//	Matrix2x2 mAxes;
//};
//
//class SpatialAlgebra
//{
//public:
//	//// Length of a vector (= Euclidean norm)
//	//double length( const Vector2D& v );
//	//double length2( const Vector2D& v );
//	//double length( const Vector3D& v );
//	//double length2( const Vector3D& v );
//	//double length( const VectorND& v );
//	//double length2( const VectorND& v );
//	// Rotate a vector around a point-vector counter-clockwise
//	//   if axis is not specified, then rotate about origin and z-vector
//	Vector2D rotate( const Vector2D& v, double radians );
//	Vector2D rotate( const Vector2D& v, double radians,
//					 const Vector2D& axisOrigin );
//	Vector3D rotate( const Vector3D& v, double radians );
//	Vector3D rotate( const Vector3D& v, double radians,
//					 const Vector3D& axisDirection );
//	Vector3D rotate( const Vector3D& v, double radians,
//					 const Vector3D& axisOrigin, const Vector3D& axisDirection );
//};