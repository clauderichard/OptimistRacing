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

#include "Algebra.hpp"

/**
 * \brief		Contains functions for detecting collisions between shapes.
 * \author		Claude Richard
 * \date		2012
 * \todo		Add more functions to this class.
 */
class Collision
{

public:
	
	/**
	 * \brief		Determines whether 2 spheres overlap each other.
	 * \details		A sphere s1 has radius radius1 and is centered at center1.
	 *				A sphere s2 has radius radius2 and is centered at center2.
	 *				This function returns true if s1 and s2 overlap.
	 *				I.e. it returns true if the distance between the two centers
	 *				is smaller than the sum of the two radii.
	 * \pre			\a radius1 and \a radius2 must be non-negative.
	 * \param		radius1	The radius of the first sphere.
	 * \param		radius2	The radius of the second sphere.
	 * \param		center1	The center position of the first sphere.
	 * \param		center2	The center position of the second sphere.
	 * \return		True if and only if the two spheres overlap.
	 * \throw		An error when one of the radius arguments is negative.
	 * \todo		Make this function actually throw an error.
	 */
	static bool overlapSpheres( double radius1, double radius2,
								const Vector3D& center1, const Vector3D& center2 );

};