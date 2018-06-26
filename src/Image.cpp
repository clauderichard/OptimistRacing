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

#include "Image.hpp"
#include <png.h>
#include <fstream>
#include <stdio.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>


#define PNG_SIGNATURE_SIZE 4

void userReadData(png_structp pngPtr, png_bytep data, png_size_t length) {
    //Here we get our IO pointer back from the read struct.
    //This is the parameter we passed to the png_set_read_fn() function.
    //Our std::istream pointer.
    png_voidp a = png_get_io_ptr(pngPtr);
    //Cast the pointer to std::istream* and read 'length' bytes into 'data'
    ((std::istream*)a)->read((char*)data, length);
}

// create a 1x1 image with 1 colour
Image::Image()
	: mWidth( 1 )
	, mHeight( 1 )
	, mNumColours( 3 )
{
	mData = new int[ mWidth*mHeight*mNumColours ];
	for (int i=0; i<mWidth*mHeight*mNumColours; i++) {
		mData[i] = 100;
	}
}
Image::Image( int numX, int numY )
	: mWidth( numX )
	, mHeight( numY )
	, mNumColours( 3 )
{
	mData = new int[ mWidth*mHeight*mNumColours ];
	for (int i=0; i<mWidth*mHeight*mNumColours; i++) {
		mData[i] = 100;
	}
}
Image::Image( int numX, int numY, int numColours )
	: mWidth( numX )
	, mHeight( numY )
	, mNumColours( numColours )
{
	mData = new int[ mWidth*mHeight*mNumColours ];
	for (int i=0; i<mWidth*mHeight; i++) {
		mData[i] = 100;
	}
}
Image::~Image()
{
	delete[] mData;
}


int Image::getWidth()
{
	return mWidth;
}
int Image::getHeight()
{
	return mHeight;
}
int Image::getNumColours()
{
	return mNumColours;
}
int Image::getData( int x, int y, int colour )
{
	return mData[ colour + y*mWidth*mNumColours + x*mNumColours ];
}

