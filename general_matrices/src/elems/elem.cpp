/*
 * elem.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "elem.h"

#include <iomanip>





elem::elem(int i) :
	elem { "" }
{
	(*this) = i;
}

elem::elem() {}

elem::elem(const std::string& val) :
		value { val } {}
elem::elem(const std::string& mat, int i, int j) :
		value { mat + "[" + str(i) + "," + str(j) + "]" } {}

int elem::text_size() const
{
	return value.size();
}

bool elem::is_one() const
{
	return value == "1";
}

bool elem::is_zero() const
{
	return value == "0";
}

bool elem::is_unknown() const
{
	return value == "X";
}

elem& elem::operator=(int val)
{
	value = str(val);
	return *this;
}
elem& elem::operator=(const std::string& val)
{
	value = val;
	return *this;
}

elem elem::operator*(const elem& other) const
{
	if (is_zero() || other.is_zero())
	{
		return elem { "0" };
	}
	if (is_one())
	{
		return elem { other.value };
	}
	if (other.is_one())
	{
		return elem { value };
	}
	if (is_unknown() || other.is_unknown())
	{
		return elem { "X" };
	}

	std::stringstream ss;
	ss << value << '*' << other.value;
	return elem { ss.str() };
}
elem elem::operator+(const elem& other) const
{
	if (is_zero())
	{
		return elem { other.value };
	}
	if (other.is_zero())
	{
		return elem { value };
	}
	if (is_unknown() || other.is_unknown())
	{
		return elem { "X" };
	}
	std::stringstream ss;
	ss << value << '+' << other.value;
	return elem { ss.str() };
}

