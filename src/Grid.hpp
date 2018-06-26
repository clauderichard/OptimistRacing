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

/**
 * \brief		A 2d grid where each cell has a value.
 * \details		Represents a 2d grid with constant spacing (may be different for x and y) where each cell has a value.
 * \author		Claude Richard
 * \date		2012
 */
template<typename T>
class Grid2D
{
public:
	
	/**
	 * \brief		Basic constructor.
	 * \details		In this constructor, everything about the grid is specified in the arguments.
	 * \pre			The values in the \a values array must be ordered as follows:
	 *				(x1,y1), (x2,y1), (x3,y1), ... , (xm,yn).
	 * \post		This object will represent a 2d grid, with origin (originX,originY),
	 *				x-spacing gridHX, y-spacing gridHY, with
	 *				numCellsX cells along the x-axis and numCellsY cells along the y-axis.
	 *				The origin is the bottom-left corner of the grid.
	 *				This object will not hold a pointer to \a values; it simply copies the array.
	 * \param		originX		The origin's x-value, which is the smallest x-value on the grid.
	 * \param		originY		The origin's y-value, which is the smallest y-value on the grid.
	 * \param		numCellsX	The number of cells counting along the x-axis.
	 * \param		numCellsY	The number of cells counting along the y-axis.
	 * \throw		An error if \a values has length smaller than \a numCellsX * \a numCellsY.
	 *				An error if any of gridHX, gridHY, numCellsX, or numCellsY is <= 0.
	 */
	Grid2D( double originX, double originY, int numCellsX, int numCellsY, double gridHX, double gridHY, T* values )
		: mOriginX( originX )
		, mOriginY( originY )
		, mNumCellsX( numCellsX )
		, mNumCellsY( numCellsY )
		, mGridHX( gridHX )
		, mGridHY( gridHY )
	{
		mValues = new T[mNumCellsX*mNumCellsY];
		for (int i=0; i<mNumCellsX; i++) {
			for (int j=0; j<mNumCellsY; j++) {
				mValues[ i + j*mNumCellsX ] = values[ i + j*mNumCellsX ];
			}
		}
	}
	
	/**
	 * \brief		The destructor.
	 * \details		This destructor simply deletes its copy of the values array.
	 */
	~Grid2D()
	{
		delete[] mValues;
	}
	
	/**
	 * \brief		Returns the x-value of the origin of the grid (bottom-left corner).
	 * \return		The x-value of the origin of the grid (bottom-left corner).
	 */
	double getOriginX() const { return mOriginX; };

	/**
	 * \brief		Returns the y-value of the origin of the grid (bottom-left corner).
	 * \return		The y-value of the origin of the grid (bottom-left corner).
	 */
	double getOriginY() const { return mOriginY; };

	/**
	 * \brief		Returns the x-spacing of the grid (the width of each cell).
	 * \return		The x-spacing of the grid (the width of each cell).
	 */
	double getGridHX() const { return mGridHX; };

	/**
	 * \brief		Returns the y-spacing of the grid (the height of each cell).
	 * \return		The y-spacing of the grid (the height of each cell).
	 */
	double getGridHY() const { return mGridHY; };

	/**
	 * \brief		Returns the number of cells across the x-direction.
	 * \return		The number of cells across the x-direction.
	 */
	int getNumCellsX() const { return mNumCellsX; };

	/**
	 * \brief		Returns the number of cells across the y-direction.
	 * \return		The number of cells across the y-direction.
	 */
	int getNumCellsY() const { return mNumCellsY; };
	
	/**
	 * \brief		Returns the value at the cell number [i,j]
	 * \details		If i or j is off the grid, then returns the value of the closest cell.
	 * \param		i				The x-index of the cell (counting cells, not the x-value in the coordinate system).
	 * \param		j				The y-index of the cell (counting cells, not the y-value in the coordinate system).
	 * \param		defaultValue	The value to be returned if the cell-index [i,j] is outside the grid.
	 * \return		The value at the cell number [i,j].
	 *				If i or j is off the grid, then returns \a defaultValue.
	 */
	T getValue( int i, int j, T defaultValue ) const
	{
		if (i<0 || j<0 || i>=mNumCellsX || j>=mNumCellsY) {
			return defaultValue;
		}
		return mValues[ mNumCellsX * j + i ];
	}
	
	/**
	 * \brief		Returns the value at the point (x,y) (takes into account grid spacing).
	 * \details		If (x,y) is off the grid, then returns \a defaultValue.
	 * \param		x				The x-value of the point in the coordinate system.
	 * \param		y				The y-value of the point in the coordinate system.
	 * \param		defaultValue	The value to be returned if (x,y) is outside the grid.
	 * \return		The value of the cell at (x,y).
	 *				If (x,y) is off the grid, then returns \a defaultValue.
	 */
	T getValue( double x, double y, T defaultValue ) const
	{
		int floox = floor(x/mGridHX);
		int flooy = floor(y/mGridHY);
		return getValue( floox, flooy, defaultValue );
	}

private:
	
	/**
	 * \brief		The x-value of the bottom-left corner of the grid.
	 */
	double mOriginX;
	
	/**
	 * \brief		The y-value of the bottom-left corner of the grid.
	 */
	double mOriginY;
	
	/**
	 * \brief		The x-spacing of the grid, i.e. the height of each cell.
	 */
	double mGridHX;
	
	/**
	 * \brief		The y-spacing of the grid, i.e. the width of each cell.
	 */
	double mGridHY;
	
	/**
	 * \brief		The number of cells counting across the x-axis.
	 */
	int mNumCellsX;
	
	/**
	 * \brief		The number of cells counting across the y-axis.
	 */
	int mNumCellsY;
	
	/**
	 * \brief		Array of the values of the cells.
	 * \details		The cells are ordered as follows: (x1,y1), (x2,y1), (x3,y1), ... , (xm,yn).
	 */
	T* mValues;
};