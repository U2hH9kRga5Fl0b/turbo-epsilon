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
}

expr_ptr recursive_apply(expr_ptr& expr, expr_ptr (simplifier)(expr_ptr& expr, bool&), bool& mod)
{
	switch(expr->get_type())
	{
		case MULT     : { binary*b=(binary*) expr.release(); expr = Binary{new multiplication{ recursive_apply(b->first, simplifier, mod), recursive_apply(b->second, simplifier, mod) }}; break; }
		case DIV      : { binary*b=(binary*) expr.release(); expr = Binary{new division      { recursive_apply(b->first, simplifier, mod), recursive_apply(b->second, simplifier, mod) }}; break; }
		case ADD      : { binary*b=(binary*) expr.release(); expr = Binary{new addition      { recursive_apply(b->first, simplifier, mod), recursive_apply(b->second, simplifier, mod) }}; break; }
		case SUB      : { binary*b=(binary*) expr.release(); expr = Binary{new subtraction   { recursive_apply(b->first, simplifier, mod), recursive_apply(b->second, simplifier, mod) }}; break; }
		case EXPO     : { break; }
		case LOG      : { break; }
		case NEGATE   : { Negation n{(negation*) expr.release()}; expr = recursive_apply(n->orig, simplifier, mod); break; }
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

expr_ptr simplify_an_expression(expr_ptr& expr, bool& mod)
{
//	expr->append_text(std::cout << "simplifying: ") << std::endl;
	switch(expr->get_type())
	{
		case REAL    : /* return simplify     (Real           {(real           *) expr.release()}, mod); */ break;
		case COMPLEX : /* return simplify     (Complex        {(complex        *) expr.release()}, mod); */ break;
		case MULT    :    return  simplify_mult(Multiplication {(multiplication *) expr.release()}, mod);
		case DIV     : /* return simplify     (Division       {(division       *) expr.release()}, mod); */ break;
		case ADD     :    return simplify_add (Addition       {(addition       *) expr.release()}, mod);
		case SUB     : /* return simplify     (Subtraction    {(subtraction    *) expr.release()}, mod); */ break;
		case EXPO    : /* return simplify     (Exponent       {(exponent       *) expr.release()}, mod); */ break;
		case NEGATE  :    return simplify_neg (Negation       {(negation       *) expr.release()}, mod);
		case VARIABLE: /* return simplify     (Variable       {(variable       *) expr.release()}, mod); */ break;

		case LOG     : /* return simplify     (expr_ptr       {(expression_raw *) expr.release()}, mod); */ break;
		case INTERVAL: /* return simplify     (expr_ptr       {(expression_raw *) expr.release()}, mod); */ break;
		case IEEE    : /* return simplify     (expr_ptr       {(expression_raw *) expr.release()}, mod); */ break;

		case ZERO    : /* return expr_ptr{expr.release()};                                               */ break;
		case UNITY   : /* return expr_ptr{expr.release()};                                               */ break;
		case ANYTHING: /* return expr_ptr{expr.release()};                                               */ break;
		case NAN     : /* return expr_ptr{expr.release()};                                               */ break;
		case INFINITY: /* return expr_ptr{expr.release()};                                               */ break;
		default:
			trap("Unable to simplify expression of type: " + expr->get_text());
	}
	return expr_ptr{expr.release()};
}

expr_ptr simplify_expression(expr_ptr&& expr)
{
	expr_ptr arg{expr.release()};
	return simplify_expression(arg);
}

expr_ptr simplify_expression(expr_ptr& expr)
{

	bool mod;
	do
	{
		mod = false;
		expr = recursive_apply(expr, simplify_an_expression, mod);
	} while (mod);
	return expr_ptr{expr.release()};
}

