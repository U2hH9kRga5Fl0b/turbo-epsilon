/*
 * variable.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "expression.h"

struct variable : public expression
{
	const std::string name;
};


#endif /* VARIABLE_H_ */
