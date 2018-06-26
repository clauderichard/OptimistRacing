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

#include "Bezier.hpp"


// BernsteinPolynomial
BernsteinPolynomial::BernsteinPolynomial( unsigned int degree )
{
	mD = degree;
	mB = new int*[mD+1];
	for (unsigned int i=0; i<=mD; i++) {
		mB[i] = new int[(i+1)*(mD+1-i)];
		// Fill last corner
		int firstcol = (i+1)*(mD-i);
		mB[i][firstcol+i] = 1; // 
		// Fill last row
		for (int j=i-1; j>=0; j--) {
			mB[i][firstcol+j] = - mB[i][firstcol+j+1]*(j+1);
		}
		// Fill the other rows in order
		for (int k=mD-i-1; k>=0; k--) {
			int firstcol = (i+1)*k;
			mB[i][firstcol+i] = mB[i][firstcol+2*i+1]*(k+1);
			for (int j=i-1; j>=0; j--) {
				mB[i][firstcol+j] = mB[i][firstcol+j+i+1]*(k+1) - mB[i][firstcol+j+1]*(j+1);
			}
		}
	}
}
BernsteinPolynomial::~BernsteinPolynomial()
{
	for (unsigned int i=0; i<=mD; i++) {
		delete[] mB[i];
	}
	delete[] mB;
}
unsigned int BernsteinPolynomial::getD() const
{
	return mD;
}
MatrixMxN BernsteinPolynomial::compute( double t ) const
{
	int l = (mD+1)*(mD+1);
	double* ret = new double[l];
	for (int i=0; i<l; i++) {
		ret[i] = 0;
	}
	double topt = 1;
	// for each column of T
	for (unsigned int i=0; i<=mD; i++) {
		double valt = topt;
		// for each row of T
		for (unsigned int j=0; j<=mD-i; j++) {
			int a = mD-i-j;
			int b = i+j;
			// for every valid Bk matrix
			for (unsigned int k=i; k<=mD-j; k++) {
				// ret[k][mD-i-j] += valt*Bk[j][i]
				ret[k*(mD+1)+a] += valt*mB[k][j*k+b];
			}
			valt *= t;
		}
		topt *= (1-t);
	}
	MatrixMxN retmatrix( mD+1, mD+1, ret );
	delete[] ret;
	return retmatrix;
}
MatrixMxN BernsteinPolynomial::computeFOnly( double t ) const
{
	int l = mD+1;
	double* ret = new double[l];
	for (int i=0; i<l; i++) {
		ret[i] = 0;
	}
	double topt = 1;
	// for each column of T
	for (unsigned int i=0; i<=mD; i++) {
		double valt = topt;
		unsigned int j=mD-i;
		for (int k=0; k<j; k++) {
			valt *= t;
		}
		// ret[i][1] += valt*Bi[j][i]
		ret[i] += valt*mB[i][j*i+mD];
		topt *= (1-t);
	}
	MatrixMxN retmatrix( l, 1, ret );
	delete[] ret;
	return retmatrix;
}


// BezierPatch
BezierPatch::BezierPatch( const BernsteinPolynomial* BP )
	: mBP( BP )
	, mK( BP->getD()+1, BP->getD()+1 )
{
}
BezierPatch::BezierPatch( const BernsteinPolynomial* BP, MatrixMxN K )
	: mBP( BP )
	, mK( K )
{
}
BezierPatch::BezierPatch( const BernsteinPolynomial* BP,
						  const MatrixMxN& BTildaInv0,
						  const MatrixMxN& BTildaInv1,
						  const MatrixMxN& f00, const MatrixMxN& f01,
						  const MatrixMxN& f10, const MatrixMxN& f11 )
	: mBP( BP )
	, mK( BTildaInv1.transposeAndMultiply(f11) * BTildaInv1,
		  BTildaInv1.transposeAndMultiply(f10) * BTildaInv0,
		  BTildaInv0.transposeAndMultiply(f01) * BTildaInv1,
		  BTildaInv0.transposeAndMultiply(f00) * BTildaInv0)
{
	if ( BP->getD()+1 != mK.getNumRows() || BP->getD()+1 != mK.getNumCols() ) throw -1;
}
BezierPatch::~BezierPatch()
{
}
const MatrixMxN& BezierPatch::getK() const
{
	return mK;
}
const BernsteinPolynomial* BezierPatch::getBP() const
{
	return mBP;
}
MatrixMxN BezierPatch::compute( double x, double y ) const
{
	return mBP->compute(x).transposeAndMultiply(mK) * mBP->compute(y);
}
double BezierPatch::computeFOnly( double x, double y ) const
{
	MatrixMxN ret = mBP->computeFOnly(x).transposeAndMultiply(mK) * mBP->computeFOnly(y);
	if (ret.getNumCols()!=1 || ret.getNumRows()!=1) throw -1;
	return ret[0][0];
}


