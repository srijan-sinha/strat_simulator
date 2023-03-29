#pragma once
#include <fstream>
#include <vector>
#include <cstring>

namespace utils {
/**
\class Parser
\brief class that reads the input file line by line and provides well formed data

It reads the input file line by line and stores this line data. When the getter
functions are called it transforms this data into appropriate data structure and
provides it to the caller.

More information can be found here:
https://docs.google.com/document/d/1qQxmnjdF83CJ6g21Zv_VjCWYLnzhT5ONP10oC3Wrnf0/edit?usp=sharing
*/
class Parser {
public:
	/**
	Constructor
	@param[in] filename name of the file to read from
	*/
	Parser(const char* filename);

	/**
	Destructor
	*/
	~Parser();

	/**
	Reads the next line from the file and updates its internal data members
	@return true: if next line was read successfully
	@return false: if not able to read next line
	*/
	bool read_next_line();

	/**
	Provides the caller with the headers split by ',' as delimiter
	@param[inout] header_vec this empty vector is populated with the column headers
	@return true: if headers are successfully populated
	@return false: if not able to populate headers
	*/
	bool get_header(std::vector<std::string>& header_vec);

	/**
	Provides the timestamp of the last line that was read
	@return timestamp as a std::string
	*/
	std::string get_timestamp();

	/**
	Provides the data from the last line that was read
	@param [inout] data_vec rewrites the values of this vector with current data,
							should be appropriately resized apriori
	*/
	void get_data(std::vector<double>& data_vec);

	/**
	Stops reading and closes the input file, subsequent read calls (if any) will fail
	*/
	void close();

private:
	static constexpr int timestamp_len_ = 19; // length of the timestamp field
	std::ifstream ifs_; // input file stream
	std::string line_; // last line that was read, empty initially
	int num_lines_{0}; // number of lines read
	std::string header_; // header line that was read, populated upon constructor call
}; // class Parser
} // namespace utils