/*
 * constant.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "expression.h"

struct real: public expression_raw
{
	real (double v) : val{v} {}

	expr_type get_type() const { return REAL; }
	expr_ptr clone() const { return expr_ptr{new real{val}}; }

	std::ostream& append_text(std::ostream& out) const
	{
		return out << val;
	}

	std::ostream& append_latex(std::ostream& out) const
	{
		return out << val;
	}

	std::ostream& append_matlab(std::ostream& out) const
	{
		return out << val;
	}
#if 0
	inline real operator*(const real& other) const
	{
		return real { val * other.val };
	}

	inline real operator/(const real& other) const
	{
		return real { val / other.val };
	}

	inline real operator+(const real& other) const
	{
		return real { val + val };
	}

	inline real operator-(const real& other) const
	{
		return real { val - other.val };
	}
#endif

	double val;
};

struct complex: public expression_raw
{
	complex (double r, double i) : real{r}, imaginary{i} {}

	std::ostream& append_text(std::ostream& out) const
	{
		return out << real << "+" << imaginary << "i";
	}

	std::ostream& append_latex(std::ostream& out) const
	{
		return out << real << "+" << imaginary << "i";
	}

	std::ostream& append_matlab(std::ostream& out) const
	{
		return out << real << "+" << imaginary << "i";
	}

	expr_type get_type() const { return COMPLEX; }
	expr_ptr clone() const { return expr_ptr{new complex{real, imaginary}}; }

#if 0
	inline complex operator*(const complex& other) const
	{
		return complex {
			real * other.real - imaginary * other.imaginary,
			real * other.imaginary + imaginary * other.real };
	}

	inline complex operator/(const complex& other) const
	{
		return complex {
			(real * other.real + imaginary * other.imaginary) / (other.real * other.real + other.imaginary * other.imaginary),
			(real * other.imaginary - imaginary * other.real) / (other.real * other.real + other.imaginary * other.imaginary) };
	}

	inline complex operator+(const complex& other) const
	{
		return complex { real + other.real, imaginary + other.imaginary };
	}

	inline complex operator-(const complex& other) const
	{
		return complex { real - other.real, imaginary - other.imaginary };
	}
#endif

	double real;
	double imaginary;
};

class special_constant : public expression_raw
{
	virtual std::ostream& append_latex(std::ostream& out) const { return append_text(out); }
	virtual std::ostream& append_matlab(std::ostream& out) const { return append_text(out); }
};

class zero: public special_constant
{
	std::ostream& append_text(std::ostream& out) const { return out << "0"; }

	expr_type get_type() const { return ZERO; };
	expr_ptr clone() const {return expr_ptr{new zero}; };
};
class unity: public special_constant
{
	std::ostream& append_text(std::ostream& out) const { return out << "1"; }

	expr_type get_type() const { return UNITY; };
	expr_ptr clone() const {return expr_ptr{new unity}; };
};
class anything: public special_constant
{
	std::ostream& append_text(std::ostream& out) const { return out << "X"; }
//	std::ostream& append_matlab(std::ostream& out) const { return out << "rand()"; }

	expr_type get_type() const { return ANYTHING; };
	expr_ptr clone() const {return expr_ptr{new anything}; };
};
class nan: public special_constant
{
	std::ostream& append_text(std::ostream& out) const { return out << "NAN"; }

	expr_type get_type() const { return NAN; };
	expr_ptr clone() const {return expr_ptr{new nan}; };
};
class infinity: public special_constant
{
	std::ostream& append_text(std::ostream& out) const { return out << "inf"; }
	std::ostream& append_latex(std::ostream& out) const { return out << "\\inf"; }

	expr_type get_type() const { return INFINITY; };
	expr_ptr clone() const {return expr_ptr{new infinity}; };
};



#endif /* CONSTANT_H_ */
