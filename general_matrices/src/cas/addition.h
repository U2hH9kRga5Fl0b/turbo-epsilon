/*
 * addition.h
 *
 *  Created on: Nov 15, 2014
 *      Author: thallock
 */

#ifndef ADDITION_H_
#define ADDITION_H_


// ()+(-()) = ()-()


expr_ptr simplify_add(Addition&& a, bool& mod)
{
	if (a->first->get_type() == NAN || a->second->get_type() == NAN)
	{
		return Nan{new nan};
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
			return Infinity{new infinity};
//		}
	}

	if (a->first->get_type() == ANYTHING || a->second->get_type() == ANYTHING)
	{
		return Anything{new anything};
	}

	if (a->first->get_type() == ZERO)
	{
		expr_ptr ret {a->second.release()};
		a->first = nullptr;
		return ret;
	}
	if (a->second->get_type() == ZERO)
	{
		expr_ptr ret {a->first.release()};
		a->first = nullptr;
		return ret;
	}

	return expr_ptr{a.release()};
}



#endif /* ADDITION_H_ */
