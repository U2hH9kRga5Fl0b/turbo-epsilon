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

expression_raw::expression_raw() {}

expression_raw::~expression_raw() {}

expr_ptr expression_raw::operator *(const expr_ptr& other) const
{
	return expr_ptr{new multiplication{clone(), other->clone()}};
}

expr_ptr expression_raw::operator /(const expr_ptr& other) const
{
	return expr_ptr{new division{clone(), other->clone()}};
}

expr_ptr expression_raw::operator +(const expr_ptr& other) const
{
	return expr_ptr{new addition{clone(), other->clone()}};
}

expr_ptr expression_raw::operator -(const expr_ptr& other) const
{
	return expr_ptr{new subtraction{clone(), other->clone()}};
}

std::ostream& expression_raw::append_text(std::ostream& out) const
{
	return out << "text not implemented for type " << type_name(get_type());
}

std::ostream& expression_raw::append_latex(std::ostream& out) const
{
	return out << "latex not implemented for type " << type_name(get_type());
}

std::ostream& expression_raw::append_matlab(std::ostream& out) const
{
	return out << "matlab not implemented for type " << type_name(get_type());
}
