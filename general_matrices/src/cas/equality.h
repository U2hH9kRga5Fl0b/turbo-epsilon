/*
 * equality.h
 *
 *  Created on: Nov 17, 2014
 *      Author: thallock
 */

#ifndef EQUALITY_H_
#define EQUALITY_H_

#include "../elems/all_expressions.h"


class equality
{
public:
	expr_ptr left;
	expr_ptr right;

	equality(const expr_ptr& lhs, const expr_ptr& rhs);
	virtual ~equality();

	expr_ptr solve(Variable& var);

	std::ostream& append_text(std::ostream& out) const;
	std::ostream& append_latex(std::ostream& out) const;
	std::ostream& append_matlab(std::ostream& out) const;
};

#endif /* EQUALITY_H_ */
