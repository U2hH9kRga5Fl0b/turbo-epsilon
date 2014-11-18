/*
 * other.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef OTHER_H_
#define OTHER_H_


#include "expression.h"

struct interval : public expression_raw
{
	expr_ptr lower;
	expr_ptr upper;
};




struct ieee : public expression_raw
{
	expr_ptr value;
	bool epsilon;
};

#endif /* OTHER_H_ */
