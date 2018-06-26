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


class KeyboardInputTracker {

public:

	KeyboardInputTracker( int numKeys );
	~KeyboardInputTracker();

	// Call this during the key-press event.
	void pressKey( int key );
	// Call this during the key-release event.
	void releaseKey( int key );

	// This resets m_times_pressed and m_times_released
	// Call this after a frame has passed.
	void resetCounts();

	// Get methods for keys and game-buttons
	int getKeyTimesPressed( int key ) const;
	int getKeyTimesReleased( int key ) const;
	bool isKeyPressed( int key ) const;

protected:

	// number of keyboard-keys and game-buttons
	int mNumKeys;

	// These are arrays. Each array has one element per button
	// Each key has a number of times pressed since the last reset.
	// Each key has a number of times released since the last reset.
	int* mKeyTimesPressed;
	int* mKeyTimesReleased;
	bool* mKeyPressed;

};


class GameButtonInputTracker : public KeyboardInputTracker {

public:

	// The constructor and destructor are pretty standard.
	// The key mapping is set to something not very usable.
	GameButtonInputTracker( int numKeys, int numButtons );
	~GameButtonInputTracker();

	// Links a key to a keytype.
	void setMap( int button, int key );

	// Get methods
	int getButtonTimesPressed( int button ) const;
	int getButtonTimesReleased( int button ) const;
	bool isButtonPressed( int button ) const;

private:

	// number of game-buttons
	int mNumButtons;

	// This is the current map from game-buttons to keyboard-keys.
	int* mMap;

};


class PointerTracker
{
	
public:

	PointerTracker();
	~PointerTracker();

	void setPosition( int x, int y );
	
	int getPositionX() const;
	int getPositionY() const;
	int getPositionDiffX() const;
	int getPositionDiffY() const;

	void resetDiff();

protected:

	// These are for the x-y position of the mouse, and the change since last frame.
	int mX;
	int mY;
	int mDiffX;
	int mDiffY;

};


class MouseInputTracker : public KeyboardInputTracker, public PointerTracker
{

public:

	// The constructor and destructor are pretty standard.
	// The key mapping is set to something not very usable.
	MouseInputTracker( int numButtons );
	~MouseInputTracker();

};