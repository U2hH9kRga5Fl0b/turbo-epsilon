/*
 * matrix.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "matrix.h"

#include "common.h"
#include "cas/simplify.h"

#include <iomanip>
#include <climits>


matrix::matrix(const std::string& name, int rows_, int cols_) :
	rows { rows_ },
	cols { cols_ },
	elems { new expression *[rows * cols] }
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			elems[i * rows + j] = new variable { name, i, j };
}
matrix::matrix(const matrix& mat) :
	rows { mat.rows },
	cols { mat.cols },
	elems { new expression *[rows * cols] }
{
	for (int i = 0; i < rows * cols; i++)
		elems[i * rows + cols] = mat.elems[i * rows + cols]->clone();
}

matrix::~matrix()
{
	for (int i = 0; i < rows * cols; i++)
		delete elems[i * rows + cols];
	delete[] elems;
}

void matrix::dontknowcol(int j)
{
	for (int i = 0; i < rows; i++)
	{
		set(i, j,  new anything{});
	}
}

void matrix::hessen()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (i - 1 > j)
				set(i, j, new zero{});
}

void matrix::symm()
{
	if (rows != cols)
		trap("symmetric matrices are square");
	for (int i = 0; i < rows; i++)
		for (int j = i + 1; j < cols; j++)
			set(i, j, at(j, i)->clone());
}

void matrix::transpose()
{
	if (rows != cols)
		trap("not implemented...");
	for (int i = 0; i < rows; i++)
		for (int j = i + 1; j < cols; j++)
		{
			expression* tmp = elems[i * rows + j];
			elems[i * rows + j] = elems[j * rows + i];
			elems[j * rows + i] = tmp;
		}
}
const expression* matrix::at(int i, int j) const
{
	return elems[i * rows + j];
}
expression* matrix::at(int i, int j)
{
	return elems[i * rows + j];
}

void matrix::set(int i, int j, expression* expr)
{
	set(i * rows + j, expr);
}

void matrix::set(int idx, expression* expr)
{
	delete elems[idx];
	elems[idx] = expr;
}

matrix matrix::operator *(const matrix& other) const
{
	if (other.rows != cols)
		trap("bad multiplication dimensions");

	matrix output{"this doesn't matter", rows, other.cols};
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < other.cols; j++)
		{
			expression * sum = new zero();
			for (int k = 0; k < cols; k++)
			{
				sum = (*sum)+(   (*elems[i * rows + k]) * other.elems[k * rows + j]);
			}
			output.set(i, j, sum);
		}
	return output;
}

std::ostream& operator<<(std::ostream& out, const matrix& mat)
{
	int max = INT_MIN;
	for (int i = 0; i < mat.rows * mat.cols; i++)
	{
		max = std::max(max, (int) mat.elems[i]->get_text().size());
	}

	for (int i = 0; i < mat.rows; i++)
	{
		for (int j = 0; j < mat.cols; j++)
			out << std::setw(max) << mat.elems[i * mat.rows + j]->get_text() << "\t";
		out << '\n';
	}
;
	return out;
}

void matrix::simplify()
{
	for (int i = 0; i < rows * cols; i++)
		elems[i] = simplify_expression(elems[i]);
}

matrix& matrix::operator =(const matrix& other)
{
	for (int i = 0; i < rows * cols; i++)
		delete elems[i * rows + cols];
	delete[] elems;

	rows = other.rows;
	cols = other.cols;
	for (int i = 0; i < rows * cols; i++)
		elems[i * rows + cols] = other.elems[i * rows + cols]->clone();
	return (*this);
}
