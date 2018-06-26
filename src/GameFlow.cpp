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
//#include "GameFlow.hpp"
//#include <GL\glew.h>
//#include <GL\freeglut.h>
//
//GameFlow::GameFlow()
//{
//	// Set up the camera
//	glMatrixMode( GL_PROJECTION );
//	glLoadIdentity();
//	gluPerspective( 90, 1.0*400/400, 0.01, 500 );
//
////	// Set up the orientation of faces:
////	// Vertices go counterclockwise for the front face.
////	glFrontFace( GL_CCW );
////	// don't show the backs of faces (inside an object)
////	// This is necessary if the camera goes into an object.
////	glEnable( GL_CULL_FACE );
////	glCullFace( GL_BACK );
//
//}
//
//GameFlow::~GameFlow()
//{
//}
//
//void GameFlow::step( double seconds )
//{
//
//}
//
//void GameFlow::render( double seconds )
//{
//
//}