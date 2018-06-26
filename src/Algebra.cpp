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

#include "Algebra.hpp"


// Vector2D
Vector2D::Vector2D()
{
	mV[0] = 0;
	mV[1] = 0;
}
Vector2D::Vector2D( double x, double y )
{
	mV[0] = x;
	mV[1] = y;
}
Vector2D::Vector2D( const Vector2D& other )
{
	mV[0] = other.mV[0];
	mV[1] = other.mV[1];
}
Vector2D& Vector2D::operator=( const Vector2D& other )
{
	mV[0] = other.mV[0];
	mV[1] = other.mV[1];
	return *this;
}
double& Vector2D::operator []( size_t idx )
{
	return mV[idx];
}
double Vector2D::operator []( size_t idx ) const
{
	return mV[idx];
}
double Vector2D::euclideanNorm2() const
{
	return mV[0]*mV[0] + mV[1]*mV[1];
}
double Vector2D::euclideanNorm() const
{
	return sqrt( euclideanNorm2() );
}
double Vector2D::dot( const Vector2D& other ) const
{
	return mV[0]*other.mV[0] + mV[1]*other.mV[1];
}
bool Vector2D::normalize()
{
	double l = euclideanNorm();
	if (l==0) return false;
	mV[0] = mV[0]/l;
	mV[1] = mV[1]/l;
	return true;
}


// Matrix2x2
Matrix2x2::Matrix2x2()
{
	mV[0] = 1;
	mV[1] = 0;
	mV[2] = 0;
	mV[3] = 1;
}
Matrix2x2::Matrix2x2( const Matrix2x2& other )
{
	for (int i=0; i<4; i++) {
		mV[i] = other.mV[i];
	}
}
Matrix2x2::Matrix2x2( const Vector2D& row1, const Vector2D& row2 )
{
	mV[0] = row1[0];
	mV[1] = row1[1];
	mV[2] = row2[0];
	mV[3] = row2[1];
}
Matrix2x2::Matrix2x2( const double* values )
{
	for (int i=0; i<4; i++) {
		mV[i] = values[i];
	}
}
Matrix2x2& Matrix2x2::operator =( const Matrix2x2& other )
{
	for (int i=0; i<4; i++) {
		mV[i] = other.mV[i];
	}
	return *this;
}
Vector2D Matrix2x2::getRow( size_t row ) const
{
	return Vector2D( mV[2*row], mV[2*row+1] );
}
double* Matrix2x2::getRow( size_t row )
{
	return (double*)mV + 4*row;
}
Vector2D Matrix2x2::getColumn( size_t col ) const
{
	return Vector2D( mV[col], mV[col+2] );
}
Vector2D Matrix2x2::operator []( size_t row ) const
{
	return getRow(row);
}
double* Matrix2x2::operator []( size_t row )
{
	return getRow(row);
}
Matrix2x2 Matrix2x2::transpose() const
{
	return Matrix2x2( getColumn(0), getColumn(1) );
}
Matrix2x2 Matrix2x2::invert() const
{
	double det = determinant();
	double newvals[4];
	newvals[0] = mV[3] / det;
	newvals[1] = -mV[1] / det;
	newvals[2] = -mV[2] / det;
	newvals[3] = mV[0] / det;
	return Matrix2x2( newvals );
}
double Matrix2x2::determinant() const
{
	return mV[0]*mV[3] - mV[1]*mV[2];
}
Vector2D Matrix2x2::matrixSolve( const Vector2D& b ) const
{
	double det = determinant();
	double det1 = b[0]*mV[3] - b[1]*mV[1];
	double det2 = b[1]*mV[0] - b[0]*mV[2];
	return Vector2D( det1/det, det2/det );
}
const double* Matrix2x2::begin() const
{
    return (double*)mV;
}
const double* Matrix2x2::end() const
{
	return begin()+4;
}


