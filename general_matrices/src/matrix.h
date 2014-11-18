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
	expr_ptr *elems;

	matrix(const std::string& name, int rows, int cols);
	~matrix();

	matrix(const matrix& other);
	matrix& operator=(const matrix& other);

	void dontknowcol(int j);

	void hessen();
	void symm();
	void transpose();
	matrix inv();
	expr_ptr det();

	const expr_ptr& at(int i, int j) const;
	expr_ptr& at(int i, int j);
	void set(int i, int j, expr_ptr& expr);
	void set(int idx, expr_ptr& expr);
	void set(int i, int j, expr_ptr&& expr);
	void set(int idx, expr_ptr&& expr);

	friend std::ostream& operator<<(std::ostream& out, const matrix& mat);

	void simplify();


	expr_ptr dot(int col1, int col2) const;

	std::ostream& append_text(std::ostream& out);
	std::ostream& append_latex(std::ostream& out);
	std::ostream& append_matlab(std::ostream& out);

	matrix operator *(const matrix& other) const;
};

#endif /* MATRIX_H_ */
