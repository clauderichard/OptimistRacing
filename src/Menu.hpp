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

#include <list>
#include "InputTracker.hpp"
#include "Event.hpp"


class RectangularPointableArea : EventPublisher {

public:

	RectangularPointableArea( double left, double right, double top, double bottom );
	~RectangularPointableArea();

	void addArea( RectangularPointableArea* area );

	void stepArea( double seconds );
	void glRender() const;

protected:

	void eventPointerClickRecursive();
	void eventPointerUnclickRecursive();
	void eventPointerMoveRecursive( double positionX, double positionY );
	virtual void stepThis( double seconds );
	virtual void eventPointerClick();
	virtual void eventPointerUnclick();
	virtual void eventPointerGoaway();
	virtual void eventPointerComeback();
	virtual void eventPointerMove( double positionX, double positionY );
	virtual void glRenderThis() const;
	
	std::list<RectangularPointableArea*> mButtons;

	// position within parent area
	// left < right
	// top < bottom
	double mLeftX;
	double mRightX;
	double mTopY;
	double mBottomY;

	// mouse position and whether it's left-clicked
	bool mPointerPressed;
	bool mPointerInside;
	double mPointerX;
	double mPointerY;

};


class RectangularPointableAreaMaster : public RectangularPointableArea {

public:

	RectangularPointableAreaMaster( const MouseInputTracker* pointerTracker,
		double left, double right, double top, double bottom );
	~RectangularPointableAreaMaster();

protected:
	void stepThis( double seconds ); // trigger events here
	
	//void eventMouseClick( int button, double positionX, double positionY );
	//void eventMouseUnclick( int button, double positionX, double positionY );
	//void eventMouseGoaway();
	void eventMouseComeback();
	//void eventMouseMove( double positionX, double positionY );
	void glRenderThis() const;

	const MouseInputTracker* mPointerTracker;

};