// Vector3D
Vector3D::Vector3D()
{
	mV[0] = 0;
	mV[1] = 0;
	mV[2] = 0;
}
Vector3D::Vector3D( double x, double y, double z )
{
	mV[0] = x;
	mV[1] = y;
	mV[2] = z;
}
Vector3D::Vector3D( const Vector3D& other )
{
	mV[0] = other.mV[0];
	mV[1] = other.mV[1];
	mV[2] = other.mV[2];
}
Vector3D& Vector3D::operator=( const Vector3D& other )
{
	mV[0] = other.mV[0];
	mV[1] = other.mV[1];
	mV[2] = other.mV[2];
	return *this;
}
double& Vector3D::operator[]( size_t idx )
{
	return mV[idx];
}
double Vector3D::operator[]( size_t idx ) const
{
	return mV[idx];
}
double Vector3D::euclideanNorm2() const
{
	return mV[0]*mV[0] + mV[1]*mV[1] + mV[2]*mV[2];
}
double Vector3D::euclideanNorm() const
{
	return sqrt( euclideanNorm2() );
}
double Vector3D::dot( const Vector3D& other ) const
{
	return mV[0]*other.mV[0] + mV[1]*other.mV[1] + mV[2]*other.mV[2];
}
Vector3D Vector3D::cross( const Vector3D& other ) const
{
	return Vector3D( mV[1]*other.mV[2] - mV[2]*other.mV[1],
					 mV[2]*other.mV[0] - mV[0]*other.mV[2],
					 mV[0]*other.mV[1] - mV[1]*other.mV[0] );
}
bool Vector3D::normalize()
{
	double l = euclideanNorm();
	if (l==0) return false;
	mV[0] = mV[0]/l;
	mV[1] = mV[1]/l;
	mV[2] = mV[2]/l;
	return true;
}


// Matrix3x3
Matrix3x3::Matrix3x3()
{
	for (int i=0; i<9; i++) {
		mV[i] = 0;
	}
	mV[0] = 1;
	mV[4] = 1;
	mV[8] = 1;
}
Matrix3x3::Matrix3x3( const Matrix3x3& other )
{
	for (int i=0; i<9; i++) {
		mV[i] = other.mV[i];
	}
}
Matrix3x3::Matrix3x3( const Vector3D& row1, const Vector3D& row2, const Vector3D& row3 )
{
	for (int i=0; i<3; i++) {
		mV[i] = row1[i];
		mV[i+3] = row2[i];
		mV[i+6] = row3[i];
	}
}
Matrix3x3::Matrix3x3( const double* values )
{
	for (int i=0; i<9; i++) {
		mV[i] = values[i];
	}
}
	
Matrix3x3& Matrix3x3::operator =( const Matrix3x3& other )
{
	for (int i=0; i<9; i++) {
		mV[i] = other.mV[i];
	}
	return *this;
}
Vector3D Matrix3x3::getRow( size_t row ) const
{
	return Vector3D( mV[3*row], mV[3*row+1], mV[3*row+2] );
}
double* Matrix3x3::getRow( size_t row )
{
    return (double*)mV + 3*row;
}
Vector3D Matrix3x3::getColumn( size_t col ) const
{
	return Vector3D( mV[col], mV[col+3], mV[col+6] );
}
Vector3D Matrix3x3::operator []( size_t row ) const
{
	return getRow(row);
}
double* Matrix3x3::operator []( size_t row )
{
	return getRow(row);
}
Matrix3x3 Matrix3x3::transpose() const
{
    return Matrix3x3( getColumn(0), getColumn(1), getColumn(2) );
}
Matrix3x3 Matrix3x3::invert() const
{
	double det = determinant();
	if (det==0) throw -1;
	return Matrix3x3( Vector3D( (mV[4]*mV[8]-mV[5]*mV[7])/det,
								(mV[5]*mV[6]-mV[3]*mV[8])/det,
								(mV[3]*mV[7]-mV[4]*mV[6])/det ),
					  Vector3D( (mV[2]*mV[7]-mV[1]*mV[8])/det,
								(mV[0]*mV[8]-mV[2]*mV[6])/det,
								(mV[1]*mV[6]-mV[0]*mV[7])/det ),
					  Vector3D( (mV[1]*mV[5]-mV[2]*mV[4])/det,
								(mV[2]*mV[3]-mV[0]*mV[5])/det,
								(mV[0]*mV[4]-mV[1]*mV[3])/det ) );
}
double Matrix3x3::determinant() const
{
	return mV[0]*(mV[4]*mV[8]-mV[5]*mV[7]) +
		   mV[1]*(mV[5]*mV[6]-mV[3]*mV[8]) +
		   mV[2]*(mV[3]*mV[7]-mV[4]*mV[6]);
}
Vector3D Matrix3x3::matrixSolve( const Vector3D& b ) const
{
	double det = determinant();
	double det1 = b[0]*(mV[4]*mV[8]-mV[5]*mV[7]) + b[1]*(mV[5]*mV[6]-mV[3]*mV[8]) + b[2]*(mV[3]*mV[7]-mV[4]*mV[6]);
	double det2 = b[0]*(mV[5]*mV[6]-mV[3]*mV[8]) + b[1]*(mV[0]*mV[8]-mV[2]*mV[6]) + b[2]*(mV[2]*mV[3]-mV[0]*mV[5]);
	double det3 = b[0]*(mV[3]*mV[7]-mV[4]*mV[6]) + b[1]*(mV[1]*mV[6]-mV[0]*mV[7]) + b[2]*(mV[0]*mV[4]-mV[1]*mV[3]);
	return Vector3D( det1/det, det2/det, det3/det );
}
const double* Matrix3x3::begin() const
{
	return (double*)mV;
}
const double* Matrix3x3::end() const
{
	return begin()+9;
}


