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

#include "Data.hpp"
#include "Primitive.hpp"
#include "Material.hpp"
#include "WorldEngine.hpp"
#include "Lagrange.hpp"
#include "InputTracker.hpp"
#include "IntensityTracker.hpp"
#include "Menu.hpp"


class StoryMenu;


class WorldIconArea : public RectangularPointableArea {
	
	WorldIconArea( double left, double right, double top, double bottom, const std::string& imageName );
	~WorldIconArea();

protected:

	virtual void stepThis( double seconds );
	virtual void eventPointerClick();
	virtual void eventPointerUnclick();
	virtual void eventPointerGoaway();
	virtual void eventPointerComeback();
	//virtual void eventPointerMove( double positionX, double positionY );
	virtual void glRenderThis() const;

private:

	Texture* mTexture;
	IntensityTracker* mIntensityTracker;
	StoryMenu* mParent;

};


class StoryMenu : public RectangularPointableAreaMaster
{

public:

	StoryMenu( const UniverseData* univ, const MouseInputTracker* mouse, int pixelsX, int pixelsY );
	~StoryMenu();

	void selectWorld( WorldIconArea* area );

	// returns selected (clicked) world index, or -1.
	int step( double seconds );
	void glRenderThis() const;

private:

	const MouseInputTracker* mMouse;

	// number of world images across screen
	int mNum;
	int mNumX;
	int mNumY;
	int mPixelsX;
	int mPixelsY;
	// array of world images
	Texture** mWorldImages;
	IntensityTracker** mIntensityTrackers;
	int mSelectedWorld;

};