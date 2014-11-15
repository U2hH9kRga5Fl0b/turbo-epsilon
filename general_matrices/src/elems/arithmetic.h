/*
 * arithmetic.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "expression.h"



struct binary : public expression
{
	expression* first;
	expression* second;

//	binary() : first{nullptr}, second{nullptr} {}
	binary(expression* e1, expression* e2) : first{e1}, second{e2} {}
	~binary() { delete first; delete second; }
};

struct exponent : public binary
{
	exponent(expression* e1, expression* e2) : binary{e1, e2} {}
	expr_type get_type() const { return EXPO; }
	expression* clone() const { return new exponent{first->clone(), second->clone()}; }
};

struct multiplication : public binary
{
	multiplication(expression* e1, expression* e2) : binary{e1, e2} {}
	expr_type get_type() const { return MULT; }
	expression* clone() const { return new multiplication{first->clone(), second->clone()}; }
};
struct division : public binary
{
	division(expression* e1, expression* e2) : binary{e1, e2} {}
	expr_type get_type() const { return DIV; }
	expression* clone() const { return new division{first->clone(), second->clone()}; }
};

struct addition : public binary
{
	addition(expression* e1, expression* e2) : binary{e1, e2} {}
	expr_type get_type() const { return ADD; }
	expression* clone() const { return new addition{first->clone(), second->clone()}; }
};
struct subtraction : public binary
{
	subtraction(expression* e1, expression* e2) : binary{e1, e2} {}
	expr_type get_type() const { return SUB; }
	expression* clone() const { return new subtraction{first->clone(), second->clone()}; }
};

struct negation
{
	negation(expression* e) : orig{e} {}
	expression* orig;
};


#endif /* ARITHMETIC_H_ */
