#pragma once
#include </Users/srijansinha/Projects/strat_simulator/code/include/strategy/base_strategy.hpp>
#include <cstdint>

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
	Simulator(uint32_t time_points, uint32_t num_stocks);

	/**
	Destructor
	*/
	~Simulator() = default;

	/**
	Starts the simulation run once everything is in place
	@param[in] num_threads
	*/
	void run_sim(int num_threads=1);
	
	/**
	Starts the simulation run once everything is in place
	@param[in] num_threads
	*/
	void add_strategy(::strategy::BaseStrategy* strat);

private:
	uint32_t time_points_;
	uint32_t num_stocks_;


}; // class Simulator
} // namespace sim