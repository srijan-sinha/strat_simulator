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
	Simulator(const boost::property_tree::ptree& pt);

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
	void load_strategies();
	/**
	Starts the simulation run once everything is in place
	@param[in] strat
	*/
	void add_strategy(std::string strat_name, strategy::strat_types type,
		const boost::property_tree::ptree& config);

	void copy_header_to_output();

	void dump_holdings_to_file(std::string strat_name, int timestamp_index, std::vector<double>& curr_position);

	const boost::property_tree::ptree pt_;
	const std::string closing_prices_csv_path_;
	const std::string holdings_files_path_;
	const std::string start_time_;
	const std::string end_time_;
	const uint32_t num_stocks_;
	const int num_threads_;
	utils::Parser parser_;

	std::vector<std::pair<std::string, strategy::BaseStrategy*>> strats_;
	std::unordered_map<std::string, std::ofstream> output_fds_;
	std::vector<std::string> headers_;
	std::vector<std::string> timestamps_;
	std::vector<double> data_points_;
	std::unordered_map<std::string, std::vector<double>> curr_position_;

}; // class Simulator
} // namespace sim