/*
 * common.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <sstream>

#define DIMENSION 2

void trap(const std::string& msg);

std::string str(int i);


#endif /* COMMON_H_ */



#if 0

q[2,1]      =  (q[2,2]*a[2,1]*q[1,1]+q[2,2]*a[2,2]*q[1,2]) / (a[1,1]+a[1,2])




q[2,2]*a[2,1]*q[1,1]*q[2,2]*a[2,2]*q[1,2] + q[2,2]*a[2,2]*q[1,2]*q[2,2]*a[2,2]*q[1,2] +
q[2,2]*a[2,1]*q[1,1]*q[2,2]*a[2,1]*q[1,1] + q[2,2]*a[2,2]*q[1,2]*q[2,2]*a[2,1]*q[1,1]
/
(a[1,1]a[1,1]+a[1,2]*a[1,2] + 2 * a[1,1]*a[1,2])

+ q[]




a = rand(2,2)
q = [1, 1; 1 -1];
q(2,1) = -(q(2,2)*a(2,1)*q(1,1)+q(2,2)*a(2,2)*q(1,2)) / (a(1,1)+a(1,2))
q * a * q'



#endif
