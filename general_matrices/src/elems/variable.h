/*
 * variable.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "expression.h"

struct variable : public expression
{
	const std::string mat;
	int idx1, idx2;

	variable(const std::string& name);
	variable(const std::string& mat, int row, int col);

	std::ostream& append_text(std::ostream& out) const;
	std::ostream& append_latex(std::ostream& out) const;
	std::ostream& append_matlab(std::ostream& out) const;

	expr_type get_type() const;
	expression* clone() const;
};


#endif /* VARIABLE_H_ */
