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

#include "Primitive.hpp"
#include "Algebra.hpp"
#include "Grid.hpp"
#include <GL\glew.h>
#include <GL\freeglut.h>

//WireSphereRenderer::WireSphereRenderer( int numSlices, int numStacks )
//	: mNumSlices( numSlices )
//	, mNumStacks( numStacks )
//{
//}
//WireSphereRenderer::~WireSphereRenderer()
//{
//}
//void WireSphereRenderer::glRender()
//{
//	glBegin( GL_QUADS );
//	for (int i=0; i<mNumSlices; i++) {
//		double theta1 = i*2*M_PI/mNumSlices;
//		double theta2 = (i+1)*2*M_PI/mNumSlices;
//		double costheta1 = cos(theta1);
//		double costheta2 = cos(theta2);
//		double sintheta1 = sin(theta1);
//		double sintheta2 = sin(theta2);
//		for (int j=0; j<mNumStacks; j++) {
//			double phi1 = j*M_PI/mNumStacks;
//			double phi2 = (j+1)*M_PI/mNumStacks;
//			double sinphi1 = sin(phi1);
//			double sinphi2 = sin(phi2);
//			double cosphi1 = cos(phi1);
//			double cosphi2 = cos(phi2);
//			glVertex3d( costheta1*sinphi1, sintheta1*sinphi1, cosphi1 );
//			glVertex3d( costheta1*sinphi2, sintheta1*sinphi2, cosphi2 );
//			glVertex3d( costheta2*sinphi2, sintheta2*sinphi2, cosphi2 );
//			glVertex3d( costheta2*sinphi1, sintheta2*sinphi1, cosphi1 );
//		}
//	}
//	glEnd(); // GL_LINES
//}


Primitive::Primitive()
{
}
Primitive::~Primitive()
{
}
void Primitive::drawTriangles( const Vector3D& centerVector,
		const Vector3D* outerVectors )
{
	// TODO: implement this
	//glVertex3d( x2, -yt2, zb2 );
	//glVertex3d( 0.0, 0.0, radius1 );
	//Vector3D norm = (v2-v1).cross( v3-v1 ); norm.normalize(); glNormal3d( norm[0], norm[1], norm[2] );
	//glVertex3d( 0.0, -yb1, -zb1 );
	//norm = vec2.cross( vec3 ); norm.normalize(); glNormal3d( norm[0], norm[1], norm[2] );
	//glVertex3d( x1, yt1, -zb1 );
	//norm = vec3.cross( vec1 ); norm.normalize(); glNormal3d( norm[0], norm[1], norm[2] );
	//glVertex3d( 0.0, 0.0, radius1 );
}
void Primitive::drawTriangle( const Vector3D& v1,
		const Vector3D& v2, const Vector3D& v3 )
{
	Vector3D norm = (v2-v1).cross( v3-v1 );
	norm.normalize();
	glNormal3d( norm[0], norm[1], norm[2] );
	glVertex3d( v1[0], v1[1], v1[2] );
	glVertex3d( v2[0], v2[1], v2[2] );
	glVertex3d( v3[0], v3[1], v3[2] );
}
void Primitive::drawTrianglePyramid( const Vector3D& vcenter,
		const Vector3D& v1, const Vector3D& v2, const Vector3D& v3 )
{
	drawTriangle( vcenter, v1, v2 );
	drawTriangle( vcenter, v2, v3 );
	drawTriangle( vcenter, v3, v1 );
}


// ImmobilePrimitive
ImmobilePrimitive::ImmobilePrimitive()
{
}
ImmobilePrimitive::~ImmobilePrimitive()
{
	glDeleteLists( mList, 1 );
}
void ImmobilePrimitive::glRender() const
{
	glCallList( mList );
}


// MobilePrimitive
MobilePrimitive::MobilePrimitive()
{
}
MobilePrimitive::~MobilePrimitive()
{
}


