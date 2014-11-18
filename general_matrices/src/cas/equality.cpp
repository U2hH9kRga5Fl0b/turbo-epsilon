/*
 * equality.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: thallock
 */

#include "equality.h"

#include "simplify.h"


struct contains_var
{
	Variable var;

	expr_ptr operator()(const expr_ptr& expr, bool& has_var)
	{
		if (expr->get_type() == VARIABLE)
		{
			has_var |= (*var) == expr;
		}
		return expr_ptr { expr->clone() };
	}
};

equality::equality(const expr_ptr& lhs, const expr_ptr& rhs) :
	left{simplify_expression(lhs->clone())},
	right{simplify_expression(rhs->clone())} {}

equality::~equality() {}

expr_ptr equality::solve(Variable& var)
{
	expr_ptr ret;

	return ret;
}

std::ostream& equality::append_text(std::ostream& out) const
{
	return right->append_text(left->append_text(out) << "=");
}

std::ostream& equality::append_latex(std::ostream& out) const
{
	return right->append_latex(left->append_latex(out) << "=");
}

std::ostream& equality::append_matlab(std::ostream& out) const
{
	return right->append_matlab(left->append_matlab(out) << "=");
}