// VectorND
VectorND::VectorND( int n )
{
	mN = n;
	mV = new double[n];
	for (int i=0; i<n; i++) {
		mV[i] = 0;
	}
}
VectorND::VectorND( int n, const double* x )
{
	mN = n;
	mV = new double[n];
	for (int i=0; i<n; i++) {
		mV[i] = x[i];
	}
}
VectorND::VectorND( const VectorND& other )
{
	mN = other.mN;
	mV = new double[mN];
	for (int i=0; i<mN; i++) {
		mV[i] = other.mV[i];
	}
}
VectorND::~VectorND()
{
	delete[] mV;
}
VectorND& VectorND::operator=( const VectorND& other )
{
	mN = other.mN;
	mV = new double[mN];
	for (int i=0; i<mN; i++) {
		mV[i] = other.mV[i];
	}
	return *this;
}
int VectorND::getNum() const
{
	return mN;
}
double& VectorND::operator []( size_t idx )
{
	return mV[idx];
}
double VectorND::operator []( size_t idx ) const
{
	return mV[idx];
}
double VectorND::euclideanNorm2() const
{
	double s = 0;
	for (int i=0; i<mN; i++) {
		s += mV[i]*mV[i];
	}
	return s;
}
double VectorND::euclideanNorm() const
{
	return sqrt( euclideanNorm2() );
}
double VectorND::dot( const VectorND& other ) const
{
	if (mN!=other.mN) throw -1;
	double s = 0;
	for (int i=0; i<mN; i++) {
		s += mV[i]*other.mV[i];
	}
	return s;
}
bool VectorND::normalize()
{
	double l = euclideanNorm();
	if (l==0) return false;
	for (int i=0; i<mN; i++) {
		mV[i] /= l;
	}
	return true;
}


