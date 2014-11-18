/*
 * variable.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "expression.h"

struct variable : public expression_raw
{
	const std::string mat;
	int idx1, idx2;

	variable(const std::string& name);
	variable(const std::string& mat, int row, int col);

	bool operator==(const variable& v);
	bool operator==(const expr_ptr& v);

	std::ostream& append_text(std::ostream& out) const;
	std::ostream& append_latex(std::ostream& out) const;
	std::ostream& append_matlab(std::ostream& out) const;

	expr_type get_type() const;
	expr_ptr clone() const;
};


#endif /* VARIABLE_H_ */
