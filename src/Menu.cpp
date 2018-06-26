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

#include "Menu.hpp"
#include <GL\glew.h>
#include <GL\freeglut.h>


RectangularPointableArea::RectangularPointableArea( double left, double right, double top, double bottom )
	: mLeftX( left )
	, mRightX( right )
	, mTopY( top )
	, mBottomY( bottom )
	, mPointerPressed( false )
	, mPointerInside( false )
	, mPointerX( 0 )
	, mPointerY( 0 )
{
}

RectangularPointableArea::~RectangularPointableArea()
{
}

void RectangularPointableArea::addArea( RectangularPointableArea* area )
{
	mButtons.push_back( area );
}

void RectangularPointableArea::stepArea( double seconds )
{
	// step all the children
	for (std::list<RectangularPointableArea*>::const_iterator it=mButtons.begin(); it!=mButtons.end(); it++) {
		(*it)->stepArea( seconds );
	}
}

void RectangularPointableArea::glRender() const
{
	glRenderThis();
	// render the children
	glPushMatrix();
	for (std::list<RectangularPointableArea*>::const_iterator it=mButtons.begin(); it!=mButtons.end(); it++) {
		glTranslated( (*it)->mLeftX, (*it)->mTopY, 0 );
		glScaled( (*it)->mRightX - (*it)->mLeftX, (*it)->mBottomY - (*it)->mTopY, 0 );
		(*it)->glRender();
	}
	glPopMatrix();
}

void RectangularPointableArea::eventPointerClickRecursive()
{
	mPointerPressed = true;
	eventPointerClick();
	for (std::list<RectangularPointableArea*>::const_iterator it=mButtons.begin(); it!=mButtons.end(); it++) {
		if ( ! (*it)->mPointerInside ) continue;
		(*it)->eventPointerClickRecursive();
	}
}

void RectangularPointableArea::eventPointerUnclickRecursive()
{
	mPointerPressed = false;
	eventPointerUnclick();
	for (std::list<RectangularPointableArea*>::const_iterator it=mButtons.begin(); it!=mButtons.end(); it++) {
		if ( ! (*it)->mPointerInside ) continue;
		(*it)->eventPointerUnclickRecursive();
	}
}

void RectangularPointableArea::eventPointerMoveRecursive( double positionX, double positionY )
{
	mPointerX = positionX;
	mPointerY = positionY;
	bool insideBefore = mPointerInside;
	mPointerInside = ( mPointerX>=mLeftX && mPointerX<=mRightX && mPointerY>=mTopY && mPointerY<=mBottomY );
	if ( mPointerInside && !insideBefore ) eventPointerComeback();
	if ( !mPointerInside && insideBefore ) eventPointerGoaway();
	if ( mPointerInside || insideBefore ) eventPointerMove( positionX, positionY );
	for (std::list<RectangularPointableArea*>::const_iterator it=mButtons.begin(); it!=mButtons.end(); it++) {
		(*it)->eventPointerMoveRecursive( (positionX-mLeftX)/(mRightX-mLeftX), (positionY-mTopY)/(mBottomY-mTopY) );
	}
}

void RectangularPointableArea::stepThis( double seconds )
{
}

void RectangularPointableArea::eventPointerClick()
{
}

void RectangularPointableArea::eventPointerUnclick()
{
}

void RectangularPointableArea::eventPointerGoaway()
{
}

void RectangularPointableArea::eventPointerComeback()
{
}

void RectangularPointableArea::eventPointerMove( double positionX, double positionY )
{
}

void RectangularPointableArea::glRenderThis() const
{
}


RectangularPointableAreaMaster::RectangularPointableAreaMaster( const MouseInputTracker* pointerTracker,
	double left, double right, double top, double bottom )
	: RectangularPointableArea( left, right, top, bottom )
	, mPointerTracker( pointerTracker )
{
}

RectangularPointableAreaMaster::~RectangularPointableAreaMaster()
{
}

void RectangularPointableAreaMaster::stepThis( double seconds )
{
	// move pointer if necessary
	if ( mPointerTracker->getPositionDiffX()!=0 || mPointerTracker->getPositionDiffY()!=0 ) {
		eventPointerMoveRecursive( mPointerTracker->getPositionX(), mPointerTracker->getPositionY() );
	}
	// click/unclick if necessary
	if ( mPointerTracker->getKeyTimesPressed(0)!=0 ) {
		eventPointerClickRecursive();
	}
	if ( mPointerTracker->getKeyTimesReleased(0)!=0 ) {
		eventPointerUnclickRecursive();
	}
}
	
void RectangularPointableAreaMaster::glRenderThis() const
{
}