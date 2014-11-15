/*
 * expression.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "expression.h"

#include "all_expressions.h"

expression::expression() {}

expression::~expression() {}

expression* expression::operator *(const expression* other) const
{
	return new multiplication{clone(), other->clone()};
}

expression* expression::operator /(const expression* other) const
{
	return new division{clone(), other->clone()};
}

expression* expression::operator +(const expression* other) const
{
	return new addition{clone(), other->clone()};
}

expression* expression::operator -(const expression* other) const
{
	return new subtraction{clone(), other->clone()};
}

std::ostream& expression::append_text(std::ostream& out) const
{
	return out << "text not implemented for type " << get_type();
}

std::ostream& expression::append_latex(std::ostream& out) const
{
	return out << "latex not implemented for type " << get_type();
}
