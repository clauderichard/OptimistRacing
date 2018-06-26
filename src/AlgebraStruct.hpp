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

/**
 * \file
 * This file defines structs that contain matrices and vectors.
 * These structs are intended to be returned from functions where
 * you need to compute several matrices/vectors,
 * but you need to compute them in the same function to avoid repeating some code.
 */

#include "Algebra.hpp"

/// This struct holds one MatrixMxN and one VectorND.
struct Matrix1Vector1 {

	/// The matrix.
	const MatrixMxN&	mMatrix;
	/// The vector.
	const VectorND&		mVector;

	/// The constructor.
	Matrix1Vector1( const MatrixMxN& mMatrix, const VectorND& mVector );
};