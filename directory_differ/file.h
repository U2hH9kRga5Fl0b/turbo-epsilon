/*
 * file.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef FILE_H_
#define FILE_H_

#include <iostream>

#define WHITESPACE ' '

#include <boost/filesystem.hpp>


class file
{
public:
	boost::filesystem::path path;
	mutable long byte_sum;

	file(const boost::filesystem::path& path);
	file(const std::string& path);

	virtual ~file();

	virtual std::ostream& append_to(std::ostream& out, int depth=0) const;

	virtual std::string get_name() const;

	bool operator<(const file& f) const;
	bool operator==(const file& f) const;

	bool contents_match(const file& other) const;
};

extern file& FILE_DOESNT_EXIST;

#endif /* FILE_H_ */
