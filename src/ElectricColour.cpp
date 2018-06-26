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

#include "ElectricColour.hpp"

// The following macro definitions must match the documentation of the functions in ElectricColour.hpp.
// Changing these is not recommended, as you would have to change all the files with ElectricColours in them.

/// The character representation of ELECTRICCOLOUR_BLACK.
#define CHAR_BLACK 'N'
/// The character representation of ELECTRICCOLOUR_RED.
#define CHAR_RED 'R'
/// The character representation of ELECTRICCOLOUR_GREEN.
#define CHAR_GREEN 'G'
/// The character representation of ELECTRICCOLOUR_BLUE.
#define CHAR_BLUE 'B'
/// The character representation of ELECTRICCOLOUR_YELLOW.
#define CHAR_YELLOW 'Y'
/// The character representation of ELECTRICCOLOUR_MAGENTA.
#define CHAR_MAGENTA 'M'
/// The character representation of ELECTRICCOLOUR_CYAN.
#define CHAR_CYAN 'C'
/// The character representation of ELECTRICCOLOUR_WHITE.
#define CHAR_WHITE 'W'


std::ostream& operator << ( std::ostream& out, const E_ELECTRICCOLOUR ecol )
{
	// Output the character representation of ecol to out.
	// Then return out.
	switch( ecol ) {
	case ELECTRICCOLOUR_BLACK: return (out << CHAR_BLACK);
	case ELECTRICCOLOUR_RED: return (out << CHAR_RED);
	case ELECTRICCOLOUR_GREEN: return (out << CHAR_GREEN);
	case ELECTRICCOLOUR_BLUE: return (out << CHAR_BLUE);
	case ELECTRICCOLOUR_YELLOW: return (out << CHAR_YELLOW);
	case ELECTRICCOLOUR_MAGENTA: return (out << CHAR_MAGENTA);
	case ELECTRICCOLOUR_CYAN: return (out << CHAR_CYAN);
	case ELECTRICCOLOUR_WHITE: return (out << CHAR_WHITE);
	}
}


std::istream& operator >> ( std::istream& in, E_ELECTRICCOLOUR& ecol )
{
	char c;
	// Skip all the spaces, newlines, and tabs,
	// and read the first character that is something else.
	do {
		in >> c;
	} while ( c==' ' || c=='\n' || c=='\t' );
	// Update ecol according to the character read, then return in.
	switch( c ) {
	case CHAR_BLACK: ecol = ELECTRICCOLOUR_BLACK; return in;
	case CHAR_RED: ecol = ELECTRICCOLOUR_RED; return in;
	case CHAR_GREEN: ecol = ELECTRICCOLOUR_GREEN; return in;
	case CHAR_BLUE: ecol = ELECTRICCOLOUR_BLUE; return in;
	case CHAR_YELLOW: ecol = ELECTRICCOLOUR_YELLOW; return in;
	case CHAR_MAGENTA: ecol = ELECTRICCOLOUR_MAGENTA; return in;
	case CHAR_CYAN: ecol = ELECTRICCOLOUR_CYAN; return in;
	case CHAR_WHITE: ecol = ELECTRICCOLOUR_WHITE; return in;
	}
	// If you're here then the character you read was not
	// one of the 8 we're looking for, so throw an error.
	// TODO: throw something that makes more sense here.
	throw -1;
}

E_ELECTRICCOLOUR operator ~ ( E_ELECTRICCOLOUR c )
{
	// TODO
	// Use the ~ operator for unsigned char.
	return static_cast<E_ELECTRICCOLOUR>( ~static_cast<unsigned char>(c) & 0x7 );
}

E_ELECTRICCOLOUR operator & ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Use the & operator for unsigned char.
	return static_cast<E_ELECTRICCOLOUR>( static_cast<unsigned char>(c1) & static_cast<unsigned char>(c2) );
}

E_ELECTRICCOLOUR operator | ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Use the | operator for unsigned char.
	return static_cast<E_ELECTRICCOLOUR>( static_cast<unsigned char>(c1) | static_cast<unsigned char>(c2) );
}

E_ELECTRICCOLOUR operator ^ ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Use the ^ operator for unsigned char.
	return static_cast<E_ELECTRICCOLOUR>( static_cast<unsigned char>(c1) ^ static_cast<unsigned char>(c2) );
}

E_ELECTRICCOLOUR operator - ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Return c1 & ~c2 since you want each bit i of the result to be 1 iff c1[i] is 1 and c2[i] is not 1.
	return static_cast<E_ELECTRICCOLOUR>( static_cast<unsigned char>(c1) & ~static_cast<unsigned char>(c2) );
}

bool operator ! ( E_ELECTRICCOLOUR c )
{
	// Return true iff c is BLACK.
	return c==ELECTRICCOLOUR_BLACK;
}

bool operator && ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Return true iff c1 and c2 share a basic colour.
	return (static_cast<unsigned char>(c1) & static_cast<unsigned char>(c2) ) != 0;
}

bool operator || ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Return true iff at least one of the arguments isn't black.
	return ( c1!=ELECTRICCOLOUR_BLACK || c2!=ELECTRICCOLOUR_BLACK );
}

bool operator < ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Return true if for each bit position i, b1[i] -> b2[i],
	// i.e. b1[i] && !b2[i] is false for all i.
	// An additional requirement for returning true is that c1 != c2.
	return ( (~static_cast<unsigned char>(c2) & static_cast<unsigned char>(c1)) == 0 ) &&
			 ( c1 != c2 );
}

bool operator <= ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Return true if for each bit position i, b1[i] -> b2[i],
	// i.e. b1[i] && !b2[i] is false for all i.
	return ( (~static_cast<unsigned char>(c2) & static_cast<unsigned char>(c1)) == 0 );
}

bool operator > ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Return true if for each bit position i, b2[i] -> b1[i],
	// i.e. b2[i] && !b1[i] is false for all i.
	// An additional requirement for returning true is that c1 != c2.
	return ( (~static_cast<unsigned char>(c1) & static_cast<unsigned char>(c2)) == 0 ) &&
			 ( c1 != c2 );
}

bool operator >= ( E_ELECTRICCOLOUR c1, E_ELECTRICCOLOUR c2 )
{
	// Return true if for each bit position i, b2[i] -> b1[i],
	// i.e. b2[i] && !b1[i] is false for all i.
	return ( (~static_cast<unsigned char>(c1) & static_cast<unsigned char>(c2)) == 0 );
}

E_ELECTRICCOLOUR electricColourFromChar( char c )
{
	switch( c ) {
	case CHAR_BLACK: return ELECTRICCOLOUR_BLACK;
	case CHAR_RED: return ELECTRICCOLOUR_RED;
	case CHAR_GREEN: return ELECTRICCOLOUR_GREEN;
	case CHAR_BLUE: return ELECTRICCOLOUR_BLUE;
	case CHAR_YELLOW: return ELECTRICCOLOUR_YELLOW;
	case CHAR_MAGENTA: return ELECTRICCOLOUR_MAGENTA;
	case CHAR_CYAN: return ELECTRICCOLOUR_CYAN;
	case CHAR_WHITE: return ELECTRICCOLOUR_WHITE;
	}
	throw -1;
}