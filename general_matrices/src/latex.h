/*
 * latex.h
 *
 *  Created on: Nov 17, 2014
 *      Author: thallock
 */

#ifndef LATEX_H_
#define LATEX_H_

#include "common.h"

std::ostream& get_latex_file(const std::string& file);
void close_latex_file(std::ostream& ofstream);

std::ostream& begin_math(std::ostream&ofstream);
std::ostream& end_math(std::ostream&ofstream);


#endif /* LATEX_H_ */
