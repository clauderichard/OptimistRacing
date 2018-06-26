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
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Bezier.hpp"
#include "Material.hpp"
#include "Lagrange.hpp"
#include "ElectricColour.hpp"
#include "Grid.hpp"
using namespace Lagrange;

//// TODO: use a display list
//class WireSphereRenderer
//{
//public:
//	WireSphereRenderer( int numSlices, int numStacks );
//	~WireSphereRenderer();
//	void glRender();
//private:
//	int mNumSlices;
//	int mNumStacks;
//};


class Primitive
{
public:
	Primitive();
	~Primitive();
	virtual void glRender() const = 0;
	static void drawTriangles( const Vector3D& centerVector,
		const Vector3D* outerVectors );
	static void drawTriangle( const Vector3D& v1,
		const Vector3D& v2, const Vector3D& v3 );
	static void drawTrianglePyramid( const Vector3D& vcenter,
		const Vector3D& v1, const Vector3D& v2, const Vector3D& v3 );
};


class ImmobilePrimitive : public Primitive
{
public:
	ImmobilePrimitive();
	~ImmobilePrimitive();
	void glRender() const;
protected:
	GLuint mList;
};


class MobilePrimitive : public Primitive
{
public:
	MobilePrimitive();
	~MobilePrimitive();
	virtual void step( double seconds ) = 0;
	virtual void glRender() const = 0;
};


// Cylinder without top or bottom, but with texture
class CylinderTextured : public ImmobilePrimitive
{
public:
	// image appears once, on the front.
	// so it better be a wrappable texture.
	CylinderTextured( double radius, double height,
					  int numQuads, Texture* texture,
					  double numTexturesX, double numTexturesY );
	~CylinderTextured();
};


// Cylinder without top or bottom, but with texture
class SphereTextured : public ImmobilePrimitive
{
public:
	// image appears once, on the front.
	// so it better be a wrappable texture.
	SphereTextured( double radius,
					int numSlices, int numStacks, Texture* texture,
					double numTexturesX, double numTexturesY );
	~SphereTextured();
};


// Cylinder without top or bottom, but with texture
class ConeTextured : public ImmobilePrimitive
{
public:
	// image appears once, on the front.
	// so it better be a wrappable texture.
	ConeTextured( double radius, double height, double zoffset, int numSlices, int numStacks,
				  Texture* texture, double numTexturesX, double numTexturesY );
	~ConeTextured();
};


// Tetrahedron2 is like a tetrahedron,
//  but each face is itself another tetrahedron.
// Pass in the radius of the original tetrahedron,
//  then the distance from center of original to the
//  tip of the mini-tetrahedrons.
class Tetrahedron2 : public ImmobilePrimitive
{
public:
	Tetrahedron2( double radius1, double radius2,
				  Material* matBottom, Material* matFront,
				  Material* matBackright, Material* matBackleft );
	~Tetrahedron2();
};


// Octahedron2 is like an octahedron,
//  but each face is itself a tetrahedron.
// Pass in the radius of the original tetrahedron,
//  then the distance from center of original to the
//  tip of the mini-tetrahedrons.
class Octahedron2 : public ImmobilePrimitive
{
public:
	Octahedron2( double radius1, double radius2,
				 Material* matA, Material* matB,
				 Material* matC, Material* matD,
				 Material* matE, Material* matF,
				 Material* matG, Material* matH );
	~Octahedron2();
};


// Sky
class Skybox : public ImmobilePrimitive
{
public:
	Skybox( Texture* texture, double halfsize, double height );
	~Skybox();
};


class Terrain : public MobilePrimitive
{
public:
	Terrain( Texture* texture, double halfsize, double depth,
			 double metersPerImageX, double metersPerImageY,
			 double speedX, double speedY );
	~Terrain();
	virtual void step( double seconds );
	virtual void glRender() const;
private:
	GLuint mList;
	Texture* mTexture;
	double mHalfSize;
	double mDepth;
	double mMetersPerImageX;
	double mMetersPerImageY;
	double mX;
	double mY;
	double mSpeedX;
	double mSpeedY;
};


class TrackFloorRenderer : public ImmobilePrimitive
{
public:
	// materials must be an array with a material for each ElectricColour
	TrackFloorRenderer( const BezierPatchGrid* bpg,
						const Grid2D<E_ELECTRICCOLOUR>* colourgrid,
						int cellsPerPatchX, int cellsPerPatchY,
						Material** materials, Texture* texture,
						double texturesPerCellX, double texturesPerCellY );
	~TrackFloorRenderer();
};


class RacerRenderer : public Primitive
{
public:
	RacerRenderer( LagrangianRacer* lagrangianRacer,
				   Primitive* topSphere,
				   Primitive* bottomSphere,
				   Primitive* cylinder,
				   Primitive* cone );
	~RacerRenderer();
	virtual void glRender() const;
private:
	LagrangianRacer* mLagrangianRacer;
	Primitive* mTopSphere;
	Primitive* mBottomSphere;
	Primitive* mCylinder;
	Primitive* mCone;
};