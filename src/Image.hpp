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
#include <string>

class Image
{

public:
	// create a 1x1 image with 1 colour
	Image();
	Image( int numX, int numY ); // 1 colour
	Image( int numX, int numY, int numColours );
	~Image();

	int getWidth();
	int getHeight();
	int getNumColours();
	// Returns a number between 0 and 255
	int getData( int x, int y, int colour );

	void readPngFile( const std::string& filename );

private:
	int mWidth;
	int mHeight;
	int mNumColours;
	int* mData;

};