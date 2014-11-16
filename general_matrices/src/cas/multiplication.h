/*
 * multiplication.h
 *
 *  Created on: Nov 15, 2014
 *      Author: thallock
 */

#ifndef MULTIPLICATION_H_
#define MULTIPLICATION_H_

expression* simplify(multiplication* m, bool& mod)
{
	if (m->first->get_type() == NAN || m->second->get_type() == NAN)
	{
		delete m;
		return new nan;
	}

	if (m->first->get_type() == INFINITY || m->second->get_type() == INFINITY)
	{
		// Could be zero, even if it is not ZERO
		if (m->first->get_type() == ZERO || m->second->get_type() == ZERO)
		{
			delete m;
			return new nan;
		}
		else
		{
			delete m;
			return new infinity;
		}
	}

	if (m->first->get_type() == ANYTHING || m->second->get_type() == ANYTHING)
	{
		delete m;
		return new anything;
	}

	if (m->first->get_type() == UNITY)
	{
		expression* ret = m->second;
		m->second = nullptr;
		delete m;
		return ret;
	}
	if (m->second->get_type() == UNITY)
	{
		expression* ret = m->first;
		m->first = nullptr;
		delete m;
		return ret;
	}

	if (m->first->get_type() == ZERO || m->second->get_type() == ZERO)
	{
		delete m;
		return new zero { };
	}

	return m;
}

#endif /* MULTIPLICATION_H_ */