// MatrixMxN
MatrixMxN::MatrixMxN( int m, int n )
{
	mM = m;
	mN = n;
	int mn = m*n;
	mV = new double[mn];
	for (int i=0; i<mn; i++) {
		mV[i] = 0;
	}
}
MatrixMxN::MatrixMxN( const MatrixMxN& other )
{
	mM = other.mM;
	mN = other.mN;
	mV = new double[mM*mN];
	for (int i=0; i<mM*mN; i++) {
		mV[i] = other.mV[i];
	}
}
MatrixMxN::MatrixMxN( int m, int n, const double* values )
{
	mM = m;
	mN = n;
	mV = new double[m*n];
	for (int i=0; i<m*n; i++) {
		mV[i] = values[i];
	}
}
MatrixMxN::MatrixMxN( const MatrixMxN& A, const MatrixMxN& B,
					  const MatrixMxN& C, const MatrixMxN& D )
{
	if ( A.mM!=B.mM || C.mM!=D.mM ||
		 A.mN!=C.mN || B.mN!=D.mN ) throw -1;
	mM = A.mM + C.mM;
	mN = A.mN + B.mN;
	mV = new double[mM*mN];
	for (int i=0; i<A.mM; i++) {
		for (int j=0; j<A.mN; j++) {
			mV[i*mN+j] = A.mV[i*A.mN+j];
		}
		for (int j=0; j<B.mN; j++) {
			mV[i*mN+A.mN+j] = B.mV[i*B.mN+j];
		}
	}
	for (int i=0; i<C.mM; i++) {
		for (int j=0; j<C.mN; j++) {
			mV[(i+A.mM)*mN+j] = C.mV[i*C.mN+j];
		}
		for (int j=0; j<B.mN; j++) {
			mV[(i+A.mM)*mN+A.mN+j] = D.mV[i*D.mN+j];
		}
	}
	int b = 3;
}
MatrixMxN::~MatrixMxN()
{
	delete[] mV;
}
MatrixMxN& MatrixMxN::operator =( const MatrixMxN& other )
{
	mM = other.mM;
	mN = other.mN;
	delete[] mV;
	mV = new double[mM*mN];
	for (int i=0; i<mM*mN; i++) {
		mV[i] = other.mV[i];
	}
	return *this;
}
int MatrixMxN::getNumRows() const
{
	return mM;
}
int MatrixMxN::getNumCols() const
{
	return mN;
}
VectorND MatrixMxN::getRow( size_t row ) const
{
	VectorND ret( mN );
	for (int i=0; i<mN; i++) {
		ret[i] = mV[row*mN+i];
	}
	return ret;
}
double* MatrixMxN::getRow( size_t row )
{
    return (double*)mV + mN*row;
}
VectorND MatrixMxN::getColumn( size_t col ) const
{
	VectorND ret( mM );
	for (int i=0; i<mM; i++) {
		ret[i] = mV[i*mN+col];
	}
	return ret;
}
VectorND MatrixMxN::operator []( size_t row ) const
{
	return getRow(row);
}
double* MatrixMxN::operator []( size_t row )
{
	return getRow(row);
}
MatrixMxN MatrixMxN::getPiece( int rowstart, int rowend, int colstart, int colend ) const
{
	int newN = colend-colstart;
	MatrixMxN ret( rowend-rowstart, newN );
	for (int i=rowstart; i<rowend; i++) {
		for (int j=colstart; j<colend; j++) {
			ret.mV[(i-rowstart)*newN+j-colstart] = mV[i*mN+j];
		}
	}
	return ret;
}
MatrixMxN MatrixMxN::transpose() const
{
	MatrixMxN ret( mN, mM );
	for (int i=0; i<mM; i++) {
		for (int j=0; j<mN; j++) {
			ret.mV[i+j*mM] = ret.mV[i*mN+j];
		}
	}
	return ret;
}
MatrixMxN MatrixMxN::invert() const
{
	if (mN!=mM) throw -1;
	if (mM==1) {
		MatrixMxN ret(1,1);
		ret.mV[0] = 1.0 / mV[0];
		return ret;
	}
	if (mM==2) {
		double ad_bc = mV[0]*mV[3] - mV[1]*mV[2];
		double vals[4] = { mV[3]/ad_bc, -mV[1]/ad_bc, -mV[2]/ad_bc, mV[0]/ad_bc };
		return MatrixMxN(2,2,vals);
	}
	int newM = mM/2;
	MatrixMxN Ainv = getPiece(0,newM,0,newM).invert();
	MatrixMxN B = getPiece(0,newM,newM,mM);
	MatrixMxN C = getPiece(newM,mM,0,newM);
	MatrixMxN D = getPiece(newM,mM,newM,mM);
	MatrixMxN CAinv = C*Ainv;
	MatrixMxN AinvB = Ainv*B;
	MatrixMxN biginv = (D - CAinv*B).invert();
	MatrixMxN biginvext = biginv*CAinv;
	return MatrixMxN(Ainv + AinvB*biginvext, -1*AinvB*biginv, -1*biginvext, biginv);
}
MatrixMxN MatrixMxN::switchVertical() const
{
	MatrixMxN ret( mM, mN );
	for (int i=0; i<mM; i++) {
		for (int j=0; j<mN; j++) {
			ret.mV[(mM-1-i)*mN+j] = mV[i*mN+j];
		}
	}
	return ret;
}
MatrixMxN MatrixMxN::switchHorizontal() const
{
	MatrixMxN ret( mM, mN );
	for (int i=0; i<mM; i++) {
		for (int j=0; j<mN; j++) {
			ret.mV[i*mN+(mN-1-j)] = mV[i*mN+j];
		}
	}
	return ret;
}
MatrixMxN MatrixMxN::invertUpperRight() const
{
	if (mN!=mM) throw -1;
	MatrixMxN ret( mM, mN );
	for (int i=0; i<mN; i++) {
		ret.mV[(mN+1)*i] = 1;
	}
	// for r = last row to 1st row
	for (int r=mM-1; r>=0; r--) {
		int a = r*(mN+1);
		int b = a-r;
		// ret.rowr = ret.rowr / u[r,r];
		for (int i=r; i<mM; i++) {
			ret.mV[b+i] /= mV[a];
		}
		// ret.rowr -= sum(i=r+1 to lastrow)( u[r,i]*ret.rowi )
		for (int j=r+1; j<mN; j++) {
			int c = b+j;
			for (int i=r+1; i<=j; i++) {
				ret.mV[c] -= mV[b+i]*ret.mV[i*mN+j] / mV[a];
			}
		}
	}
	return ret;
}
MatrixMxN MatrixMxN::invertLowerRight() const
{
	return switchVertical().invertUpperRight().switchHorizontal();
}
MatrixMxN MatrixMxN::invertUpperLeft() const
{
	return switchHorizontal().invertUpperRight().switchVertical();
}
MatrixMxN MatrixMxN::invertLowerLeft() const
{
	return switchVertical().switchHorizontal().invertUpperRight().switchHorizontal().switchVertical();
}
MatrixMxN MatrixMxN::operator +( const MatrixMxN& other ) const
{
	if (mN!=other.mN || mM!=other.mM) throw -1;
	MatrixMxN ret( mM, mN );
	for (int i=0; i<mM*mN; i++) {
		ret.mV[i] = mV[i] + other.mV[i];
	}
	return ret;
}
MatrixMxN MatrixMxN::operator -( const MatrixMxN& other ) const
{
	if (mN!=other.mN || mM!=other.mM) throw -1;
	MatrixMxN ret( mM, mN );
	for (int i=0; i<mM*mN; i++) {
		ret.mV[i] = mV[i] - other.mV[i];
	}
	return ret;
}
MatrixMxN MatrixMxN::operator *( const MatrixMxN& other ) const
{
	if (mN!=other.mM) throw -1;
	MatrixMxN ret( mM, other.mN );
	for (int i=0; i<mM; i++) {
		for (int j=0; j<other.mN; j++) {
			for (int k=0; k<mN; k++) {
				// ret[i,j] += this[i,k]*other[k,j]
				ret.mV[i*other.mN+j] += mV[i*mN+k]*other.mV[k*other.mN+j];
			}
		}
	}
	return ret;
}
MatrixMxN MatrixMxN::multiplyScalar( double s ) const
{
	MatrixMxN ret( mM, mN );
	for (int i=0; i<mM*mN; i++) {
		ret.mV[i] = s*mV[i];
	}
	return ret;
}
MatrixMxN MatrixMxN::transposeAndMultiply( const MatrixMxN& other ) const
{
	if (mM!=other.mM) throw -1;
	MatrixMxN ret( mN, other.mN );
	for (int i=0; i<mN; i++) {
		for (int j=0; j<other.mN; j++) {
			for (int k=0; k<mM; k++) {
				// ret[i,j] += this[k,i]*other[k,j]
				ret.mV[i*other.mN+j] += mV[k*mN+i]*other.mV[k*other.mN+j];
			}
		}
	}
	return ret;
}
MatrixMxN MatrixMxN::pointwiseMultiply( const MatrixMxN& other ) const
{
	if (mM!=other.mM || mN!=other.mN) throw -1;
	MatrixMxN ret( mM, mN );
	for (int i=0; i<mM*mN; i++) {
		ret.mV[i] = mV[i]*other.mV[i];
	}
	return ret;
}
double MatrixMxN::dot( const MatrixMxN& other ) const
{
	if (mM!=other.mM || mN!=other.mN) throw -1;
	double ret = 0;
	for (int i=0; i<mM*mN; i++) {
		ret += mV[i]*other.mV[i];
	}
	return ret;
}
const double* MatrixMxN::begin() const
{
	return (double*)mV;
}
const double* MatrixMxN::end() const
{
	return begin() + mM*mN;
}


