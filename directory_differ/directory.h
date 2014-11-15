/*
 * directory.h
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include "file.h"

#include <list>
#include <functional>

class directory : public file
{
public:
	std::list<directory> children;
	std::list<file> files;

	directory(const char *path);
	directory(const std::string& path);
	directory(const boost::filesystem::path& path);
	~directory();

	file& get_regular_file(const std::string& filename);
	directory& get_directory(const std::string& filename);
	const file& get_regular_file(const std::string& filename) const;
	const directory& get_directory(const std::string& filename) const;

	void remove(std::function<bool(const file& file)> predicate);
	void apply(std::function<void(directory& dir)> function);

	std::ostream& append_to(std::ostream& out, int depth=0) const;
	std::ostream& diff(const directory& other, std::ostream& out, int depth=0) const;

	virtual std::string get_name() const;
};

#endif /* DIRECTORY_H_ */