// CylinderTextured
CylinderTextured::CylinderTextured( double radius, double height,
								    int numQuads, Texture* texture,
									double numTexturesX, double numTexturesY)
{
	mList = glGenLists( 1 );
	glNewList( mList, GL_COMPILE );
	glEnable( GL_RESCALE_NORMAL );
	texture->glApply();
	glBegin( GL_QUAD_STRIP );
	for (int i=0; i<=numQuads; i++) {
		double theta = 2*M_PI*i/numQuads;
		double theta15 = 2*M_PI*(i-0.5)/numQuads;
		double x = radius*sin(theta);
		double y = -radius*cos(theta);
		double texx = i*numTexturesX/numQuads;
		glTexCoord2d( texx, numTexturesY );
		glVertex3d( x, y, height );
		glTexCoord2d( texx, 0 );
		glNormal3d( sin(theta15), -cos(theta15), 0 );
		glVertex3d( x, y, 0 );
	}
	glEnd();
	glEndList();
}
CylinderTextured::~CylinderTextured()
{
}


// SphereTextured
SphereTextured::SphereTextured( double radius,
								int numSlices, int numStacks, Texture* texture,
								double numTexturesX, double numTexturesY )
{
	mList = glGenLists( 1 );
	// compile display list
	glNewList( mList, GL_COMPILE );
	glEnable( GL_RESCALE_NORMAL );
	texture->glApply();
	for (int i=0; i<numStacks; i++) {
		double phi1 = M_PI*i/numStacks + M_PI;
		double phi15 = M_PI*(i+0.5)/numStacks + M_PI;
		double phi2 = M_PI*(i+1)/numStacks + M_PI;
		double radius1 = radius*sin(phi1);
		double radius2 = radius*sin(phi2);
		double z1 = radius*cos(phi1);
		double z2 = radius*cos(phi2);
		double texy1 = numTexturesY - 1.0*i*numTexturesY/numStacks;
		double texy2 = numTexturesY - 1.0*(i+1)*numTexturesY/numStacks;
		glBegin( GL_QUADS );
		for (int j=0; j<numSlices; j++) {
			double theta1 = 2*M_PI*j/numSlices;
			double theta15 = 2*M_PI*(j+0.5)/numSlices;
			double theta2 = 2*M_PI*(j+1)/numSlices;
			double x11 = radius1*sin(theta1);
			double y11 = -radius1*cos(theta1);
			double x21 = radius2*sin(theta1);
			double y21 = -radius2*cos(theta1);
			double x12 = radius1*sin(theta2);
			double y12 = -radius1*cos(theta2);
			double x22 = radius2*sin(theta2);
			double y22 = -radius2*cos(theta2);
			double texx1 = 1.0*j*numTexturesX/numSlices;
			double texx2 = 1.0*(j+1)*numTexturesX/numSlices;
			glNormal3d( sin(phi15)*sin(theta15), -sin(phi15)*cos(theta15), cos(phi15) );
			glTexCoord2d( texx1, texy1 );
			glVertex3d( x11, y11, z1 );
			glTexCoord2d( texx1, texy2 );
			glVertex3d( x21, y21, z2 );
			glTexCoord2d( texx2, texy2 );
			glVertex3d( x22, y22, z2 );
			glTexCoord2d( texx2, texy1 );
			glVertex3d( x12, y12, z1 );
		}
	}
	glEnd();
	glEndList();
}
SphereTextured::~SphereTextured()
{
}