// operations in the global scope
Vector2D operator *( double s, const Vector2D& v )
{
	return Vector2D( s*v[0], s*v[1] );
}
Vector2D operator +( const Vector2D& a, const Vector2D& b )
{
	return Vector2D( a[0]+b[0], a[1]+b[1] );
}
Vector2D operator -( const Vector2D& a, const Vector2D& b )
{
	return Vector2D( a[0]-b[0], a[1]-b[1] );
}
Vector3D operator *( double s, const Vector3D& v )
{
	return Vector3D( s*v[0], s*v[1], s*v[2] );
}
Vector3D operator +( const Vector3D& a, const Vector3D& b )
{
	return Vector3D( a[0]+b[0], a[1]+b[1], a[2]+b[2] );
}
Vector3D operator -( const Vector3D& a, const Vector3D& b )
{
	return Vector3D( a[0]-b[0], a[1]-b[1], a[2]-b[2] );
}
VectorND operator *( double s, const VectorND& v )
{
	int n = v.getNum();
	double* retvals = new double[n];
	for (int i=0; i<n; i++) {
		retvals[i] = s*v[i];
	}
	VectorND ret( n, retvals );
	delete[] retvals;
	return ret;
}
VectorND operator +( const VectorND& a, const VectorND& b )
{
	int n = a.getNum();
	if (b.getNum()!=n) throw -1;
	double* retvals = new double[n];
	for (int i=0; i<n; i++) {
		retvals[i] = a[i]+b[i];
	}
	VectorND ret( n, retvals );
	delete[] retvals;
	return ret;
}
VectorND operator -( const VectorND& a, const VectorND& b )
{
	int n = a.getNum();
	if (b.getNum()!=n) throw -1;
	double* retvals = new double[n];
	for (int i=0; i<n; i++) {
		retvals[i] = a[i]-b[i];
	}
	VectorND ret( n, retvals );
	delete[] retvals;
	return ret;
}
double dot( const Vector2D& a, const Vector2D& b )
{
	return a.dot(b);
}
double dot( const Vector3D& a, const Vector3D& b )
{
	return a.dot(b);
}
Vector3D cross( const Vector3D& a, const Vector3D& b )
{
	return a.cross(b);
}
Matrix2x2 operator *( const Matrix2x2& a, const Matrix2x2& b )
{
	return Matrix2x2( Vector2D( a.getRow(0).dot(b.getColumn(0)), a.getRow(0).dot(b.getColumn(1)) ),
					  Vector2D( a.getRow(1).dot(b.getColumn(0)), a.getRow(1).dot(b.getColumn(1)) ) );
}
Vector2D operator *( const Matrix2x2& a, const Vector2D& b )
{
	return Vector2D( a.getRow(0).dot(b), a.getRow(1).dot(b) );
}
Vector2D matrixSolve( const Matrix2x2& a, const Vector2D& b )
{
	return a.matrixSolve(b);
}
Matrix3x3 operator *( const Matrix3x3& a, const Matrix3x3& b )
{
	return Matrix3x3( Vector3D( a.getRow(0).dot(b.getColumn(0)),
								a.getRow(0).dot(b.getColumn(1)),
								a.getRow(0).dot(b.getColumn(2)) ),
					  Vector3D( a.getRow(1).dot(b.getColumn(0)),
								a.getRow(1).dot(b.getColumn(1)),
								a.getRow(1).dot(b.getColumn(2)) ),
					  Vector3D( a.getRow(2).dot(b.getColumn(0)),
								a.getRow(2).dot(b.getColumn(1)),
								a.getRow(2).dot(b.getColumn(2)) ) );
}
Vector3D operator *( const Matrix3x3& a, const Vector3D& b )
{
	return Vector3D( a.getRow(0).dot(b), a.getRow(1).dot(b), a.getRow(2).dot(b) );
}
Vector3D matrixSolve( const Matrix3x3& a, const Vector3D& b )
{
	return a.matrixSolve(b);
}
VectorND operator *( const MatrixMxN& a, const VectorND& b )
{
	int m = a.getNumRows();
	double* retvals = new double[m];
	for (int i=0; i<m; i++) {
		retvals[i] = a.getRow(i).dot(b);
	}
	VectorND ret( m, retvals );
	delete[] retvals;
	return ret;
}
MatrixMxN operator *( double s, const MatrixMxN& A )
{
	return A.multiplyScalar( s );
}
double dot( const MatrixMxN& A, const MatrixMxN& B )
{
	return A.dot(B);
}