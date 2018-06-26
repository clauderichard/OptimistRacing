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

/* This file contains definitions for Bernstein polynomials,
 * a specific type of Bezier patches,
 * and grids of the above type of Bezier patches.
 */

#pragma once
#include "Algebra.hpp"

// Stores information about all the (D+1) Berstein polynomials of degree D (denoted Bi(t) for i=0 to D),
//   so you can use this object to efficiently compute their values and derivatives at arbitrary values of t.
// NOTE: The coefficient in front of each polynomial is 1, we're not using the Pascal triangle thing in this object.
class BernsteinPolynomial
{

public:
	BernsteinPolynomial( unsigned int degree );
	~BernsteinPolynomial();
	// Returns the degree of the polynomial
	unsigned int getD() const;
	// Returns a matrix of values and derivatives of each polynomial.
	// First index  i = which polynomial.				From 0 to D
	// Second index j = how many times differentiated.	From 0 to D
	MatrixMxN compute( double t ) const;
	// For this one, it only returns the first column of the above matrix.
	MatrixMxN computeFOnly( double t ) const;

private:
	// highest power of t in the expression of B(t)
	unsigned int mD;
	// This is like a 3-d array. The coefficients are all integers.
	// First index  i = which of the mDegree polynomials.	From 0 to D
	// Second index j = power of t.							From 0 to D-i
	// Third index  k = power of (1-t).						From 0 to i
	// The number of times differentiated is implied by the three indices.
	// The indices used in the implementation are are i, j*(i+1)+k
	int** mB;

};

// This is a function f(x,y) for x,y from 0 to 1.
// The matrix K has all the coefficients.
// f(x,y) = sum(over i and j)( Bi(x)*Bj(y)*Kij )
//   where B are degree (2n-1) Bernstein Polynomials
class BezierPatch
{
public:
	// K will be all zero in this constructor.
	BezierPatch( const BernsteinPolynomial* BP );
	// The argument matrices have to be in accordance with the specified n.
	BezierPatch( const BernsteinPolynomial* BP, MatrixMxN K );
	// Specify the value and some first, second etc derivatives at each corner.
	// Each matrix has the same format as the F returned in compute(x,y).
	// BP must have an odd degree so K can be a 2n*2n matrix, where 2n=D+1.
	// BTildaInv0 is the relevant quarter of BTilda0^-1. Same for BTildaInv1.
	BezierPatch( const BernsteinPolynomial* BP,
				 const MatrixMxN& BTildaInv0,
				 const MatrixMxN& BTildaInv1,
				 const MatrixMxN& f00, const MatrixMxN& f01,
				 const MatrixMxN& f10, const MatrixMxN& f11 );
	~BezierPatch();
	
	// Returns mK (see below)
	const MatrixMxN& getK() const;
	// Returns the Berstein polynomial object that this uses.
	const BernsteinPolynomial* getBP() const;
	// x and y should both be between 0 and 1.
	// Returns the value and some derivatives of f at (x,y).
	// For example, when n = 2, it returns
	//   [ f, fy, fyy, fyyy;
	//     fx, fxy, fxyy, fxyyy;
	//     fxx, fxxy, fxxyy, fxxyyy;
	//     fxxx, fxxxy, fxxxyy, fxxxyyy ]
	MatrixMxN compute( double x, double y ) const;
	// Returns the topleft value in the above matrix.
	// computeFOnly(x,y) is more efficient than compute(x,y).
	double computeFOnly( double x, double y ) const;

private:
	const BernsteinPolynomial* mBP;
	MatrixMxN mK; // K[i][j] = coefficient for Bi(x)*Bj(y)
};


// This represents a grid where each cell is a BezierPatch.
// Let 2n-1 = degree of the BernsteinPolynomial.
// Then the whole grid will be a function f:R^2->R
//   that is C^n (differentiable n times) everywhere
//   including on the edges between cells.
class BezierPatchGrid
{
public:
	// corners is ordered in x = 0 to numCellsX-1, then by y.
	//   so corners[2] can mean x=2,y=0
	// In this constructor, BP must have odd degree.
	BezierPatchGrid( const BernsteinPolynomial* BP,
					 double gridHx, double gridHy,
					 unsigned int numCellsX, unsigned int numCellsY,
					 MatrixMxN** corners );
	~BezierPatchGrid();
	double getGridHX() const;
	double getGridHY() const;
	unsigned int getNumCellsX() const;
	unsigned int getNumCellsY() const;
	const BezierPatch& getPatch( unsigned int x, unsigned int y ) const;
	MatrixMxN compute( double x, double y ) const;
	double computeFOnly( double x, double y ) const;
private:
	const BernsteinPolynomial* mBP;
	double mGridHx;
	double mGridHy;
	unsigned int mNumCellsX;
	unsigned int mNumCellsY;
	// 1D array of pointers internally, but representing a 2D-array.
	BezierPatch** mPatches;
	// This is used in the compute() function
	int mN;
	MatrixMxN mGridHMatrix;
};