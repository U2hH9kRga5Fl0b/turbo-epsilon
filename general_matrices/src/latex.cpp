/*
 * latex_header.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: thallock
 */

#include "latex.h"

#include <fstream>

std::ostream& get_latex_file(const std::string& file)
{
	std::ofstream *ofstream = new std::ofstream{file};
	(*ofstream) << "\\documentclass{article}\n";
	(*ofstream) << "\\title{article}\n";
	(*ofstream) << "\\begin{document}\n";
	(*ofstream) << "\\section{some math}\n";
	return *ofstream;
}


void close_latex_file(std::ostream& ofstream)
{
	ofstream << "\\end{document}\n";
	delete &ofstream;
}

std::ostream& begin_math(std::ostream& ofstream)
{
	return ofstream << "\\[";
}

std::ostream& end_math(std::ostream& ofstream)
{
	return ofstream << "\\]\n\n";
}