// ConeTextured
ConeTextured::ConeTextured( double radius, double height, double zoffset, int numSlices, int numStacks,
							Texture* texture, double numTexturesX, double numTexturesY )
{
	mList = glGenLists( 1 );
	// compile display list
	glNewList( mList, GL_COMPILE );
	glEnable( GL_RESCALE_NORMAL );
	texture->glApply();
	glBegin( GL_QUAD_STRIP );
	
	for (int i=0; i<numStacks; i++) {
		double radius1 = i*radius/numStacks;
		double radius2 = (i+1)*radius/numStacks;
		double z1 = zoffset + height - i*height/numStacks;
		double z2 = zoffset + height - (i+1)*height/numStacks;
		double texy1 = numTexturesY - i*numTexturesY/numStacks;
		double texy2 = numTexturesY - (i+1)*numTexturesY/numStacks;
		glBegin( GL_QUAD_STRIP );
		for (int j=0; j<=numSlices; j++) {
			double theta = 2*M_PI*j/numSlices;
			double theta15 = 2*M_PI*(j-0.5)/numSlices;
			double x1 = radius1*sin(theta);
			double y1 = -radius1*cos(theta);
			double x2 = radius2*sin(theta);
			double y2 = -radius2*cos(theta);
			double texx = j*numTexturesX/numSlices;
			Vector3D v( sin(theta15), -cos(theta15), radius/height );
			v.normalize(); glNormal3d( v[0], v[1], v[2] );
			glTexCoord2d( texx, texy1 );
			glVertex3d( x1, y1, z1 );
			glTexCoord2d( texx, texy2 );
			glVertex3d( x2, y2, z2 );
		}
	}
	glEnd();
	glEndList();
}
ConeTextured::~ConeTextured()
{
}


// Tetrahedron2
Tetrahedron2::Tetrahedron2( double radius1, double radius2,
							Material* matBottom, Material* matFront,
							Material* matBackright, Material* matBackleft )
{
	double sqrt2 = sqrt(2.0);
	double sqrt3 = sqrt(3.0);
	double zb1 = radius1/3.0;
	double zb2 = radius2/3.0;
	double yt1 = sqrt2*radius1/3.0;
	double yt2 = sqrt2*radius2/3.0;
	double yb1 = 2*yt1;
	double yb2 = 2*yt2;
	double x1 = sqrt2*radius1/sqrt3;
	double x2 = sqrt2*radius2/sqrt3;

	// Initialize the display list.
	mList = glGenLists( 1 );
	glNewList( mList, GL_COMPILE );   // compile display list
	glEnable( GL_RESCALE_NORMAL );
	Vector3D vec1top( 0.0, 0.0, radius1 );
	Vector3D vec1bottomback( 0.0, -yb1, -zb1 );
	Vector3D vec1bottomfrontleft( -x1, yt1, -zb1 );
	Vector3D vec1bottomfrontright( x1, yt1, -zb1 );
	Vector3D vec2bottom( 0.0, 0.0, -radius2 );
	Vector3D vec2topfront( 0.0, yb2, zb2 );
	Vector3D vec2topbackleft( -x2, -yt2, zb2 );
	Vector3D vec2topbackright( x2, -yt2, zb2 );
	glBegin( GL_TRIANGLES );
	// Face 1 - top right
	matBackright->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vec2topbackright,
		vec1top, vec1bottomback, vec1bottomfrontright );
	// Face 2 - top left
	matBackleft->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vec2topbackleft,
		vec1top, vec1bottomfrontleft, vec1bottomback );
	// Face 3 - top front
	matFront->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vec2topfront,
		vec1top, vec1bottomfrontright, vec1bottomfrontleft );
	// Face 4 - bottom
	matBottom->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vec2bottom,
		vec1bottomback, vec1bottomfrontleft, vec1bottomfrontright );
	glEnd();
	// End
	glEndList();
}
Tetrahedron2::~Tetrahedron2()
{
}


