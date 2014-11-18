/*
 * multiplication.h
 *
 *  Created on: Nov 15, 2014
 *      Author: thallock
 */

#ifndef MULTIPLICATION_H_
#define MULTIPLICATION_H_

expr_ptr simplify_mult(Multiplication&& m, bool& mod)
{
	if (m->first->get_type() == NAN || m->second->get_type() == NAN)
	{
		return Nan{new nan};
	}

	if (m->first->get_type() == INFINITY || m->second->get_type() == INFINITY)
	{
		// Could be zero, even if it is not ZERO
		if (m->first->get_type() == ZERO || m->second->get_type() == ZERO)
		{
			return Nan{new nan};
		}
		else
		{
			return Infinity{new infinity};
		}
	}

	if (m->first->get_type() == ANYTHING || m->second->get_type() == ANYTHING)
	{
		return Anything{new anything};
	}

	if (m->first->get_type() == UNITY)
	{
		expr_ptr ret {m->second.release()};
		m->second = nullptr;
		return ret;
	}
	if (m->second->get_type() == UNITY)
	{
		expr_ptr ret {m->first.release()};
		m->first = nullptr;
		return ret;
	}

	if (m->first->get_type() == ZERO || m->second->get_type() == ZERO)
	{
		return Zero{new zero};
	}

	return expr_ptr{m.release()};
}

#endif /* MULTIPLICATION_H_ */
