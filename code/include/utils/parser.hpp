#pragma once
#include <fstream>
#include <vector>
#include <cstring>

namespace utils {
class Parser {
public:
	Parser(const char* filename);
	~Parser();
	bool read_next_line();
	bool get_header(std::vector<std::string>& header_vec);
	std::string get_timestamp();
	void get_data(std::vector<double>& data_vec);

private:
	static constexpr int timestamp_len_ = 19;
	std::ifstream ifs_;
	std::string line_;
	int num_lines_{0};
	std::string header_;
}; // class Parser
} // namespace utils