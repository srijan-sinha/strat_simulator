#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

namespace utils {
class Parser {
public:
	Parser(const char* filename);
	~Parser();
	bool get_next_time_point_data(std::vector<double>& data_vec, std::string& timestamp);
	bool get_header(std::vector<std::string>& header_vec);

private:
	bool read_next_line();

private:
	static constexpr int timestamp_len_ = 19;
	std::ifstream ifs_;
	std::string line_;
	int num_lines_{0};
	std::string header_;
}; // class Parser
} // namespace utils