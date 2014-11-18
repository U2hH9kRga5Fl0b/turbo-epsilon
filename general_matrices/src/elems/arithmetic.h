/*
 * arithmetic.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "expression.h"


struct binary : public expression_raw
{
	expr_ptr first;
	expr_ptr second;

	binary() : first{nullptr}, second{nullptr} {}
	binary(const expr_ptr& e1, const expr_ptr& e2) : first{e1->clone()}, second{e2->clone()} {}

protected:
	std::string llp() const
	{
		if (needs_parens(get_type(), first->get_type()))
				return "(";
		return "";
	}
	std::string lrp() const
	{
		if (needs_parens(get_type(), first->get_type()))
				return ")";
		return "";
	}

	std::string rlp() const
	{
		if (needs_parens(get_type(), second->get_type()))
				return "(";
		return "";
	}
	std::string rrp() const
	{
		if (needs_parens(get_type(), second->get_type()))
				return ")";
		return "";
	}

private:
	bool needs_parens(expr_type me, expr_type inn) const
	{
		if (inn == VARIABLE) return false;
		if (me == ADD && inn == MULT) return false;
		if (me == SUB && inn == MULT) return false;
		if (me == ADD && inn == ADD) return false;
		return true;
	}
};
struct exponent : public binary
{
	exponent(const expr_ptr& e1, const expr_ptr& e2) : binary{e1, e2} {}
	expr_type get_type() const { return EXPO; }
	expr_ptr clone() const { return expr_ptr{new exponent{first, second}}; }

	// these are mesed up....
	std::ostream& append_text(std::ostream& out) const   { return second->append_text(  first->append_text(  out        << llp()) << lrp() << "^")   << rrp();}
	std::ostream& append_latex(std::ostream& out) const  { return second->append_latex( first->append_latex( out << "{" << llp()) << lrp() << "}^{") << rrp() << "}"; }
	std::ostream& append_matlab(std::ostream& out) const { return second->append_matlab(first->append_matlab(out        << llp()) << lrp() << "^")   << rrp(); }
};
struct multiplication : public binary
{
	multiplication(const expr_ptr& e1, const expr_ptr& e2) : binary{e1, e2} {}
	expr_type get_type() const { return MULT; }
	expr_ptr clone() const { return expr_ptr{new multiplication{first->clone(), second->clone()}}; }

	std::ostream& append_text(std::ostream& out) const   { return second->append_text(  first->append_text(  out << llp()) << lrp() << "*" << rlp()) << rrp(); }
	std::ostream& append_latex(std::ostream& out) const  { return second->append_latex( first->append_latex( out << llp()) << lrp() << " " << rlp()) << rrp(); }
	std::ostream& append_matlab(std::ostream& out) const { return second->append_matlab(first->append_matlab(out << llp()) << lrp() << "*" << rlp()) << rrp(); }
};
struct division : public binary
{
	division(const expr_ptr& e1, const expr_ptr& e2) : binary{e1, e2} {}
	expr_type get_type() const { return DIV; }
	expr_ptr clone() const { return expr_ptr{new division{first->clone(), second->clone()}}; }

	std::ostream& append_text(std::ostream& out) const   { return second->append_text(  first->append_text(  out << llp()) << lrp() << "/(") << rrp(); }
	std::ostream& append_latex(std::ostream& out) const  { return second->append_latex( first->append_latex( out << "\\frac{") << "}{") << "}"; }
	std::ostream& append_matlab(std::ostream& out) const { return second->append_matlab(first->append_matlab(out << llp()) << lrp() << "/(") << rrp(); }
};
struct addition : public binary
{
	addition(const expr_ptr& e1, const expr_ptr& e2) : binary{e1, e2} {}
	expr_type get_type() const { return ADD; }
	expr_ptr clone() const { return expr_ptr{new addition{first->clone(), second->clone()}}; }

	std::ostream& append_text(std::ostream& out) const   { return second->append_text(  first->append_text(  out << llp()) << lrp() << " + " << rlp()) << rrp(); }
	std::ostream& append_latex(std::ostream& out) const  { return second->append_latex( first->append_latex( out << llp()) << lrp() << " + " << rlp()) << rrp(); }
	std::ostream& append_matlab(std::ostream& out) const { return second->append_matlab(first->append_matlab(out << llp()) << lrp() << " + " << rlp()) << rrp(); }
};
struct subtraction : public binary
{
	subtraction(const expr_ptr& e1, const expr_ptr& e2) : binary{e1, e2} {}
	expr_type get_type() const { return SUB; }
	expr_ptr clone() const { return expr_ptr{new subtraction{first->clone(), second->clone()}}; }

	std::ostream& append_text(std::ostream& out) const   { return second->append_text(  first->append_text(  out << llp()) << lrp() << " - " << rlp()) << rrp(); }
	std::ostream& append_latex(std::ostream& out) const  { return second->append_latex( first->append_latex( out << llp()) << lrp() << " - " << rlp()) << rrp(); }
	std::ostream& append_matlab(std::ostream& out) const { return second->append_matlab(first->append_matlab(out << llp()) << lrp() << " - " << rlp()) << rrp(); }
};
struct negation : public expression_raw
{
	negation(const expr_ptr& e) : orig{e->clone()} {}
	expr_type get_type() const { return NEGATE; }
	expr_ptr clone() const { return expr_ptr{new negation{orig}}; }

	std::ostream& append_text(std::ostream& out) const   { return orig->append_text(  out << "(-(") << "))"; }
	std::ostream& append_latex(std::ostream& out) const  { return orig->append_latex( out << "(-(") << "))"; }
	std::ostream& append_matlab(std::ostream& out) const { return orig->append_matlab(out << "(-(") << "))"; }

	expr_ptr orig;
};


#endif /* ARITHMETIC_H_ */
