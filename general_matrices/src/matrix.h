/*
 * matrix.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "common.h"

#include "elems/elem.h"

class matrix
{
public:
	elem elems[DIMENSION * DIMENSION];

	matrix();
	matrix(const std::string& name);

	void dontknowcol(int j);

	void hessen();
	void symm();
	void transpose();

	elem& at(int i, int j);

	friend std::ostream& operator<<(std::ostream& out, const matrix& mat);

	matrix operator *(const matrix& other) const;
};

#endif /* MATRIX_H_ */
