/*
 * elem.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef ELEM_H_
#define ELEM_H_

#include "../common.h"




class elem
{
public:
	    std::string value;

	    elem();
	    elem(int i);
	    elem(const std::string& val);
	    elem(const std::string& mat, int i, int j);

	    int text_size() const;

	    bool is_one() const;
	    bool is_zero() const;
	    bool is_unknown() const;

	    elem& operator=(int val);
	    elem& operator=(const std::string& val);
	    elem operator* (const elem& other) const;
	    elem operator+ (const elem& other) const;
};



#endif /* ELEM_H_ */
