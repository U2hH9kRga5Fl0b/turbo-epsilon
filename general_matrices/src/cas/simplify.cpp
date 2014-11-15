/*
 * simplify.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "simplify.h"

#include "../common.h"
#include "../elems/all_expressions.h"

namespace
{
	void simplify_zero_times(multiplication* m)
	{
	}

	void simplify(multiplication* m)
	{
	}
}


void simply_expression(expression* expr)
{
	switch(expr->get_type())
	{
		case REAL    :                                               return;
		case COMPLEX :                                               return;
		case CONSTANT:                                               return;
		case MULT    : simplify((multiplication *) expr);            return;
		case DIV     :                                               return;
		case ADD     :                                               return;
		case SUB     :                                               return;
		case EXPO    :                                               return;
		case LOG     :                                               return;
		case NEGATE  :                                               return;
		case VARIABLE:                                               return;
		case INTERVAL:                                               return;
		case IEEE    :                                               return;
		default:
			trap("Unable to simplify expression of type: " + expr->get_text());
	}
}
