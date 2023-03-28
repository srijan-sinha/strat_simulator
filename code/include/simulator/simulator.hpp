#pragma once
#include "code/include/strategy/base_strategy.hpp"
#include "code/include/strategy/defs.h"
#include "code/include/utils/parser.hpp"
#include <boost/property_tree/ptree.hpp>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <utility>

namespace sim {
/**
\class Simulator
\brief class that allows us to simulate a trading algo given the time series market data

It reads the input time series market data and then feeds it to one or multiple strategies
(in parallel) and keeps track of their individual holdings. At the end of the simulation,
it generates output files containing this holdings information.

More information can be found here:
https://docs.google.com/document/d/1qQxmnjdF83CJ6g21Zv_VjCWYLnzhT5ONP10oC3Wrnf0/edit?usp=sharing
*/
class Simulator {
public:
	/**
	Constructor
	@param[in] time_points
	@param[in] num_stocks
	*/
	Simulator(const char* config_file);

	/**
	Destructor
	*/
	~Simulator();

	/**
	Starts the simulation run once everything is in place
	@param[in] num_threads
	*/
	void run_sim();
	

private:
	void load_config();
	/**
	Starts the simulation run once everything is in place
	@param[in] strat
	*/
	void add_strategy(std::string strat_name, strategy::strat_types type,
		const boost::property_tree::ptree& config);

	void dump_holdings_to_file(std::string strat_name, int timestamp_index, std::vector<double>& curr_position);

	void write_headers_to_output();

	utils::Parser* parser_;
	boost::property_tree::ptree pt_;
	std::string closing_prices_csv_path_;
	std::string holdings_files_path_;
	std::unordered_map<std::string, std::ofstream> output_fds_;
	std::string start_time_;
	std::string end_time_;
	int num_threads_;
	uint32_t time_points_;
	uint32_t num_stocks_;
	std::vector<std::pair<std::string, strategy::BaseStrategy*>> strats_;
	std::vector<std::vector<double>> data_points_;
	std::vector<std::string> headers_;
	std::vector<std::string> timestamps_;

}; // class Simulator
} // namespace sim