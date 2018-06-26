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

/// This class tracks the intensity of e.g. a light bulb.
/// Input: for each timestep, whether the switch is on or off.
/// Output: the intensity of the light.
/// This will be used when the mouse hovers over (on) and not over (off) an icon.
class IntensityTracker {

public:

	IntensityTracker();
	~IntensityTracker();

	/// returns the new intensity
	virtual double step( double seconds, bool on ) = 0;

	/// returns the current intensity
	double getCurrentIntensity();

	/// returns whether the switch is on or off
	bool getCurrentSwitch();

	/// returns the initial intensity
	virtual double reset() = 0;

protected:

	/// true if the switch is on
	bool mCurrentSwitch;

	// number of keyboard-keys and game-buttons
	double mCurrentIntensity;

};


class FlickeringIntensityTracker : public IntensityTracker {

public:

	// The constructor and destructor are pretty standard.
	// The key mapping is set to something not very usable.
	FlickeringIntensityTracker( double intensityOff, double intensityOnTop, double intensityOnBottom, double topBottomSeconds );
	~FlickeringIntensityTracker();

	/// returns the new intensity
	virtual double step( double seconds, bool on );

	/// returns the initial intensity
	virtual double reset();

protected:

	/// intensities
	double mIntensityOff;
	double mIntensityOnTop;
	double mIntensityOnBottom;

	/// how much time from on-switch to intensity stabilization
	double mTopBottomSeconds;
	
	/// how much time since last on-switch
	double mCurrentTimeOn;

};