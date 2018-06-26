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

/**
 * This file contains the code necessary for all sorts of linear algebra,
 * which includes vectors and matrices of varying sizes.
 */

#pragma once
#include <algorithm>
#include <cmath>

//#define M_PI 3.141592653589793

/**
 * \brief		Represents a vector with 2 entries.
 * \details		This class includes some operations that you can do with 2D vectors.
 * \author		Claude Richard
 * \date		2012
 */
class Vector2D
{
public:

	/**
	 * \brief		Makes a zero vector.
	 * \details		After this constructor is done, both entries in the vector will be zero.
	 * \post		Both entries in the vector are zero.
	 */
	Vector2D();

	/**
	 * \brief		Makes a vector with the entries x and y.
	 * \details		After this constructor is done, the entries in the vector will be x and y, in that order.
	 * \post		The vector's entries are x and y, in that order.
	 * \param		x	The 1st value in the vector.
	 * \param		y	The 2nd value in the vector.
	 */
	Vector2D( double x, double y );

	/**
	 * \brief		Makes a copy of the vector \a other.
	 * \details		After this constructor is done, the entries in this will match the entries in the vector \a other.
	 * \post		The entries in this vector match the entries in the vector \a other.
	 * \param		other	The vector to copy.
	 */
	Vector2D( const Vector2D& other );

	/**
	 * \brief		Makes a copy of the vector \a other.
	 * \details		The entries in this vector will be made to match the entries in the vector \a other.
	 * \post		The entries in this vector match the entries in the vector \a other.
	 * \param		other	The vector to copy.
	 * \return		A reference to this.
	 */
	Vector2D& operator=( const Vector2D& other );

	double& operator []( size_t idx );

	double operator []( size_t idx ) const;

	double euclideanNorm2() const;

	double euclideanNorm() const;

	/**
	 * \brief		Returns the dot product between this and \a other.
	 * \details		Computes the dot product \f$ \overrightarrow{this} \cdot \overrightarrow{other} \f$.
	 * \param		other	The vector to be dot producted with this.
	 * \return		The dot product \f$ \overrightarrow{this} \cdot \overrightarrow{other} \f$.
	 */
	double dot( const Vector2D& other ) const;

	bool normalize();

private:

	double mV[2];
};

class Matrix2x2
{
public:

	/**
	 *
	  */
	Matrix2x2();

	/**
	 *
	  */
	Matrix2x2( const Matrix2x2& other );

	/**
	 *
	  */
	Matrix2x2( const Vector2D& row1, const Vector2D& row2 );

	/**
	 *
	  */
	Matrix2x2( const double* values );

	/**
	 *
	  */
	Matrix2x2& operator =( const Matrix2x2& other );

	/**
	 *
	  */
	Vector2D getRow( size_t row ) const;

	/**
	 *
	  */
	double* getRow( size_t row );

	/**
	 *
	  */
	Vector2D getColumn( size_t col ) const;

	/**
	 *
	  */
	Vector2D operator []( size_t row ) const;

	/**
	 *
	  */
	double* operator []( size_t row );

	/**
	 *
	  */
	Matrix2x2 transpose() const;

	/**
	 *
	  */
	Matrix2x2 invert() const;

	/**
	 *
	  */
	double determinant() const;

	/**
	 *
	  */
	Vector2D matrixSolve( const Vector2D& b ) const;

	/**
	 *
	  */
	const double* begin() const;

	/**
	 *
	  */
	const double* end() const;
private:
	double mV[4];
};

class Vector3D
{
public:

	/**
	 *
	  */
	Vector3D();

	/**
	 *
	  */
	Vector3D( double x, double y, double z );

	/**
	 *
	  */
	Vector3D( const Vector3D& other );

	/**
	 *
	  */
	Vector3D& operator=( const Vector3D& other );

	/**
	 *
	  */
	double& operator []( size_t idx );

	/**
	 *
	  */
	double operator []( size_t idx ) const;

	/**
	 *
	  */
	double euclideanNorm2() const;

	/**
	 *
	  */
	double euclideanNorm() const;

	/**
	 *
	  */
	double dot( const Vector3D& other ) const;

	/**
	 *
	  */
	Vector3D cross( const Vector3D& other ) const;

	/**
	 *
	  */
	bool normalize();
private:
	double mV[3];
};

class Matrix3x3
{
public:

	/**
	 *
	  */
	Matrix3x3();

	/**
	 *
	  */
	Matrix3x3( const Matrix3x3& other );

	/**
	 *
	  */
	Matrix3x3( const Vector3D& row1, const Vector3D& row2, const Vector3D& row3 );

	/**
	 *
	  */
	Matrix3x3( const double* values );

	/**
	 *
	  */
	Matrix3x3& operator =( const Matrix3x3& other );

	/**
	 *
	  */
	Vector3D getRow( size_t row ) const;

	/**
	 *
	  */
	double* getRow( size_t row );

	/**
	 *
	  */
	Vector3D getColumn( size_t col ) const;

	/**
	 *
	  */
	Vector3D operator []( size_t row ) const;

	/**
	 *
	  */
	double* operator []( size_t row );

	/**
	 *
	  */
	Matrix3x3 transpose() const;

	/**
	 *
	  */
	Matrix3x3 invert() const;

	/**
	 *
	  */
	double determinant() const;

	/**
	 *
	  */
	Vector3D matrixSolve( const Vector3D& b ) const;

	/**
	 *
	  */
	const double* begin() const;

