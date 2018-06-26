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

#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Material.hpp"
#include <algorithm>
#include "Image.hpp"

Texture::Texture( Image* image, bool wrap )
	: mGL( 0 )
{
	int width, height;
    BYTE* data;
	// allocate buffer
    width = image->getWidth();
    height = image->getHeight();
    data = new BYTE[ height*width*3 ];
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			unsigned int k = image->getData(i, j, 0);
			data[3*width*j + 3*i] = k;
			unsigned int k1 = image->getData(i, j, 1);
			data[3*width*j + 3*i + 1] = k1;
			unsigned int k2 = image->getData(i, j, 2);
			data[3*width*j + 3*i + 2] = k2;
			if (width==255 && i==0 && j==254) {
				int hoo = 22;
			}
			if (width==256 && i==0 && j==255) {
				int hoo = 22;
			}
		}
	}
	// Use data array to make the texture
	glDisable( GL_TEXTURE_2D );
    // allocate a texture name
    glGenTextures( 1, &mGL );
    // select our current texture
    glBindTexture( GL_TEXTURE_2D, mGL );
    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
                     //GL_LINEAR );
    // when texture area is large, bilinear filter the first mipmap
    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );
    // build our texture mipmaps
	//glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );
    // free buffer
    free( data );
}
Texture::~Texture()
{
    glDeleteTextures( 1, &mGL );
}
GLuint Texture::glGet() const
{
	return mGL;
}
void Texture::glApply() const
{
	glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, mGL );
}


Colour::Colour( double red, double green, double blue )
	: mR( red )
	, mG( green )
	, mB( blue )
{
}
Colour::~Colour()
{
}
double Colour::R() const
{
	return mR;
}
double Colour::G() const
{
	return mG;
}
double Colour::B() const
{
	return mB;
}

// Material
Material::Material( Colour emission, Colour ambient,
					Colour diffuse, Colour specular, double shininess )
{
	mEmission[0] = emission.R();
	mEmission[1] = emission.G();
	mEmission[2] = emission.B();
	mAmbient[0] = ambient.R();
	mAmbient[1] = ambient.G();
	mAmbient[2] = ambient.B();
	mDiffuse[0] = diffuse.R();
	mDiffuse[1] = diffuse.G();
	mDiffuse[2] = diffuse.B();
	mSpecular[0] = specular.R();
	mSpecular[1] = specular.G();
	mSpecular[2] = specular.B();
	mShininess[0] = shininess;
}
Material::~Material()
{
}

void Material::glApply( GLenum face ) const
{
	glMaterialfv( face, GL_EMISSION, mEmission );
	glMaterialfv( face, GL_AMBIENT, mAmbient );
	glMaterialfv( face, GL_SPECULAR, mSpecular );
	glMaterialfv( face, GL_DIFFUSE, mDiffuse );
	glMaterialfv( face, GL_SHININESS, mShininess );
}