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

#include <iostream>

/**
 * \brief	A set of 8 colours that affect the physics of the game.
 * \details
 * There are 8 ElectricColours.
 * There are 3 basic colours: red, green and blue.
 * You can think of an ElectricColour as a subset of the set {red, green, blue}.
 * BLACK = {}.
 * RED = {red}.
 * GREEN = {green}.
 * BLUE = {blue}.
 * YELLOW = {red, green}.
 * MAGENTA = {red, blue}.
 * CYAN = {green, blue}.
 * WHITE = {red, green, blue}.
 * 2 objects of ElectricColours X and Y can interact with other if and only if
 * they share one of the 3 basic colours.
 * In other words they can interact with each other if and only if
 * \f$ X \bigcap Y \neq \emptyset \f$.
 */
enum E_ELECTRICCOLOUR {
	ELECTRICCOLOUR_BLACK = 0x0,
	ELECTRICCOLOUR_RED = 0x1,
	ELECTRICCOLOUR_GREEN = 0x2,
	ELECTRICCOLOUR_YELLOW = 0x3,
	ELECTRICCOLOUR_BLUE = 0x4,
	ELECTRICCOLOUR_MAGENTA = 0x5,
	ELECTRICCOLOUR_CYAN = 0x6,
	ELECTRICCOLOUR_WHITE = 0x7
};
#define ELECTRICCOLOUR_NUM 8

/**
 * \brief		Outputs the character representation of \a ecol to \a out.
 * \details		See ElectricColour.cpp for the character representation of each ElectricColour.
 * \pre			\a out must be a working output stream.
 * \post		\a out will be the same as before, except it will have
 *				the character representation of \a ecol written to it.
 * \param		out		The output stream where \a ecol will be written.
 * \param		ecol	The ElectricColour to be written to \a out.
 * \return		A reference to the modified output stream \a out.
 * \throw		Whatever \a out throws.
 */
std::ostream& operator << ( std::ostream& out, const E_ELECTRICCOLOUR ecol );

/**
 * \brief		Reads in the character representation of \a ecol from \a in.
 * \details		See ElectricColour.cpp for the character representation of each ElectricColour.
 * \pre			\a in must be a working input stream, of which the next character to be read
 *				(excluding spaces and newlines) is one of the 8 character representations of ElectricColours.
 * \post		\a in will have advanced by one character (excluding spaces and newlines).
 *				\a ecol will have the value that was read from \a in.
 * \param		in		The input stream from which \a ecol will be read.
 * \param		ecol	A reference to the ElectricColour that will store what was read from \a in.
 * \return		A reference to the modified input stream \a in.
 * \throw		Whatever \a in throws. Also throws an exception if the character read from \a in
 *				is not one of the 8 character representations above.
 */
std::istream& operator >> ( std::istream& in, E_ELECTRICCOLOUR& ecol );

/**
 * \brief		Inverts the ElectricColour \a c.
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns the subtraction: white - \a c.
 * \param		c	The ElectricColour to be inverted.
 * \return		The result of the subtraction: white - \a c.
 */
E_ELECTRICCOLOUR operator ~ ( E_ELECTRICCOLOUR c );

/**
 * \brief		Returns the intersection of two ElectricColours.
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns an ElectricColour representing the intersection of the two arguments.
 * \param		c1	The first ElectricColour.
 * \param		c2	The second ElectricColour.
 * \return		The intersection of \a c1 and \a c2.
 */
E_ELECTRICCOLOUR operator & ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Returns the union of two ElectricColours.
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns an ElectricColour representing the union of the two arguments.
 * \param		c1	The first ElectricColour.
 * \param		c2	The second ElectricColour.
 * \return		The union of \a c1 and \a c2.
 */
E_ELECTRICCOLOUR operator | ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Returns the element-wise XOR of \a c1 and \a c2.
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns an ElectricColour c3 such that for each basic colour c,
 *				c3 contains c if and only if c1 contains c XOR c2 contains c.
 *				E.g. MAGENTA ^ CYAN = YELLOW.
 * \param		c1	The first ElectricColour.
 * \param		c2	The second ElectricColour.
 * \return		The bitwise XOR of \a c1 and \a c2.
 */
E_ELECTRICCOLOUR operator ^ ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Returns the subtraction of two ElectricColours.
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns an ElectricColour representing the subtraction of the two arguments.
 *				In other words, it returns an ElectricColour c3 such that for each basic colour c in {red, green, blue},
 *				c3 contains c if and only if c1 contains c and c2 doesn't contain c.
 * \param		c1	The first ElectricColour.
 * \param		c2	The second ElectricColour.
 * \return		The subtraction of \a c1 and \a c2.
 */
E_ELECTRICCOLOUR operator - ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Determines whether \a c is BLACK.
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns true if and only if \a c is the empty set, i.e. BLACK.
 * \param		c	The ElectricColour that may or may not be BLACK.
 * \return		True if and only if \a c is BLACK.
 */
bool operator ! ( E_ELECTRICCOLOUR c );

/**
 * \brief		Determines whether \a c1 and \a c2 share a basic colour.
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns true if and only if there exists a basic colour
 *				which is in both \a c1 and \a c2.
 * \param		c1	The first ElectricColour.
 * \param		c2	The second ElectricColour.
 * \return		True if and only if \a c1 and \a c2 share a basic colour.
 */
bool operator && ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Determines whether \a c1 and \a c2 are not both BLACK.
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns true if and only if the union of \a c1 and \c2 is non-empty,
 *				i.e. \a c1 and \a c2 are not both BLACK.
 * \param		c1	The first ElectricColour.
 * \param		c2	The second ElectricColour.
 * \return		True if and only if either \a c1 or \a c2 is not BLACK.
 */
bool operator || ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Determines whether \a c1 is a proper subset of \a c2
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns true if and only if c2 contains every basic colour that c1 contains
 *				and c1 contains strictly fewer basic colours than c2.
 * \param		c1	The ElectricColour that may or may not be a proper subset of \a c2.
 * \param		c2	The ElectricColour that may or may not be a proper superset of \a c1.
 * \return		True if and only if \a c1 is a proper subset of \a c2.
 */
bool operator < ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Determines whether \a c1 is a subset of \a c2
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns true if and only if c2 contains every basic colour that c1 contains.
 * \param		c1	The ElectricColour that may or may not be a subset of \a c2.
 * \param		c2	The ElectricColour that may or may not be a superset of \a c1.
 * \return		True if and only if \a c1 is a subset of \a c2.
 */
bool operator <= ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Determines whether \a c1 is a proper superset of \a c2
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns true if and only if c1 contains every basic colour that c2 contains
 *				and c1 contains strictly more basic colours than c2.
 * \param		c1	The ElectricColour that may or may not be a proper superset of \a c2.
 * \param		c2	The ElectricColour that may or may not be a proper subset of \a c1.
 * \return		True if and only if \a c1 is a proper superset of \a c2.
 */
bool operator > ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Determines whether \a c1 is a superset of \a c2
 * \details		Each ElectricColour represents a subset of the set {red, green, blue}.
 *				This function returns true if and only if c1 contains every basic colour that c2 contains.
 * \param		c1	The ElectricColour that may or may not be a superset of \a c2.
 * \param		c2	The ElectricColour that may or may not be a subset of \a c1.
 * \return		True if and only if \a c1 is a superset of \a c2.
 */
bool operator >= ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 );

/**
 * \brief		Turns a strings into an ElectricColour.
 * \param		c	The character representation of the ElectricColour
 * \return		The ElectricColour
 */
E_ELECTRICCOLOUR electricColourFromChar( char c );