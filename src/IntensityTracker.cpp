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

#include "IntensityTracker.hpp"
#include <algorithm>

IntensityTracker::IntensityTracker()
	: mCurrentSwitch( false )
	, mCurrentIntensity( 0 )
{
}

IntensityTracker::~IntensityTracker()
{
}

double IntensityTracker::getCurrentIntensity()
{
	return mCurrentIntensity;
}

bool IntensityTracker::getCurrentSwitch()
{
	return mCurrentSwitch;
}


FlickeringIntensityTracker::FlickeringIntensityTracker( double intensityOff,
	double intensityOnTop, double intensityOnBottom, double topBottomSeconds )
	: mIntensityOff( intensityOff )
	, mIntensityOnTop( intensityOnTop )
	, mIntensityOnBottom( intensityOnBottom )
	, mTopBottomSeconds( topBottomSeconds )
	, mCurrentTimeOn( 0 )
{
}

FlickeringIntensityTracker::~FlickeringIntensityTracker()
{
}

double FlickeringIntensityTracker::step( double seconds, bool on )
{
	mCurrentSwitch = on;
	if (on) {
		mCurrentTimeOn += seconds;
		double p = mCurrentTimeOn / mTopBottomSeconds;
		//p = std::min( p, 1.0 );
		p = p - floor(p);
		double q = 1-p;
		mCurrentIntensity = p*mIntensityOnBottom + q*mIntensityOnTop;
	} else {
		mCurrentTimeOn = 0;
		mCurrentIntensity = mIntensityOff;
	}
	return mCurrentIntensity;
}

double FlickeringIntensityTracker::reset()
{
	mCurrentSwitch = false;
	mCurrentTimeOn = 0;
	mCurrentIntensity = mIntensityOff;
	return mCurrentIntensity;
}