Octahedron2::Octahedron2( double radius1, double radius2,
						  Material* matA, Material* matB,
						  Material* matC, Material* matD,
						  Material* matE, Material* matF,
						  Material* matG, Material* matH )
{
	double sqrt2 = sqrt(2.0);
	double sqrt3 = sqrt(3.0);
	double x = radius1 / sqrt2;
	double h = radius1/sqrt3;
	double r2 = radius1*sqrt2/sqrt3;
	double r1 = r2/2;
	double R = radius2;
	double R3 = R/3.0;
	double X = R*sqrt2/sqrt3;
	double Y1 = R*sqrt2/3;
	double Y2 = 2*Y1;
	// Initialize the display list.
	mList = glGenLists( 1 );
	glNewList( mList, GL_COMPILE );   // compile display list
	Vector3D v1( 0, r2, h );
	Vector3D v2( -x, -r1, h );
	Vector3D v3( x, -r1, h );
	Vector3D v4( 0, -r2, -h );
	Vector3D v5( -x, r1, -h );
	Vector3D v6( x, r1, -h );
	Vector3D va( 0, 0, R );
	Vector3D vb( 0, Y2, -R3 );
	Vector3D vc( X, Y1, R3 );
	Vector3D vd( X, -Y1, -R3 );
	Vector3D ve( 0, -Y2, R3 );
	Vector3D vf( -X, -Y1, -R3 );
	Vector3D vg( -X, Y1, R3 );
	Vector3D vh( 0, 0, -R );
	glBegin( GL_TRIANGLES );
	// Top - 12A, 23A, 31A
	matA->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( va, v1, v2, v3 );
	// Front - 16B, 65B, 51B
	matB->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vb, v1, v6, v5 );
	// Frontright - 13C, 36C, 61C
	matC->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vc, v1, v3, v6 );
	// Backright - 34D, 46D, 63D
	matD->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vd, v3, v4, v6 );
	// Back - 24E, 43E, 32E
	matE->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( ve, v2, v4, v3 );
	// Backleft - 25F, 54F, 42F
	matF->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vf, v2, v5, v4 );
	// Frontleft - 15G, 52G, 21G
	matG->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vg, v1, v5, v2 );
	// Bottom - 45H, 56H, 64H
	matH->glApply( GL_FRONT_AND_BACK );
	drawTrianglePyramid( vh, v4, v5, v6 );
	glEnd();
	// End
	glEnd(); // GL_TRIANGLES
	glEndList();
}
Octahedron2::~Octahedron2()
{
}


// Skybox
Skybox::Skybox( Texture* texture, double halfsize, double height )
{
	mList = glGenLists( 1 );
	glNewList( mList, GL_COMPILE );   // compile display list
	texture->glApply();
	glBegin( GL_QUADS );
	// Front
	glTexCoord2d( 0.25, 0.25 ); glVertex3d( -halfsize, halfsize, halfsize + height );
	glTexCoord2d( 0.25, 0.00 ); glVertex3d( -halfsize, halfsize, height );
	glTexCoord2d( 0.75, 0.00 ); glVertex3d( halfsize, halfsize, height );
	glTexCoord2d( 0.75, 0.25 ); glVertex3d( halfsize, halfsize, halfsize + height );
	// Left
	glTexCoord2d( 0.00, 0.25 ); glVertex3d( -halfsize, halfsize, height );
	glTexCoord2d( 0.25, 0.25 ); glVertex3d( -halfsize, halfsize, halfsize + height );
	glTexCoord2d( 0.25, 0.75 ); glVertex3d( -halfsize, -halfsize, halfsize + height );
	glTexCoord2d( 0.00, 0.75 ); glVertex3d( -halfsize, -halfsize, height );
	// Right
	glTexCoord2d( 0.75, 0.25 ); glVertex3d( halfsize, halfsize, halfsize + height );
	glTexCoord2d( 1.00, 0.25 ); glVertex3d( halfsize, halfsize, height );
	glTexCoord2d( 1.00, 0.75 ); glVertex3d( halfsize, -halfsize, height );
	glTexCoord2d( 0.75, 0.75 ); glVertex3d( halfsize, -halfsize, halfsize + height );
	// Back
	glTexCoord2d( 0.25, 0.75 ); glVertex3d( -halfsize, -halfsize, halfsize + height );
	glTexCoord2d( 0.25, 1.00 ); glVertex3d( -halfsize, -halfsize, height );
	glTexCoord2d( 0.75, 1.00 ); glVertex3d( halfsize, -halfsize, height );
	glTexCoord2d( 0.75, 0.75 ); glVertex3d( halfsize, -halfsize, halfsize + height );
	// Top
	glTexCoord2d( 0.25, 0.25 ); glVertex3d( -halfsize, halfsize, halfsize + height );
	glTexCoord2d( 0.75, 0.25 ); glVertex3d( halfsize, halfsize, halfsize + height );
	glTexCoord2d( 0.75, 0.75 ); glVertex3d( halfsize, -halfsize, halfsize + height );
	glTexCoord2d( 0.25, 0.75 ); glVertex3d( -halfsize, -halfsize, halfsize + height );
	glEnd();
	glEndList();
}
Skybox::~Skybox()
{
}


