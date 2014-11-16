/*
 * expression.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "expression.h"

#include "all_expressions.h"



std::string type_name(expr_type t)
{
	switch (t)
	{
		case MULT     : return "MULT    ";
		case DIV      : return "DIV     ";
		case ADD      : return "ADD     ";
		case SUB      : return "SUB     ";
		case EXPO     : return "EXPO    ";
		case LOG      : return "LOG     ";
		case NEGATE   : return "NEGATE  ";
		case VARIABLE : return "VARIABLE";
		case INTERVAL : return "INTERVAL";
		case IEEE     : return "IEEE    ";
		case REAL     : return "REAL    ";
		case COMPLEX  : return "COMPLEX ";
		case ZERO     : return "ZERO    ";
		case UNITY    : return "UNITY   ";
		case ANYTHING : return "ANYTHING";
		case NAN      : return "NAN     ";
		case INFINITY : return "INFINITY";
	}
	return "unknown type";
}

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
	return out << "text not implemented for type " << type_name(get_type());
}

std::ostream& expression::append_latex(std::ostream& out) const
{
	return out << "latex not implemented for type " << type_name(get_type());
}

std::ostream& expression::append_matlab(std::ostream& out) const
{
	return out << "matlab not implemented for type " << type_name(get_type());
}
