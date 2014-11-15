/*
 * matrix.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "matrix.h"

#include <iomanip>
#include <climits>

matrix::matrix() {}

matrix::matrix(const std::string& name)
{
	for (int i = 0; i < DIMENSION; i++)
		for (int j = 0; j < DIMENSION; j++)
			elems[i * DIMENSION + j] = elem { name, i, j };
}

void matrix::dontknowcol(int j)
{
	for (int i = 0; i < DIMENSION; i++)
		elems[i * DIMENSION + j] = "X";

}

void matrix::hessen()
{
	for (int i = 0; i < DIMENSION; i++)
		for (int j = 0; j < DIMENSION; j++)
			if (i - 1 > j)
				elems[i * DIMENSION + j] = 0;
}

void matrix::symm()
{
	for (int i = 0; i < DIMENSION; i++)
		for (int j = i + 1; j < DIMENSION; j++)
			elems[i * DIMENSION + j] = elems[j * DIMENSION + i];
}

void matrix::transpose()
{
	for (int i = 0; i < DIMENSION; i++)
		for (int j = i + 1; j < DIMENSION; j++)
		{
			elem tmp = elems[i * DIMENSION + j];
			elems[i * DIMENSION + j] = elems[j * DIMENSION + i];
			elems[j * DIMENSION + i] = tmp;
		}
}

elem& matrix::at(int i, int j)
{
	return elems[i * DIMENSION + j];
}

matrix matrix::operator *(const matrix& other) const
{
	matrix output;
	for (int i = 0; i < DIMENSION; i++)
		for (int j = 0; j < DIMENSION; j++)
		{
			elem sum = 0;
			for (int k = 0; k < DIMENSION; k++)
			{
				elem prod = elems[i * DIMENSION + k] * other.elems[k * DIMENSION + j];
				sum = sum + prod;
			}
			output.elems[i * DIMENSION + j] = sum;
		}
	return output;
}

std::ostream& operator<<(std::ostream& out, const matrix& mat)
{
	int max = INT_MIN;
	for (int i = 0; i < DIMENSION * DIMENSION; i++)
		if (mat.elems[i].text_size() > max)
			max = mat.elems[i].text_size();

	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
			out << std::setw(max) << mat.elems[i * DIMENSION + j].value << "\t";
		out << '\n';
	}

	return out;
}
