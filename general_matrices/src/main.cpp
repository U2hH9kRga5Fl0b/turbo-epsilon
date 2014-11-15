/*
 * main.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */



#include "common.h"

#include "matrix.h"

int main(int argc, char **argv)
{

    matrix a {"a"};
    matrix q {"q"};

//    for (int i=DIMENSION-1;i<DIMENSION;i++)
//        a.dontknowcol(i);

//    q.at(2,2) = "X";
//    q.at(2,3) = "X";

//    q.at(0,0) = 0;
//    q.at(1,1) = 0;

    matrix qt;
    qt = q;
    qt.transpose();
    a.hessen();


    std::cout << a << std::endl;
    std::cout << q << std::endl;
    std::cout << qt << std::endl;

    std::cout << q*a << std::endl;
    std::cout << q*a*qt << std::endl;
}