// Terrain
Terrain::Terrain( Texture* texture, double halfsize, double depth,
				  double metersPerImageX, double metersPerImageY,
				  double speedX, double speedY )
	: mTexture( texture )
	, mHalfSize( halfsize )
	, mDepth( depth )
	, mMetersPerImageX( metersPerImageX )
	, mMetersPerImageY( metersPerImageY )
	, mX( 0 )
	, mY( 0 )
	, mSpeedX( speedX )
	, mSpeedY( speedY )
{
	mList = glGenLists( 1 );
	glNewList( mList, GL_COMPILE );   // compile display list

	mTexture->glApply();
	double x2 = mHalfSize*2/mMetersPerImageX;
	double y2 = mHalfSize*2/mMetersPerImageY;
	glPushMatrix();
	glTranslated( mX*mMetersPerImageX, mY*mMetersPerImageY, 0 );
	glBegin( GL_QUADS );
	glNormal3d( 0, 0, 1 );
	//glTexCoord2d( -mX, -mY ); glVertex3d( -mHalfSize, -mHalfSize, -mDepth );
	//glTexCoord2d( x2, -mY ); glVertex3d( mHalfSize, -mHalfSize, -mDepth );
	//glTexCoord2d( x2, y2 ); glVertex3d( mHalfSize, mHalfSize, -mDepth );
	//glTexCoord2d( -mX, y2 ); glVertex3d( -mHalfSize, mHalfSize, -mDepth );
	glTexCoord2d( 0, 0 ); glVertex3d( -mHalfSize, -mHalfSize, -mDepth );
	glTexCoord2d( x2, 0 ); glVertex3d( mHalfSize, -mHalfSize, -mDepth );
	glTexCoord2d( x2, y2 ); glVertex3d( mHalfSize, mHalfSize, -mDepth );
	glTexCoord2d( 0, y2 ); glVertex3d( -mHalfSize, mHalfSize, -mDepth );
	glEnd();
	glPopMatrix();

	glEndList();
}
Terrain::~Terrain()
{
	glDeleteLists( mList, 1 );
}
void Terrain::step( double seconds )
{
	mX += seconds*mSpeedX;
	mY += seconds*mSpeedY;
	while (mX>=mMetersPerImageX) mX -= mMetersPerImageX;
	while (mY>=mMetersPerImageY) mY -= mMetersPerImageY;
}
void Terrain::glRender() const
{
	glPushMatrix();
	glTranslated( mX*mMetersPerImageX, mY*mMetersPerImageY, 0 );
	glCallList( mList );
	glPopMatrix();
}


