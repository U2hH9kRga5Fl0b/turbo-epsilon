/*
 * directory.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: thallock
 */

#include "directory.h"

#include <algorithm>
#include <set>

directory DIRECTORY_DOESNT_EXIST{"doesn't exist"};
file& FILE_DOESNT_EXIST = DIRECTORY_DOESNT_EXIST;

directory::directory(const boost::filesystem::path& path_) :
	file {path_}
{
	if (!boost::filesystem::exists(path))
		return;

	boost::filesystem::directory_iterator end_itr;

	for (boost::filesystem::directory_iterator itr{path}; itr != end_itr; ++itr)
	{
		if (boost::filesystem::is_regular_file(itr->path()))
		{
			files.push_back(file{itr->path()});
		}
		else
		{
			children.push_back(directory{itr->path().string()});
		}
	}

	children.sort();
	files.sort();
}

directory::directory(const std::string& path_) :
	directory{absolute(boost::filesystem::path{path_})} {}
directory::directory(const char *path_) :
	directory{std::string{path_}} {}

directory::~directory() {}

std::ostream& directory::append_to(std::ostream& out, int depth) const
{
	for (int i = 0; i < depth; i++)
		out << WHITESPACE;
	out << get_name() << '\n';

	{
		auto end = files.end();
		for (auto it = files.begin(); it != end; ++it)
			it->append_to(out /*<< "F: "*/, depth + 1) << '\n';
	}

//	for (int i = 0; i < depth; i++)
//		out << WHITESPACE;
//	out << '-' << '\n';

	{
		auto end = children.end();
		for (auto it = children.begin(); it != end; ++it)
			it->append_to(out /*<< "D: "*/, depth + 1);
	}

	return out;
}

void directory::remove(std::function<bool(const file& file)> predicate)
{
	apply([&predicate](directory& dir)
	{
		dir.files.remove_if(predicate);
		dir.children.remove_if(predicate);
	});
}

void directory::apply(std::function<void(directory& dir)> function)
{
	function(*this);
	std::for_each(children.begin(), children.end(), [&function](directory& dir) { dir.apply(function); } );
}


const directory& directory::get_directory(const std::string& filename) const
{
	if (filename.at(filename.size() - 1) != '/')
	{
		auto end = children.end();
		for (auto it = children.begin(); it != end; ++it)
			if (it->get_name() == filename + '/')
				return *it;
	}
	else
	{
		auto end = children.end();
		for (auto it = children.begin(); it != end; ++it)
			if (it->get_name() == filename)
				return *it;
	}
	return DIRECTORY_DOESNT_EXIST;
}

directory& directory::get_directory(const std::string& filename)
{
	if (filename.at(filename.size() - 1) != '/')
	{
		auto end = children.end();
		for (auto it = children.begin(); it != end; ++it)
			if (it->get_name() == filename + '/')
				return *it;
	}
	else
	{
		auto end = children.end();
		for (auto it = children.begin(); it != end; ++it)
			if (it->get_name() == filename)
				return *it;
	}
	return DIRECTORY_DOESNT_EXIST;
}

const file& directory::get_regular_file(const std::string& filename) const
{
	auto end = files.end();
	for (auto it = files.begin(); it != end; ++it)
		if (it->get_name() == filename)
			return *it;
	return FILE_DOESNT_EXIST;
}

file& directory::get_regular_file(const std::string& filename)
{
	auto end = files.end();
	for (auto it = files.begin(); it != end; ++it)
		if (it->get_name() == filename)
			return *it;
	return FILE_DOESNT_EXIST;
}

std::string directory::get_name() const
{
	return path.filename().string() + "/";
}

std::ostream& directory::diff(const directory& other, std::ostream& out, int depth) const
{
	{
		std::set<std::string> considered;

		auto end = files.end();
		for (auto it = files.begin(); it != end; ++it)
		{
			const file& o = other.get_regular_file(it->get_name());
			if (o == FILE_DOESNT_EXIST)
			{
				out << "+ " << it->path.string() << '\n';
			}
			else if (!it->contents_match(o))
			{
				out << "x " << it->path.string() << '\n';
				considered.insert(it->get_name());
			}
			else
			{
				considered.insert(it->get_name());
			}
		}
		end = other.files.end();
		for (auto it = other.files.begin(); it != end; ++it)
		{
			if (considered.find(it->get_name()) != considered.end())
			{
				continue;
			}
			const file& o = get_regular_file(it->get_name());
			if (o == FILE_DOESNT_EXIST)
			{
				out << "- " << it->path.string() << '\n';
			}
		}
	}

	{
		std::set<std::string> considered;
		std::list<std::pair<const directory&, const directory&>> torecurse;

		auto end = children.end();
		for (auto it = children.begin(); it != end; ++it)
		{
			const directory& o = other.get_directory(it->get_name());
			if (o == FILE_DOESNT_EXIST)
			{
				out << "+ " << it->path.string() << "/\n";
			}
			else
			{
				torecurse.push_back(std::pair<const directory&,const directory&>{*it, o});
				considered.insert(it->get_name());
			}
		}
		end = other.children.end();
		for (auto it = other.children.begin(); it != end; ++it)
		{
			if (considered.find(it->get_name()) != considered.end())
			{
				continue;
			}
			const directory& o = get_directory(it->get_name());
			if (o == FILE_DOESNT_EXIST)
			{
				out << "- " << it->path.string() << "/\n";
			}
		}

		std::for_each(torecurse.begin(), torecurse.end(), [&out, depth](std::pair<const directory&, const directory&> p)
		{
			p.first.diff(p.second, out, depth+1);
		});
	}

	return out;
}





