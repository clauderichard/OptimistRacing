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
#include "Image.hpp"

/**
 * A Texture basically stores an image,
 * which is usually read from an image file (e.g. PNG)
 * so it can do texture mapping in OpenGL.
 */
class Texture
{
public:
	// image must have height and width that are powers of 2
	// e.g. 64x128 or 256x256 are fine
	Texture( Image* image, bool wrap );
	~Texture();
	GLuint glGet() const;
	void glApply() const;
private:
	GLuint mGL;
};


class Colour
{
public:
	Colour( double red, double green, double blue );
	~Colour();
	double R() const;
	double G() const;
	double B() const;
private:
	double mR;
	double mG;
	double mB;
};


class Material
{
public:
	Material( Colour emission, Colour ambient,
			  Colour diffuse, Colour specular, double shininess );
	~Material();
	void glApply( GLenum face ) const;
private:
	GLfloat mEmission[3];
	GLfloat mAmbient[3];
	GLfloat mDiffuse[3];
	GLfloat mSpecular[3];
	GLfloat mShininess[1];
};
