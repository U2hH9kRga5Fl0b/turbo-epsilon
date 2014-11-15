/*
 * file.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "file.h"


#include <stdio.h>


file::file(const boost::filesystem::path& path_) :
	path{path_},
	byte_sum{-1}
	{}
file::file(const std::string& path_) : file {absolute(boost::filesystem::path{path_})} {}

file::~file() {}


std::ostream& file::append_to(std::ostream& out, int depth) const
{
	for (int i = 0; i < depth; i++)
		out << WHITESPACE;
	return out << get_name();
}

std::string file::get_name() const
{
	return path.filename().string();
}

bool file::operator <(const file& f) const
{
	return path < f.path;
}

bool file::operator ==(const file& f) const
{
	return path == f.path;
}

bool file::contents_match(const file& other) const
{
	if (!boost::filesystem::exists(other.path))
		return false;
	if (!boost::filesystem::exists(path))
		return false;
	if (boost::filesystem::file_size(path) != boost::filesystem::file_size(other.path))
		return false;
	if (byte_sum >= 0 && other.byte_sum >= 0 && byte_sum != other.byte_sum)
		return false;

	int sum = 0;
	int last_byte = 0;

	FILE *f1 = fopen(      path.string().c_str(), "r");
	FILE *f2 = fopen(other.path.string().c_str(), "r");

	do
	{
		last_byte = fgetc(f1);
		int other_byte = fgetc(f2);

		if (last_byte != other_byte)
		{
			fclose(f1);
			fclose(f2);
			return false;
		}
		sum += last_byte;

	} while (last_byte >= 0);

	byte_sum = sum;
	other.byte_sum = sum;

	fclose(f1);
	fclose(f2);

	return true;
}
