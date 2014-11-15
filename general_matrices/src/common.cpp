/*
 * common.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "common.h"

void trap(const std::string& msg)
{
	std::cerr << msg << std::endl;
	exit(-1);
}

std::string str(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}
