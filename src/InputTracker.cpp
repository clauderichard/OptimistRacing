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

#include "InputTracker.hpp"



KeyboardInputTracker::KeyboardInputTracker( int numKeys )
	: mNumKeys( numKeys )
{
	mKeyTimesPressed = new int[ mNumKeys ];
	mKeyTimesReleased = new int[ mNumKeys ];
	mKeyPressed = new bool[ mNumKeys ];
	for (int i=0; i<mNumKeys; i++) {
		mKeyTimesPressed[ i ] = 0;
		mKeyTimesReleased[ i ] = 0;
		mKeyPressed[ i ] = false;
	}
}

KeyboardInputTracker::~KeyboardInputTracker()
{
	delete mKeyTimesPressed;
	delete mKeyTimesReleased;
	delete mKeyPressed;
}

void KeyboardInputTracker::pressKey( int key )
{
	mKeyPressed[ key ] = true;
	mKeyTimesPressed[ key ] ++;
}

void KeyboardInputTracker::releaseKey( int key )
{
	mKeyPressed[ key ] = false;
	mKeyTimesReleased[ key ] ++;
}

void KeyboardInputTracker::resetCounts()
{
	for (int i=0; i<mNumKeys; i++) {
		mKeyTimesPressed[ i ] = 0;
		mKeyTimesReleased[ i ] = 0;
	}
}

int KeyboardInputTracker::getKeyTimesPressed( int key ) const
{
	return mKeyTimesPressed[key];
}

int KeyboardInputTracker::getKeyTimesReleased( int key ) const
{
	return mKeyTimesReleased[key];
}

bool KeyboardInputTracker::isKeyPressed( int key ) const
{
	return mKeyPressed[key];
}

GameButtonInputTracker::GameButtonInputTracker( int numKeys, int numButtons )
	: KeyboardInputTracker( numKeys )
	, mNumButtons( numButtons )
{
	mMap = new int[ mNumButtons ];
	for (int i=0; i<mNumButtons; i++) {
		mMap[ i ] = -1;
	}
}

GameButtonInputTracker::~GameButtonInputTracker()
{
	delete mMap;
}

void GameButtonInputTracker::setMap( int button, int key )
{
	mMap[ button ] = key;
}

int GameButtonInputTracker::getButtonTimesPressed( int button ) const
{
	int key = mMap[ button ];
	return key < 0 ? 0 : mKeyTimesPressed[ key ];
}

int GameButtonInputTracker::getButtonTimesReleased( int button ) const
{
	int key = mMap[ button ];
	return key < 0 ? 0 : mKeyTimesReleased[ key ];
}

bool GameButtonInputTracker::isButtonPressed( int button ) const
{
	int key = mMap[ button ];
	return key < 0 ? false : mKeyPressed[ key ];
}

PointerTracker::PointerTracker()
	: mX( 0 )
	, mY( 0 )
	, mDiffX( 0 )
	, mDiffY( 0 )
{
}

PointerTracker::~PointerTracker()
{
}

void PointerTracker::setPosition( int x, int y )
{
	mX = x;
	mY = y;
}
	
int PointerTracker::getPositionX() const
{
	return mX;
}

int PointerTracker::getPositionY() const
{
	return mY;
}

int PointerTracker::getPositionDiffX() const
{
	return mDiffX;
}

int PointerTracker::getPositionDiffY() const
{
	return mDiffY;
}

void PointerTracker::resetDiff()
{
	mDiffX = 0;
	mDiffY = 0;
}

MouseInputTracker::MouseInputTracker( int numButtons )
	: KeyboardInputTracker( numButtons )
{
}

MouseInputTracker::~MouseInputTracker()
{
}