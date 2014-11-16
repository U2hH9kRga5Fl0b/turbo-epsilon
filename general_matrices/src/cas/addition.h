/*
 * addition.h
 *
 *  Created on: Nov 15, 2014
 *      Author: thallock
 */

#ifndef ADDITION_H_
#define ADDITION_H_


// ()+(-()) = ()-()


expression* simplify(addition* a, bool& mod)
{
	if (a->first->get_type() == NAN || a->second->get_type() == NAN)
	{
		delete a;
		return new nan;
	}

	if (a->first->get_type() == INFINITY || a->second->get_type() == INFINITY)
	{
		// Could be zero, even if it is not ZERO
//		if (a->first->get_type() == negative infinity || a->second->get_type() == negative infinity)
//		{
//			delete a;
//			return new nan;
//		}
//		else
//		{
			delete a;
			return new infinity;
//		}
	}

	if (a->first->get_type() == ANYTHING || a->second->get_type() == ANYTHING)
	{
		delete a;
		return new anything;
	}

	if (a->first->get_type() == ZERO)
	{
		expression* ret = a->second;
		a->second = nullptr;
		delete a;
		return ret;
	}
	if (a->second->get_type() == ZERO)
	{
		expression* ret = a->first;
		a->first = nullptr;
		delete a;
		return ret;
	}

	return a;
}



#endif /* ADDITION_H_ */