// TrackFloorRenderer
TrackFloorRenderer::TrackFloorRenderer( const BezierPatchGrid* bpg,
										const Grid2D<E_ELECTRICCOLOUR>* colourgrid,
										int cellsPerPatchX, int cellsPerPatchY,
										Material** materials, Texture* texture,
										double texturesPerCellX, double texturesPerCellY )
{
	int numCellsX = bpg->getNumCellsX();
	int numCellsY = bpg->getNumCellsY();
	double gridHX = bpg->getGridHX();
	double gridHY = bpg->getGridHY();
	if ( numCellsX != colourgrid->getNumCellsX() || numCellsY != colourgrid->getNumCellsY() ||
		 gridHX != colourgrid->getGridHX() || gridHY != colourgrid->getGridHY() ) throw -1;
	int mNumHeightsX = numCellsX*cellsPerPatchX+1;
	int mNumHeightsY = numCellsY*cellsPerPatchY+1;
	double mGridHx = gridHX/cellsPerPatchX;
	double mGridHy = gridHY/cellsPerPatchY;
	double* mHeights = new double[ mNumHeightsX * mNumHeightsY ];
	// TODO: fill in mHeights appropriately
	for (int i=0; i<mNumHeightsX; i++) {
		double x = i*mGridHx;
		for (int j=0; j<mNumHeightsY; j++) {
			mHeights[j*mNumHeightsX+i] = bpg->computeFOnly( x, j*mGridHy );
		}
	}
	
	mList = glGenLists( 1 );
	glNewList( mList, GL_COMPILE );   // compile display list
	glEnable( GL_RESCALE_NORMAL );
	texture->glApply();
	for (int i=0; i<numCellsX; i++) {
		for (int k=0; k<cellsPerPatchX; k++) {
			int i0 = k+i*cellsPerPatchX;
			double x0 = i0*mGridHx;
			double x1 = x0+mGridHx;
			double texx0 = i0*texturesPerCellX;
			double texx1 = (i0+1)*texturesPerCellX;
			for (int j=0; j<numCellsY; j++) {
				E_ELECTRICCOLOUR ec = colourgrid->getValue( i, j, ELECTRICCOLOUR_BLACK );
				if (ec==ELECTRICCOLOUR_BLACK) continue;
				materials[ec]->glApply( GL_FRONT_AND_BACK );
				glBegin( GL_QUAD_STRIP );
				for (int l=0; l<=cellsPerPatchY; l++) {
					int j0 = l+j*cellsPerPatchY;
					double y = j0*mGridHy;
					double texy = j0*texturesPerCellY;
					double xmid = (i0+0.5)*mGridHx;
					double ymid = (j0+0.5)*mGridHy;
					MatrixMxN F = bpg->compute( xmid, ymid );
					double fx = F[1][0];
					double fy = F[0][1];
					double g = 1+fx*fx+fy*fy;
					glNormal3d( -fx/g, -fy/g, 1.0/g );
					glTexCoord2d( texx0, texy );
					glVertex3d( x0, y, mHeights[j0*mNumHeightsX+i0] );
					glTexCoord2d( texx1, texy );
					glVertex3d( x1, y, mHeights[j0*mNumHeightsX+i0+1] );
				}
				glEnd(); // GL_QUAD_STRIP
			}
		}
	}
	glEndList();
}
TrackFloorRenderer::~TrackFloorRenderer()
{
}


// RacerRenderer
RacerRenderer::RacerRenderer( LagrangianRacer* lagrangianRacer,
							  Primitive* topSphere,
							  Primitive* bottomSphere,
							  Primitive* cylinder,
							  Primitive* cone )
	: mLagrangianRacer( lagrangianRacer )
	, mTopSphere( topSphere )
	, mBottomSphere( bottomSphere )
	, mCylinder( cylinder )
	, mCone( cone )
{
}
RacerRenderer::~RacerRenderer()
{
}
void RacerRenderer::glRender() const
{
	double x = mLagrangianRacer->getX();
	double y = mLagrangianRacer->getY();
	double z = mLagrangianRacer->getZ();
	double theta = mLagrangianRacer->getTheta();
	double phi = mLagrangianRacer->getPhi();
	
	glEnable( GL_LIGHTING );
	glPushMatrix();
	glTranslated( x, y, z );
	glRotated( theta*180.0/M_PI, 0, 0, 1 );
	mBottomSphere->glRender();
	glRotated( phi*180.0/M_PI, 0, 1, 0 );
	glPushMatrix();
	glTranslated( 0, 0, 1 );
	mTopSphere->glRender();
	mCone->glRender();
	glPopMatrix();
	mCylinder->glRender();
	glPopMatrix();
}