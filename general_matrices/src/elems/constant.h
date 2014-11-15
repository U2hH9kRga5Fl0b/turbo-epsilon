/*
 * constant.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "expression.h"

struct constant
{
	static constant ZERO;
	static constant UNITY;
	static constant UNKNOWN;
	static constant NAN;
	static constant INFINITY;
};

struct real: public constant
{
	double val;
};
struct complex: public constant
{
	double real;
	double imaginary;
};



#endif /* CONSTANT_H_ */