	/**
	 *
	  */
	const double* end() const;
private:
	double mV[9];
};

class VectorND
{
public:

	/**
	 *
	  */
	VectorND( int n );

	/**
	 *
	  */
	VectorND( int n, const double* x );

	/**
	 *
	  */
	VectorND( const VectorND& other );

	/**
	 *
	  */
	~VectorND();

	/**
	 *
	  */
	VectorND& operator=( const VectorND& other );

	/**
	 *
	  */
	int getNum() const;

	/**
	 *
	  */
	double& operator []( size_t idx );

	/**
	 *
	  */
	double operator []( size_t idx ) const;

	/**
	 *
	  */
	double euclideanNorm2() const;

	/**
	 *
	  */
	double euclideanNorm() const;

	/**
	 *
	  */
	double dot( const VectorND& other ) const;

	/**
	 *
	  */
	bool normalize();
private:
	int mN;
	double* mV;
};

class MatrixMxN
{
public:

	/**
	 *
	  */
	MatrixMxN( int m, int n ); // Creates a zero matrix

	/**
	 *
	  */
	MatrixMxN( const MatrixMxN& other );

	/**
	 *
	  */
	MatrixMxN( const MatrixMxN& A, const MatrixMxN& B,
			   const MatrixMxN& C, const MatrixMxN& D );

	/**
	 *
	  */
	MatrixMxN( int m, int n, const double* values );

	/**
	 *
	  */
	~MatrixMxN();

	/**
	 *
	  */
	MatrixMxN& operator =( const MatrixMxN& other );

	/**
	 *
	  */
	int getNumRows() const;

	/**
	 *
	  */
	int getNumCols() const;

	/**
	 *
	  */
	VectorND getRow( size_t row ) const;

	/**
	 *
	  */
	double* getRow( size_t row );

	/**
	 *
	  */
	VectorND getColumn( size_t col ) const;

	/**
	 *
	  */
	VectorND operator []( size_t row ) const;

	/**
	 *
	 */
	double* operator []( size_t row );

	/**
	 *
	 * rowend and colend are immediately AFTER the last row and column of the returned matrix.
	 */
	MatrixMxN getPiece( int rowstart, int rowend, int colstart, int colend ) const;

	/**
	 *
	 */
	MatrixMxN transpose() const;

	/**
	 *
	 */
	MatrixMxN invert() const;

	/**
	 *
	 */
	MatrixMxN switchVertical() const;

	/**
	 *
	 */
	MatrixMxN switchHorizontal() const;

	/**
	 *
	 */
	MatrixMxN invertUpperRight() const;

	/**
	 *
	 */
	MatrixMxN invertLowerRight() const;

	/**
	 *
	 */
	MatrixMxN invertUpperLeft() const;

	/**
	 *
	 */
	MatrixMxN invertLowerLeft() const;

	/**
	 *
	 */
	MatrixMxN operator +( const MatrixMxN& other ) const;

	/**
	 *
	 */
	MatrixMxN operator -( const MatrixMxN& other ) const;

	/**
	 *
	 */
	MatrixMxN operator *( const MatrixMxN& other ) const;

	/**
	 *
	 */
	MatrixMxN multiplyScalar( double s ) const;

	/**
	 *
	 */
	MatrixMxN transposeAndMultiply( const MatrixMxN& other ) const;

	/**
	 *
	 */
	MatrixMxN pointwiseMultiply( const MatrixMxN& other ) const;

	/**
	 *
	 */
	double dot( const MatrixMxN& other ) const;

	/**
	 *
	 */
	const double* begin() const;

	/**
	 *
	 */
	const double* end() const;
private:
	int mM;
	int mN;
	double* mV;
};


// operations in the global scope


/**
 */
Vector2D operator *( double s, const Vector2D& v );

/**
 */
Vector2D operator +( const Vector2D& a, const Vector2D& b );

/**
 */
Vector2D operator -( const Vector2D& a, const Vector2D& b );

/**
 */
Vector3D operator *( double s, const Vector3D& v );

/**
 */
Vector3D operator +( const Vector3D& a, const Vector3D& b );

/**
 */
Vector3D operator -( const Vector3D& a, const Vector3D& b );

/**
 */
VectorND operator *( double s, const VectorND& v );

/**
 */
VectorND operator +( const VectorND& a, const VectorND& b );

/**
 */
VectorND operator -( const VectorND& a, const VectorND& b );

/**
 */
double dot( const Vector2D& a, const Vector2D& b );

/**
 */
double dot( const Vector3D& a, const Vector3D& b );

/**
 */
Vector3D cross( const Vector3D& a, const Vector3D& b );

/**
 */
Matrix2x2 operator *( const Matrix2x2& A, const Matrix2x2& B );

/**
 */
Vector2D operator *( const Matrix2x2& A, const Vector2D& b );

/**
 */
Vector2D matrixSolve( const Matrix2x2& A, const Vector2D& b );

/**
 */
Matrix3x3 operator *( const Matrix3x3& A, const Matrix3x3& B );

/**
 */
Vector3D operator *( const Matrix3x3& A, const Vector3D& b );

/**
 */
Vector3D matrixSolve( const Matrix3x3& a, const Vector3D& b );

/**
 */
VectorND operator *( const MatrixMxN& A, const VectorND& b );

/**
 */
MatrixMxN operator *( double s, const MatrixMxN& A );

/**
 */
double dot( const MatrixMxN& A, const MatrixMxN& B );
