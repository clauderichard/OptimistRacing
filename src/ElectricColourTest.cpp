///*	Copyright (C) 2012  Claude Richard
// *
// *	Optimist Racing is free software: you can redistribute it and/or modify
// *	it under the terms of the GNU General Public License as published by
// *	the Free Software Foundation, either version 3 of the License, or
// *	(at your option) any later version.
// *
// *	Optimist Racing is distributed in the hope that it will be useful,
// *	but WITHOUT ANY WARRANTY; without even the implied warranty of
// *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *	GNU General Public License for more details.
// *
// *	You should have received a copy of the GNU General Public License
// *	along with Optimist Racing.  If not, see <http://www.gnu.org/licenses/>.
// */
//
//// This is the main program.
//// It has a loop that deals with the event queue, and updates and renders the game.
//// Right now there are a lot of hardcoded things in here,
////   that should be moved to different objects.
//
//#define BOOST_TEST_MODULE ElectricColourTest
//#include <boost/test/unit_test.hpp>
//#include "ElectricColour.hpp"
//
//
//**
// * Test c1 && c2
// */
//BOOST_AUTO_TEST_CASE( operatorDoubleAmpersand )
//{
//	// Check same colour. Should all be true except for black.
//	for (unsigned char i=0; i<ELECTRICCOLOUR_NUM; i++) {
//		if (i==ELECTRICCOLOUR_BLACK) {
//			BOOST_CHECK( ! ( static_cast<E_ELECTRICCOLOUR>(i) && static_cast<E_ELECTRICCOLOUR>(i) ) );
//		} else {
//			BOOST_CHECK( static_cast<E_ELECTRICCOLOUR>(i) && static_cast<E_ELECTRICCOLOUR>(i) );
//		}
//	}
//	// Check black against everything. Should all be false.
//	for (unsigned char i=0; i<ELECTRICCOLOUR_NUM; i++) {
//		BOOST_CHECK( ! ( ELECTRICCOLOUR_BLACK && static_cast<E_ELECTRICCOLOUR>(i) ) );
//		BOOST_CHECK( ! ( static_cast<E_ELECTRICCOLOUR>(i) && ELECTRICCOLOUR_BLACK ) );
//	}
//	// Check white against everything. Should all be true except for black.
//	for (unsigned char i=0; i<ELECTRICCOLOUR_NUM; i++) {
//		if (i==ELECTRICCOLOUR_BLACK) {
//			BOOST_CHECK( ! ( ELECTRICCOLOUR_WHITE && static_cast<E_ELECTRICCOLOUR>(i) ) );
//			BOOST_CHECK( ! ( static_cast<E_ELECTRICCOLOUR>(i) && ELECTRICCOLOUR_WHITE ) );
//		} else {
//			BOOST_CHECK( ELECTRICCOLOUR_WHITE && static_cast<E_ELECTRICCOLOUR>(i) );
//			BOOST_CHECK( static_cast<E_ELECTRICCOLOUR>(i) && ELECTRICCOLOUR_WHITE );
//		}
//	}
//	// Check single colour vs. another single colour. Should all be false.
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_RED && ELECTRICCOLOUR_GREEN ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_GREEN && ELECTRICCOLOUR_RED ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_RED && ELECTRICCOLOUR_BLUE ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_BLUE && ELECTRICCOLOUR_RED ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_GREEN && ELECTRICCOLOUR_BLUE ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_BLUE && ELECTRICCOLOUR_GREEN ) );
//	// Check single colour vs. opposite colour. Should all be false.
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_RED && ELECTRICCOLOUR_CYAN ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_CYAN && ELECTRICCOLOUR_RED ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_GREEN && ELECTRICCOLOUR_MAGENTA ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_MAGENTA && ELECTRICCOLOUR_GREEN ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_BLUE && ELECTRICCOLOUR_YELLOW ) );
//	BOOST_CHECK( ! ( ELECTRICCOLOUR_YELLOW && ELECTRICCOLOUR_BLUE ) );
//	// Check single colour vs. double colour including it. Should all be true.
//	BOOST_CHECK( ELECTRICCOLOUR_RED && ELECTRICCOLOUR_YELLOW );
//	BOOST_CHECK( ELECTRICCOLOUR_YELLOW && ELECTRICCOLOUR_RED );
//	BOOST_CHECK( ELECTRICCOLOUR_RED && ELECTRICCOLOUR_MAGENTA );
//	BOOST_CHECK( ELECTRICCOLOUR_MAGENTA && ELECTRICCOLOUR_RED );
//	BOOST_CHECK( ELECTRICCOLOUR_GREEN && ELECTRICCOLOUR_YELLOW );
//	BOOST_CHECK( ELECTRICCOLOUR_GREEN && ELECTRICCOLOUR_CYAN );
//	// Check double colour vs. another double colour. Should all be true.
//	BOOST_CHECK( ELECTRICCOLOUR_YELLOW && ELECTRICCOLOUR_MAGENTA );
//	BOOST_CHECK( ELECTRICCOLOUR_MAGENTA && ELECTRICCOLOUR_YELLOW );
//	BOOST_CHECK( ELECTRICCOLOUR_YELLOW && ELECTRICCOLOUR_CYAN );
//	BOOST_CHECK( ELECTRICCOLOUR_CYAN && ELECTRICCOLOUR_YELLOW );
//	BOOST_CHECK( ELECTRICCOLOUR_MAGENTA && ELECTRICCOLOUR_CYAN );
//	BOOST_CHECK( ELECTRICCOLOUR_CYAN && ELECTRICCOLOUR_MAGENTA );
//}
//
////BOOST_AUTO_TEST_CASE( myTest )
////{
////    // seven ways to detect and report the same error:
////    BOOST_CHECK( ! ( ELECTRICCOLOUR_RED && ELECTRICCOLOUR_GREEN ) );
////
////    BOOST_REQUIRE( add( 2,2 ) == 4 );      // #2 throws on error
////
////    if( add( 2,2 ) != 4 )
////      BOOST_ERROR( "Ouch..." );            // #3 continues on error
////
////    if( add( 2,2 ) != 4 )
////      BOOST_FAIL( "Ouch..." );             // #4 throws on error
////
////    if( add( 2,2 ) != 4 ) throw "Ouch..."; // #5 throws on error
////
////    BOOST_CHECK_MESSAGE( add( 2,2 ) == 4,  // #6 continues on error
////                         "add(..) result: " << add( 2,2 ) );
////
////    BOOST_CHECK_EQUAL( ELECTRICCOLOUR_RED, 4 );	  // #7 continues on error
////}