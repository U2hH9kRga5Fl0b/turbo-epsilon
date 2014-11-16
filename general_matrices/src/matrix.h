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

#include "elems/all_expressions.h"

class matrix
{
public:
	int rows, cols;
	expression **elems;

	matrix(const std::string& name, int rows, int cols);
///	matrix(const char *name, int rows, int cols) : matrix(std::string{name}, rows, cols) {}
	~matrix();

	matrix(const matrix& other);
	matrix& operator=(const matrix& other);

	void dontknowcol(int j);

	void hessen();
	void symm();
	void transpose();

	const expression* at(int i, int j) const;
	expression* at(int i, int j);
	void set(int i, int j, expression* expr);
	void set(int idx, expression* expr);

	friend std::ostream& operator<<(std::ostream& out, const matrix& mat);

	void simplify();

	matrix operator *(const matrix& other) const;
};

#endif /* MATRIX_H_ */
