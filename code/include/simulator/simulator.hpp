#pragma once
#include "code/include/strategy/base_strategy.hpp"
#include "code/include/strategy/defs.h"
#include "code/include/utils/parser.hpp"
#include <boost/property_tree/ptree.hpp>
#include <atomic>
#include <thread>
#include <mutex>
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
	@param[in] config config for the simulator
	*/
	Simulator(const boost::property_tree::ptree& config);

	/**
	Destructor
	*/
	~Simulator();

	/**
	Starts the simulation run once everything is in place
	*/
	void run_sim();
	

private:
	/**
	Initializes the various kinds of strategies based on the config
	*/
	void load_strategies();

	/**
	Initializes a strategy and adds it to the vector of strategies
	@param[in] strat_name name to be used for the strategy
	@param[in] type the kind of strategy to be initialized
	@param[in] config config of the strategy
	*/
	void add_strategy(std::string strat_name, strategy::strat_types type,
		const boost::property_tree::ptree& config);

	/**
	Gets the header from the parser and copies it to all the output files that are opened
	*/
	void copy_header_to_output();

	/**
	Dumps the current position vector to file for a particular strategy
	@param[in] strat_name name of the strategy for which data is to be dumped
	@param[in] timestamp_index the index of the timestamp that is to be written to file
	*/
	void dump_holdings_to_file(std::string strat_name, int timestamp_index);

	/**
	Fetches if data available flag for all threads is set to false
	@return true: if all flags are false
	@return false: if any flag is set to true, i.e thread is still processing the data
	*/
	bool get_if_all_data_avail_false();

	/**
	Sets all data available flags to true, signalling the threads to start consuming the data
	*/
	void set_all_data_avail_true();

	const boost::property_tree::ptree config_;
	const std::string closing_prices_file_;
	const std::string holdings_output_folder_;
	const std::string start_time_;
	const std::string end_time_;
	const uint32_t num_instruments_;
	const int num_extra_threads_;
	utils::Parser parser_;
	std::vector<std::thread> threads_; // vector of all threads that are running other than main
	std::vector<std::atomic<int>> data_avail_for_thread_; // vector of data available flags for all threads

	std::vector<std::pair<std::string, strategy::BaseStrategy*>> strats_; // vector of all <strat_name, strat> mapping
	std::unordered_map<std::string, std::ofstream> output_fds_; // map of <strat_name, output_file_stream>
	std::vector<std::string> headers_; // vector of column headers from input file
	std::vector<std::string> timestamps_; // vector of timestamps
	std::vector<double> data_points_; // vector of closing_prices for the current timestamp in simulation
	// map of <strat_name, curr_position> where curr_position is for current timestamp in simulation
	std::unordered_map<std::string, std::vector<double>> curr_position_;
	int ts_num_{0}; // count of the number of timestamps/lines read till now from input
	volatile bool data_finished_{false}; // used to signal to threads that input is finished

}; // class Simulator
} // namespace sim