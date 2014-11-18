/*
 * simplify.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef SIMPLIFY_H_
#define SIMPLIFY_H_

#include "../elems/expression.h"

expr_ptr recursive_apply(expr_ptr& expr, expr_ptr (func)(expr_ptr& expr, bool&), bool& mod);

expr_ptr simplify_expression(expr_ptr& expr);
expr_ptr simplify_expression(expr_ptr&& expr);

#endif /* SIMPLIFY_H_ */
