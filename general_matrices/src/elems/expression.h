/*
 * expression.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "../common.h"

enum expr_type
{
//	CONSTANT /* =  3*/,
	//
	MULT     /* =  4*/,
	DIV      /* =  5*/,
	ADD      /* =  6*/,
	SUB      /* =  7*/,
	EXPO     /* =  8*/,
	LOG      /* =  9*/,
	NEGATE   /* = 10*/,


	//
	VARIABLE /* = 11*/,


	//
	INTERVAL /* = 12*/,
	IEEE     /* = 13*/,


	//
	REAL     /* =  1*/,
	COMPLEX  /* =  2*/,


	//
	ZERO     /* = 14*/,
	UNITY    /* = 15*/,
	ANYTHING /* = 16*/,
	NAN      /* = 17*/,
	INFINITY /* = 18*/,
};

std::string type_name(expr_type t);


class expression_raw
{
public:
	expression_raw();
	virtual ~expression_raw();

	std::string get_text() const
	{
		std::stringstream ss;
		append_text(ss);
		return ss.str();
	}

	expression_raw(const expression_raw& other) = delete;
	expression_raw& operator=(const expression_raw& other) = delete;

	virtual std::ostream& append_text(std::ostream& out) const;
	virtual std::ostream& append_latex(std::ostream& out) const;
	virtual std::ostream& append_matlab(std::ostream& out) const;

	virtual expr_type get_type() const = 0;
	virtual std::unique_ptr<expression_raw> clone() const = 0;

	std::unique_ptr<expression_raw> operator*(const std::unique_ptr<expression_raw>& other) const;
	std::unique_ptr<expression_raw> operator/(const std::unique_ptr<expression_raw>& other) const;

	std::unique_ptr<expression_raw> operator+(const std::unique_ptr<expression_raw>& other) const;
	std::unique_ptr<expression_raw> operator-(const std::unique_ptr<expression_raw>& other) const;


//	virtual void set(const expression* other) const = 0;
//	expression* operator=(const expression* other);
};

typedef std::unique_ptr<expression_raw> expr_ptr;

#endif /* EXPRESSION_H_ */
