/*
 * variable.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "variable.h"
//#include "all_expressions.h"

variable::variable(const std::string& name_) :
	mat{mat},
	idx1{-1},
	idx2{-1} {}

variable::variable(const std::string& mat, int row, int col) :
	mat{mat},
	idx1{row},
	idx2 { col } {}

std::ostream& variable::append_text(std::ostream& out) const
{
	if (idx1 == idx2 && idx1 == -1)
		return out << mat;
	return out << mat << "[" << (idx1) << "," << (idx2) << "]";
}

std::ostream& variable::append_latex(std::ostream& out) const
{
	if (idx1 == idx2 && idx1 == -1)
		return out << mat;
	return out << mat << "_{" << (idx1 + 1) << "," << (idx2 + 1) << "}";
}

std::ostream& variable::append_matlab(std::ostream& out) const
{
	if (idx1 == idx2 && idx1 == -1)
		return out << mat;
	return out << mat << "(" << (idx1 + 1) << "," << (idx2 + 1) << ")";
}

expr_type variable::get_type() const
{
	return VARIABLE;
}

expr_ptr variable::clone() const
{
	return expr_ptr{new variable { mat, idx1, idx2 }};
}

bool variable::operator ==(const variable& v)
{
	return idx1 == v.idx1 && idx2 == v.idx2 && mat == v.mat;
}

bool variable::operator ==(const expr_ptr& p)
{
	if (p->get_type() != VARIABLE)
	{
		return false;
	}
	return (*this) == (*      (variable *) (&(*p)));
}
