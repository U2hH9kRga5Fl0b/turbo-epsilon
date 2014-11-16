/*
 * simplify. cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "simplify.h"

#include "../common.h"
#include "../elems/all_expressions.h"

#include <functional>

namespace
{
	#include "multiplication.h"
	#include "division.h"
	#include "addition.h"
	#include "subtraction.h"
	#include "negation.h"

	// default catch case if there is no simplify found in the above rules
	expression* simplify(expression* expr, bool& mod)
	{
		return expr;
	}

	expression* recursive_apply(expression* expr, expression* (simplifier)(expression*, bool&), bool& mod)
	{
		switch(expr->get_type())
		{
			case MULT     : { binary*   b=(binary*)   expr; b->first = recursive_apply(b->first, simplifier, mod); b->second = recursive_apply(b->second, simplifier, mod); break; }
			case DIV      : { binary*   b=(binary*)   expr; b->first = recursive_apply(b->first, simplifier, mod); b->second = recursive_apply(b->second, simplifier, mod); break; }
			case ADD      : { binary*   b=(binary*)   expr; b->first = recursive_apply(b->first, simplifier, mod); b->second = recursive_apply(b->second, simplifier, mod); break; }
			case SUB      : { binary*   b=(binary*)   expr; b->first = recursive_apply(b->first, simplifier, mod); b->second = recursive_apply(b->second, simplifier, mod); break; }
			case EXPO     : { binary*   b=(binary*)   expr; b->first = recursive_apply(b->first, simplifier, mod); b->second = recursive_apply(b->second, simplifier, mod); break; }
			case LOG      : { binary*   b=(binary*)   expr; b->first = recursive_apply(b->first, simplifier, mod); b->second = recursive_apply(b->second, simplifier, mod); break; }
			case NEGATE   : { negation* n=(negation*) expr; recursive_apply(n->orig, simplifier, mod); break; }
			case VARIABLE : { break; }
			case INTERVAL : { break; }
			case IEEE     : { break; }
			case REAL     : { break; }
			case COMPLEX  : { break; }
			case ZERO     : { break; }
			case UNITY    : { break; }
			case ANYTHING : { break; }
			case NAN      : { break; }
			case INFINITY : { break; }
			default:
				trap("Unable to simplify expression of type: " + expr->get_text());
		}
		return simplifier(expr, mod);
	}
}

expression* simplify_an_expression(expression* expr, bool& mod)
{
	switch(expr->get_type())
	{
		case REAL    : return simplify((real           *) expr, mod);
		case COMPLEX : return simplify((complex        *) expr, mod);
		case MULT    : return simplify((multiplication *) expr, mod);
		case DIV     : return simplify((division       *) expr, mod);
		case ADD     : return simplify((addition       *) expr, mod);
		case SUB     : return simplify((subtraction    *) expr, mod);
		case EXPO    : return simplify((exponent       *) expr, mod);
		case NEGATE  : return simplify((negation       *) expr, mod);
		case VARIABLE: return simplify((variable       *) expr, mod);

		case LOG     : return simplify((expression     *) expr, mod);
		case INTERVAL: return simplify((expression     *) expr, mod);
		case IEEE    : return simplify((expression     *) expr, mod);
		default:
			trap("Unable to simplify expression of type: " + expr->get_text());
	}
	return expr;
}

expression* simplify_expression(expression* expr)
{

	bool mod;
	do
	{
		mod = false;
		expr = recursive_apply(expr, simplify_an_expression, mod);
	} while (mod);
	return expr;
}
