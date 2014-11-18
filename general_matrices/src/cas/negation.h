/*
 * negation.h
 *
 *  Created on: Nov 15, 2014
 *      Author: thallock
 */

#ifndef NEGATION_H_
#define NEGATION_H_


expr_ptr simplify_neg(Negation&& neg, bool& changed)
{
	return expr_ptr{neg.release()};
}


#endif /* NEGATION_H_ */
