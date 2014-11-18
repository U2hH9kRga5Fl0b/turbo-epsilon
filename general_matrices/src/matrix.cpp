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
	elems { new expr_ptr[rows * cols] }
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			set(i, j, expr_ptr{new variable { name, i, j }});
}
matrix::matrix(const matrix& mat) :
	rows { mat.rows },
	cols { mat.cols },
	elems { new expr_ptr[rows * cols] }
{
	for (int i = 0; i < rows * cols; i++)
		set(i, mat.elems[i]);
}

matrix::~matrix()
{
	delete[] elems;
}

void matrix::dontknowcol(int j)
{
	for (int i = 0; i < rows; i++)
	{
		set(i, j, expr_ptr{new anything});
	}
}

void matrix::hessen()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (i - 1 > j)
				set(i, j, expr_ptr{new zero});
}

void matrix::symm()
{
	if (rows != cols)
		trap("symmetric matrices are square");
	for (int i = 0; i < rows; i++)
		for (int j = i + 1; j < cols; j++)
			set(i, j, at(j, i));
}

void matrix::transpose()
{
	if (rows != cols)
		trap("not implemented...");
	for (int i = 0; i < rows; i++)
		for (int j = i + 1; j < cols; j++)
		{
			at(i, j).swap(at(j, i));
		}
}
const expr_ptr& matrix::at(int i, int j) const
{
	return elems[i * rows + j];
}
expr_ptr& matrix::at(int i, int j)
{
	return elems[i * rows + j];
}

void matrix::set(int i, int j, expr_ptr& expr)
{
	set(i * rows + j, expr);
}

void matrix::set(int idx, expr_ptr& expr)
{
	elems[idx] = expr->clone();
}

void matrix::set(int i, int j, expr_ptr&& expr)
{
	set(i * rows + j, expr);
}

void matrix::set(int idx, expr_ptr&& expr)
{
	elems[idx] = expr_ptr{expr.release()};
}

std::ostream& matrix::append_text(std::ostream& out)
{
	return out << (*this);
}

std::ostream& matrix::append_latex(std::ostream& out)
{
	out << "\\[\\left( \\begin{array} {";
	for (int i=0;i<cols;i++) out << "c";
	out << "}\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			at(i, j)->append_latex(out) << ((j == cols - 1) ? " \\\\\n" : " & " );
	}

	out << "\\end{array} \\right)\\]\n\n";
	return out;
}

std::ostream& matrix::append_matlab(std::ostream& out)
{
	return out;
}

expr_ptr matrix::dot(int col1, int col2) const
{

	expr_ptr sum{new zero};

	for (int i = 0; i < rows; i++)
	{
		sum = sum->operator+(at(i, col1)->operator*(at(i, col2)));
	}

	return sum;
}

matrix matrix::inv()
{
	if (rows == cols && rows == 2)
	{
		matrix mat{"i", 2, 2};
		expr_ptr d = det();
		mat.set(0,0, at(1,1)->operator/(d));
		mat.set(1,1, at(0,0)->operator/(d));
		mat.set(0,1, negation{at(1,0)}.operator/(d));
		mat.set(1,0, negation{at(0,1)}.operator/(d));
		return mat;
	}
	trap("bad dims");
	return matrix{*this};
}

expr_ptr matrix::det()
{
	if (rows == cols && rows == 2)
	{
		return (at(0, 0)->operator *(at(1, 1)))->operator -((at(0, 1)->operator *(at(1, 0))));
	}
	trap("bad dims");
	return expr_ptr{new zero};
}

matrix matrix::operator *(const matrix& other) const
{
	if (other.rows != cols)
		trap("bad multiplication dimensions");

	matrix output {"this doesn't matter", rows, other.cols};
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < other.cols; j++)
		{
			expr_ptr sum {new zero};
			for (int k = 0; k < cols; k++)
			{
				sum = (*sum) + ((*elems[i * rows + k]) * other.elems[k * other.rows + j]);
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
			out << std::setw(max) << mat.at(i, j)->get_text() << "\t";
		out << '\n';
	}

	return out;
}

void matrix::simplify()
{
	for (int i = 0; i < rows * cols; i++)
		elems[i] = simplify_expression(elems[i]);
}

matrix& matrix::operator =(const matrix& other)
{
	if (rows != other.rows || cols != other.cols)
	{
		delete[] elems;
		rows = other.rows;
		cols = other.cols;
		elems = new expr_ptr[rows * cols];
	}
	for (int i = 0; i < rows * cols; i++)
		elems[i] = other.elems[i]->clone();
	return (*this);
}
