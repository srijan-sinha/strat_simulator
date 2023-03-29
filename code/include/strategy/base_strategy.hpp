#pragma once
#include "code/include/strategy/defs.h"
#include <boost/property_tree/ptree.hpp>
#include <cstdint>
#include <vector>

namespace strategy {
/**
\class BaseStrategy
\brief abstract class from which all strategies inherit

This class defines some basic methods that are essential to all running strategies.
Inheriting strategies need to implement the virtual method on their own.

More information can be found here:
https://docs.google.com/document/d/1qQxmnjdF83CJ6g21Zv_VjCWYLnzhT5ONP10oC3Wrnf0/edit?usp=sharing
*/
class BaseStrategy {
public:
	/**
	Constructor
	@param[in] config config for the strategy
	*/
	BaseStrategy(const boost::property_tree::ptree& config) : pt_(config) {}

	/**
	Destructor
	*/
	~BaseStrategy() = default;

	/**
	Provides the position given the current closing price and the timestamp index
	@param[in] time_index index of the timestamp for which closing price data is provided
	@param[in] closing_price vector of closing prices
	@param[inout] positions position vector which will be updated with new values
							should be appropriately resized apriori
	*/
	virtual void get_position(uint32_t time_index,
			const std::vector<double>& closing_price,
			std::vector<double>& positions) = 0;
private:
	const boost::property_tree::ptree pt_;
}; // class BaseStrategy
} // namespace strategy