void Image::readPngFile( const std::string& filename )
{
	ALLEGRO_BITMAP* b = al_load_bitmap( filename.c_str() );

	mWidth = al_get_bitmap_width( b );
	mHeight = al_get_bitmap_height( b );
	mNumColours = 3;
	delete[] mData;
	mData = new int[ mWidth*mHeight*mNumColours ];
	al_lock_bitmap( b, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY  );
	for (int i=0; i<mWidth; i++) {
		for (int j=0; j<mHeight; j++) {
			ALLEGRO_COLOR cc = al_get_pixel( b, i, j );
			mData[0 + j*mWidth*mNumColours + i*mNumColours] = min(floor(cc.r * 256),255);
			mData[1 + j*mWidth*mNumColours + i*mNumColours] = min(floor(cc.g * 256),255);
			mData[2 + j*mWidth*mNumColours + i*mNumColours] = min(floor(cc.b * 256),255);
		}
	}
	al_unlock_bitmap( b );
	al_destroy_bitmap( b );


	//std::ifstream in( filename, std::ios::binary );
	//if ( ! in.is_open() ) throw -1;
	////Allocate a buffer of 8 bytes, where we can put the file signature.
 //   png_byte pngSignature[PNG_SIGNATURE_SIZE];
 //   int is_png = 0;
 //   //Read the 8 bytes from the stream into the sig buffer.
 //   in.read( (char*)pngSignature, PNG_SIGNATURE_SIZE);
 //   //Check if the read worked...
 //   if ( !in.good() ) {
	//	int a = 0;
	//	a = 4;
	//	throw -1;
	//}
 //   //Let LibPNG check the sig. If this function returns 0, everything is OK.
 //   bool isPng = png_sig_cmp(pngSignature, 0, PNG_SIGNATURE_SIZE);
 //   if ( isPng != 0 ) throw -1;

	////Here we create the png read struct. The 3 NULL's at the end can be used
	////for your own custom error handling functions, but we'll just use the default.
	////if the function fails, NULL is returned. Always check the return values!
	//png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	//if ( !pngPtr ) throw -1;
	////Here we create the png info struct.
	////Note that this time, if this function fails, we have to clean up the read struct!
	//png_infop infoPtr = png_create_info_struct(pngPtr);
	//if ( !infoPtr ) throw -1;

	////Here I've defined 2 pointers up front, so I can use them in error handling.
	////I will explain these 2 later. Just making sure these get deleted on error.
	//png_bytep* rowPtrs = NULL;
	//unsigned char* data = NULL;
	//if ( setjmp( png_jmpbuf(pngPtr) ) ) {
	//	int a = 0;
	//	a = 1;
	//	//throw -1;
	//	return;
	//}
	//
	//png_set_read_fn( pngPtr, (png_voidp)&in, userReadData );
	//
	////Set the amount signature bytes we've already read:
 //   //We've defined PNGSIGSIZE as 8;
 //   png_set_sig_bytes(pngPtr, PNG_SIGNATURE_SIZE);
 //   //Now call png_read_info with our pngPtr as image handle, and infoPtr to receive the file info.
 //   png_read_info(pngPtr, infoPtr);

	//png_uint_32 imgWidth =  png_get_image_width(pngPtr, infoPtr);
 //   png_uint_32 imgHeight = png_get_image_height(pngPtr, infoPtr);
 //   //bits per CHANNEL! note: not per pixel!
 //   png_uint_32 bitdepth   = png_get_bit_depth(pngPtr, infoPtr);
 //   //Number of channels
 //   png_uint_32 channels   = png_get_channels(pngPtr, infoPtr);
 //   //Color type. (RGB, RGBA, Luminance, luminance alpha... palette... etc)
 //   png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

	//switch (color_type) {
 //       case PNG_COLOR_TYPE_PALETTE:
 //           png_set_palette_to_rgb(pngPtr);
 //           //Don't forget to update the channel info (thanks Tom!)
 //           //It's used later to know how big a buffer we need for the image
 //           channels = 3;
 //           break;
 //       case PNG_COLOR_TYPE_GRAY:
 //           if (bitdepth < 8)
 //           png_set_expand_gray_1_2_4_to_8(pngPtr);
 //           //And the bitdepth info
 //           bitdepth = 8;
 //           break;
 //   }
 //   /*if the image has a transperancy set.. convert it to a full Alpha channel..*/
 //   if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
 //       png_set_tRNS_to_alpha(pngPtr);
 //       channels+=1;
 //   }

	////Here's one of the pointers we've defined in the error handler section:
 //   //Array of row pointers. One for every row.
 //   rowPtrs = new png_bytep[imgHeight];
 //   //Alocate a buffer with enough space.
 //   //(Don't use the stack, these blocks get big easilly)
 //   //This pointer was also defined in the error handling section, so we can clean it up on error.
 //   data = new unsigned char[imgWidth * imgHeight * bitdepth * channels / 8];
 //   //This is the length in bytes, of one row.
 //   const unsigned int stride = imgWidth * bitdepth * channels / 8;
 //   //A little for-loop here to set all the row pointers to the starting
 //   //Adresses for every row in the buffer
 //   for (size_t i = 0; i < imgHeight; i++) {
 //       //Set the pointer to the data pointer + i times the row stride.
 //       //Notice that the row order is reversed with q.
 //       //This is how at least OpenGL expects it,
 //       //and how many other image loaders present the data.
 //       png_uint_32 q = (imgHeight- i - 1) * stride;
 //       rowPtrs[i] = (png_bytep)data + q;
 //   }
 //   png_read_image( pngPtr, rowPtrs );
	//
	//mWidth = imgWidth;
	//mHeight = imgHeight;
	//mNumColours = channels;
	//delete[] mData;
	//mData = new int[ mWidth*mHeight*mNumColours ];
	//for (int i=0; i<mNumColours*mWidth*mHeight; i++) {
	//	mData[i] = data[i];
	//}
	////if (imgWidth==256 || imgWidth==139 || imgWidth==300) {
	////	for (int i=0; i<mWidth; i++) {
	////		for (int j=0; j<mHeight; j++) {
	////			for (int k=0; k<mNumColours; k++) {
	////				mData[k + i*mNumColours + j*mNumColours*mWidth] = i;
	////			}
	////		}
	////	}
	////}

	////Delete the row pointers array....
 //   delete[] (png_bytep)rowPtrs;
 //   //And don't forget to clean up the read and info structs !
 //   png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);

	//in.close();
}
