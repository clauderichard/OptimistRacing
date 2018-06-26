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

#include "StoryMenu.hpp"
#include "FileLocator.hpp"


WorldIconArea::WorldIconArea( double left, double right, double top, double bottom, const std::string& imageName )
	: RectangularPointableArea( left, right, top, bottom )
{
	Image img;
	img.readPngFile( imageName );
	mTexture = new Texture( &img, false );
	mIntensityTracker = new FlickeringIntensityTracker( 0.8, 1.0, 0.8, 0.15 );
}

WorldIconArea::~WorldIconArea()
{
	delete mTexture;
	delete mIntensityTracker;
}


void WorldIconArea::stepThis( double seconds )
{
	mIntensityTracker->step( seconds, mPointerInside );
}

void WorldIconArea::eventPointerClick()
{
	mParent->selectWorld(this);
}

void WorldIconArea::eventPointerUnclick()
{
}

void WorldIconArea::eventPointerGoaway()
{
}

void WorldIconArea::eventPointerComeback()
{
}

void WorldIconArea::glRenderThis() const
{
	double intensity = mIntensityTracker->getCurrentIntensity();
	glColor3d( intensity, intensity, intensity );
	mTexture->glApply();
	glBegin( GL_QUADS );
	glTexCoord2d( 0, 0 );
	glVertex3d( 0, 0, 0 );
	glTexCoord2d( 1, 0 );
	glVertex3d( 1, 0, 0 );
	glTexCoord2d( 1, 1 );
	glVertex3d( 1, 1, 0 );
	glTexCoord2d( 0, 1 );
	glVertex3d( 0, 1, 0 );
	glEnd(); // GL_QUADS
}


StoryMenu::StoryMenu( const UniverseData* univ, const MouseInputTracker* mouse, int pixelsX, int pixelsY )
	: RectangularPointableAreaMaster( mouse, 0, pixelsX, 0, pixelsY )
	, mMouse( mouse )
	, mPixelsX( pixelsX )
	, mPixelsY( pixelsY )
	, mSelectedWorld( -1 )
{
	mNum = univ->mNamesWorlds.size();
	mNumY = ceil(sqrt(mNum*1.0));
	mNumX = mNumY;
	//mNumX = mNum / mNumY;
	//if ( ( mNum % mNumY ) != 0 ) mNumX ++;
	mWorldImages = new Texture*[mNum];
	mIntensityTrackers = new IntensityTracker*[mNum];

	Image img;
	// fill in world images
	for (int i=0; i<mNum; i++) {
		WorldData* wor = loadWorldData( univ->mNamesWorlds[i] );
		img.readPngFile( "images/" + wor->mImageMenu + ".png" );
		delete wor;
		mWorldImages[i] = new Texture( &img, false );
		mIntensityTrackers[i] = new FlickeringIntensityTracker( 0.8, 1.0, 0.8, 0.15 );
	}
}

StoryMenu::~StoryMenu()
{
	for (int i=0; i<mNum; i++) {
		delete mWorldImages[i];
	}
	delete[] mWorldImages;
}

void StoryMenu::selectWorld( WorldIconArea* area )
{
	int i=0;
	for (std::list<RectangularPointableArea*>::const_iterator it=mButtons.begin(); it!=mButtons.end(); it++) {
		if ( *it == area ) {
			mSelectedWorld = i;
		}
		i ++;
	}
}

int StoryMenu::step( double seconds )
{
	double imgx = mPixelsX*1.0 / mNumX;
	double imgy = mPixelsY*1.0 / mNumY;
	int x = floor( mMouse->getPositionX()/imgx );
	int y = floor( mMouse->getPositionY()/imgy );
	int index = y*mNumX + x;

	
	for (int i=0; i<mNum; i++) {
		mIntensityTrackers[i]->step( seconds, i==index );
	}
	if ( index >= mNum ) return -1;
	if ( mMouse->getKeyTimesPressed( 0 ) == 0 ) return -1;
	mSelectedWorld = index;
	return mSelectedWorld;
}

void StoryMenu::glRenderThis() const
{
	// Set up the perspective
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, 1, 1, 0, 0, 1 );
	glDisable( GL_DEPTH_TEST );
	//gluPerspective( 90, 1.0*400/400, 0.01, 50000 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glDisable( GL_LIGHTING );
	glColor3d( 1, 1, 1 );

	// render each textured quad
	glEnable( GL_RESCALE_NORMAL );
	int k = 0;
	for (int i=0; i<mNumY; i++) {
		double ytop = i*1.0/mNumY;
		double ybottom = (i+1)*1.0/mNumY;
		for (int j=0; j<mNumX; j++) {
			if ( k >= mNum ) return;
			double xleft = j*1.0/mNumX;
			double xright = (j+1)*1.0/mNumX;

			double intensity = mIntensityTrackers[k]->getCurrentIntensity();
			glColor3d( intensity, intensity, intensity );
			mWorldImages[k]->glApply();
			glBegin( GL_QUADS );
			glTexCoord2d( 0, 0 );
			glVertex3d( xleft, ytop, 0 );
			glTexCoord2d( 1, 0 );
			glVertex3d( xright, ytop, 0 );
			glTexCoord2d( 1, 1 );
			glVertex3d( xright, ybottom, 0 );
			glTexCoord2d( 0, 1 );
			glVertex3d( xleft, ybottom, 0 );
			glEnd(); // GL_QUADS

			k ++;
		}
	}
}