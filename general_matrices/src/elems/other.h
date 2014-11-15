/*
 * other.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef OTHER_H_
#define OTHER_H_


#include "expression.h"

struct interval : public expression
{
	expression* lower;
	expression* upper;
};




struct ieee : public expression
{
	expression* value;
	bool epsilon;
};

#endif /* OTHER_H_ */
