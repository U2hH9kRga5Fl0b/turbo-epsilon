/*
 * main.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "common.h"

#include "matrix.h"
#include "latex.h"
#include "cas/simplify.h"
#include "cas/equality.h"

#define DIMENSION 2

int main(int argc, char **argv)
{

	matrix a { "a", DIMENSION, DIMENSION };
	matrix q { "q", DIMENSION, DIMENSION };

//    for (int i=DIMENSION-1;i<DIMENSION;i++)
//        a.dontknowcol(i);

//    q.at(2,2) = "X";
//    q.at(2,3) = "X";

//    q.at(0,0) = 0;
//    q.at(1,1) = 0;

	matrix qt { "q", DIMENSION, DIMENSION };
	qt = q;
	qt.transpose();
	a.hessen();

	std::ostream& out = get_latex_file("foobar.tex");

	q.append_latex(out);
	a.append_latex(out);
	qt.append_latex(out);

	matrix m = q * a;
	m.append_latex(out);
	m.simplify();
	m.append_latex(out);

	m = q * a * qt;
	m.simplify();
	m.append_latex(out);

//    begin_math(out);
//    equality{m.at(2,0), expr_ptr{new zero}}.append_latex(out);
//    end_math(out);

	begin_math(out);
	equality { q.dot(0, 0), expr_ptr { new unity } }.append_latex(out);
	end_math(out);
	begin_math(out);
	equality { q.dot(0, 1), expr_ptr { new unity } }.append_latex(out);
	end_math(out);
//    begin_math(out);
//    equality{q.dot(0,2), expr_ptr{new unity}}.append_latex(out);
//    end_math(out);
	begin_math(out);
	equality { q.dot(1, 1), expr_ptr { new unity } }.append_latex(out);
	end_math(out);

	m = q * a * q.inv();
	m.simplify();
	m.append_latex(out);
//    begin_math(out);
//    equality{q.dot(1,2), expr_ptr{new unity}}.append_latex(out);
//    end_math(out);
//    begin_math(out);
//    equality{q.dot(2,2), expr_ptr{new unity}}.append_latex(out);
//    end_math(out);

	close_latex_file(out);
}

