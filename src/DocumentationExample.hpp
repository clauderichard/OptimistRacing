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
#include <algorithm>
#include <cmath>


/**
 * \details	This namespace contains the code necessary for documenting files.
 *			You should really use this for all your code.
 */
namespace DocumentationExample {

/**
 * \brief		Pretty nice constant.
 * \details		This constant is used to demonstrate a number of section commands.
 * \author		John Doe
 * \author		Jan Doe
 * \date		2008-2019
 * \pre			First initialize the system.
 * \bug			This number is not very accurate.
 * \warning		Believing this nonsense constant can result in severe confusion.
 */
#define WHATTHEHELL 55.9554


/**
 * \brief		Pretty nice class.
 * \details		This class is used to demonstrate a number of section commands.
 * \author		John Doe
 * \author		Jan Doe
 * \version		4.1a
 * \date		2012-2018
 * \pre			First initialize the system.
 * \warning		Improper use can crash your application
 * \invariant	This class's x value never changes!
 * \bug			Not all memory is freed when deleting an object of this class.
 * \todo		Make the class better.
 */
class SomeNiceClass
{
public:

	/**
	 * \brief		Pretty nice constructor.
	 * \details		This constructor is used to demonstrate a number of section commands.
	 * \pre			You must initialize the system first.
	 * \post		The object will have the values x and y.
	 * \param[in]	x	The 1st value in the class.
	 * \param[in]	y	The 2nd value in the class.
	 * \throw		An error when y is a prime integer.
	 * \bug			An error occurs if \a y is equal to 42,003,583.
	 * \todo		Make the method better by passing in another argument.
	 */
	SomeNiceClass( double x, double y );

	/**
	 * \brief		Pretty nice destructor.
	 * \details		This constructor is used to demonstrate documentation of a destructor in a class.
	 * \pre			You must initialize the system first.
	 * \post		The entire computer will be destroyed in a firey blaze, not just this object.
	 * \throw		An error when something goes wrong in the destructor.
	 * \bug			The error occurs when it's not supposed to.
	 * \todo		Make the method better by passing in another argument.
	 */
	~SomeNiceClass();
	
	/**
	 * \brief		Pretty nice function of an integer.
	 * \details		This constructor is used to demonstrate documentation of a function in a class.
	 * \pre			\a a must be positive.
	 * \post		The object will have the value a stored in its x value for some reason.
	 * \param		a	The integer you want to evaluate the function of.
	 * \return		The function of \a a.
	 * \throw		An error when a is negative.
	 * \bug			An error occurs if \a a is equal to 42,003,583.
	 * \todo		Make the method better by passing in another argument.
	 */
	double function1( int a );
	
private:

	/**
	 * \brief		Pretty nice private variable.
	 * \details		This constructor is used to demonstrate documentation of a function in a class.
	 * \invariant	This class's x value never changes!
	 * \todo		Change the type of this variable to int.
	 */
	double mValueX;
};


/**
 * \brief		Pretty nice function of two integers.
 * \details		This function is used to demonstrate a global function documentation section.
 * \pre			\a b must be positive.
 * \post		The object will have the value \a b stored in its y value for some reason.
 * \param		a	The first integer you want to evaluate the function of.
 * \param		b	The second integer you want to evaluate the function of.
 * \return		The function of \a a and \a b.
 * \throw		An error when \a b is negative.
 * \bug			An error occurs if \a a is equal to 42,003,583.
 * \todo		Make the method better by passing in another argument.
 */
double function2( int a, int b );

} // namespace DocumentationExample