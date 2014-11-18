/*
 * all_expressions.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef ALL_EXPRESSIONS_H_
#define ALL_EXPRESSIONS_H_


#include "expression.h"

#include "arithmetic.h"
#include "variable.h"
#include "constant.h"

typedef std::unique_ptr<expression_raw> expr_ptr;

typedef std::unique_ptr<multiplication> Multiplication;
typedef std::unique_ptr<division>       Division;
typedef std::unique_ptr<addition>       Addition;
typedef std::unique_ptr<subtraction>    Subtraction;
typedef std::unique_ptr<negation>       Negation;
typedef std::unique_ptr<exponent>       Exponent;

typedef std::unique_ptr<variable>       Variable;

typedef std::unique_ptr<zero>           Zero;
typedef std::unique_ptr<unity>          Unity;
typedef std::unique_ptr<anything>       Anything;
typedef std::unique_ptr<nan>            Nan;
typedef std::unique_ptr<infinity>       Infinity;

typedef std::unique_ptr<binary>         Binary;

typedef std::unique_ptr<real>           Real;
typedef std::unique_ptr<complex>        Complex;

#if 0
// to do
INTERVAL /* = 12*/,
IEEE     /* = 13*/,
#endif


#endif /* ALL_EXPRESSIONS_H_ */
