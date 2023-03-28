#include "code/include/utils/parser.hpp"
#include <boost/algorithm/string.hpp>
#include <limits>
#include <iostream>

namespace utils {
Parser::Parser(const char* filename) : ifs_{filename} {
	if (!ifs_) {
		throw std::runtime_error("Unable to open file");
	}
	std::getline(ifs_, header_);
	++num_lines_;
}

Parser::~Parser() {
	close();
}

bool Parser::read_next_line() {
	if (!ifs_) {
		std::cout << "File reading finished." << std::endl;
		std::cout << "Read " << num_lines_ << " lines." << std::endl;
		return false;
	}
	std::getline(ifs_, line_);
	++num_lines_;
	return true;
}

bool Parser::get_header(std::vector<std::string>& header_vec) {
	if (!header_.length()) {
		return false;
	}
	boost::split(header_vec, header_, boost::is_any_of(","));
	return true;
}

std::string Parser::get_timestamp() {
	return line_.substr(0,19);
}

void Parser::get_data(std::vector<double>& data_vec) {
	std::vector<std::string> vec;
	boost::split(vec, line_, boost::is_any_of(","));
	for (int i = 0; i < vec.size(); ++i) {
		if (i == 0)
			continue;
		if (vec[i].length())
			data_vec[i-1] = (std::stod(vec[i]));
		else
			data_vec[i-1] = std::numeric_limits<double>::min();
	}
}

void Parser::close() {
	if(ifs_.is_open()) ifs_.close();
}
} // namespace utils