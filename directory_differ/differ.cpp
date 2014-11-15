/*
 * differ.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "directory.h"


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << argv[0] << ": <directory1> <directory2>" << std::endl;
		return -1;
	}
	directory dir1 { argv[1] };
	directory dir2 { argv[2] };

	dir1.remove([](const file& file) { return file.get_name().at(0) == '.'; });
	dir2.remove([](const file& file) { return file.get_name().at(0) == '.'; });

	dir1.diff(dir2, std::cout) << std::endl;

	return 0;
}
