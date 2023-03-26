#include "code/include/utils/parser.hpp"
#include <boost/algorithm/string.hpp>

namespace utils {
Parser::Parser(const char* filename) : ifs_{filename} {
	if (!ifs_) {
		throw std::runtime_error("Unable to open file");
	}
	std::getline(ifs_, header_);
	++num_lines_;
}

Parser::~Parser() {
	if(ifs_.is_open()) ifs_.close();
}

bool Parser::get_next_time_point_data(std::vector<double>& data_vec, std::string& timestamp) {
	if (!read_next_line()) {
		return false;
	}

	std::vector<std::string> vec;
	boost::split(vec, line_, boost::is_any_of(","));
	bool first_item = true;
	for (auto item: vec) {
		if (first_item) {
			timestamp = item;
			first_item = false;
			continue;
		}
		if (item.length())
			data_vec.push_back(std::stod(item));
		else
			data_vec.push_back(-1);
	}
	return true;
}

bool Parser::get_header(std::vector<std::string>& header_vec) {
	if (!header_.length()) {
		return false;
	}
	boost::split(header_vec, header_, boost::is_any_of(","));
	return true;
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
} // namespace utils