// BezierPatchGrid
BezierPatchGrid::BezierPatchGrid( const BernsteinPolynomial* BP,
								  double gridHx, double gridHy,
								  unsigned int numCellsX, unsigned int numCellsY,
								  MatrixMxN** corners )
	: mGridHMatrix(1,1)
{
	int d = BP->getD();
	if (d%2==0) throw -1;
	mN = (d+1)/2;
	mBP = BP;
	mGridHx = gridHx;
	mGridHy = gridHy;
	mNumCellsX = numCellsX;
	mNumCellsY = numCellsY;
	mPatches = new BezierPatch*[numCellsX*numCellsY];
	MatrixMxN BTildaInv0 = BP->compute(0).getPiece(mN,2*mN,0,mN).invertLowerRight();
	MatrixMxN BTildaInv1 = BP->compute(1).getPiece(0,mN,0,mN).invertUpperRight();
	double* dou = new double[mN*mN];
	double top = 1;
	for (int i=0; i<mN; i++) {
		double val = top;
		for (int j=0; j<mN; j++) {
			dou[i*mN+j] = val;
			val *= mGridHy;
		}
		top *= mGridHx;
	}
	MatrixMxN fmult( mN, mN, dou );

	for (int i=0; i<numCellsX; i++) {
		for (int j=0; j<numCellsY; j++) {
			int i00 = i+j*(numCellsX+1);
			int i01 = i+(j+1)*(numCellsX+1);
			mPatches[i+j*numCellsX] = new BezierPatch( BP, BTildaInv0, BTildaInv1,
				corners[i00]->pointwiseMultiply(fmult), corners[i01]->pointwiseMultiply(fmult),
				corners[i00+1]->pointwiseMultiply(fmult), corners[i01+1]->pointwiseMultiply(fmult) );
		}
	}
	// Make mGridHMatrix
	top = 1;
	for (int i=0; i<mN; i++) {
		double val = top;
		for (int j=0; j<mN; j++) {
			dou[i*mN+j] = val;
			val /= mGridHy;
		}
		top /= mGridHx;
	}
	mGridHMatrix = MatrixMxN( mN, mN, dou );
	delete[] dou;
}
BezierPatchGrid::~BezierPatchGrid()
{
	delete[] mPatches;
}
double BezierPatchGrid::getGridHX() const
{
	return mGridHx;
}
double BezierPatchGrid::getGridHY() const
{
	return mGridHy;
}
unsigned int BezierPatchGrid::getNumCellsX() const
{
	return mNumCellsX;
}
unsigned int BezierPatchGrid::getNumCellsY() const
{
	return mNumCellsY;
}
const BezierPatch& BezierPatchGrid::getPatch( unsigned int x, unsigned int y ) const
{
	return *(mPatches[x+y*mNumCellsX]);
}
MatrixMxN BezierPatchGrid::compute( double x, double y ) const
{
	int xfloor = floor(x/mGridHx);
	int yfloor = floor(y/mGridHy);
	int xin = xfloor;
	int yin = yfloor;
	if (xin<0) xin=0;
	if (yin<0) yin=0;
	if (xin>=mNumCellsX) xin = mNumCellsX-1;
	if (yin>=mNumCellsY) yin = mNumCellsY-1;
	MatrixMxN patchResult = getPatch(xin,yin).compute( x/mGridHx-xin, y/mGridHy-yin );
	return patchResult.getPiece(0,mN,0,mN).pointwiseMultiply( mGridHMatrix );
}
double BezierPatchGrid::computeFOnly( double x, double y ) const
{
	int xfloor = floor(x/mGridHx);
	int yfloor = floor(y/mGridHy);
	int xin = xfloor;
	int yin = yfloor;
	if (xin<0) xin=0;
	if (yin<0) yin=0;
	if (xin>=mNumCellsX) xin = mNumCellsX-1;
	if (yin>=mNumCellsY) yin = mNumCellsY-1;
	return getPatch(xin,yin).computeFOnly( x/mGridHx-xin, y/mGridHy-yin );
}