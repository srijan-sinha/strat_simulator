#pragma once
#include "code/include/strategy/defs.h"
#include <boost/property_tree/ptree.hpp>
#include <cstdint>

namespace strategy {
/**
\class BaseStrategy
\brief abstract class from which all strategies inherit

This class defines some basic methods that are essential to all running strategies.
Inheriting strategies need to implement the virtual methods on their own.

More information can be found here:
https://docs.google.com/document/d/1qQxmnjdF83CJ6g21Zv_VjCWYLnzhT5ONP10oC3Wrnf0/edit?usp=sharing
*/
class BaseStrategy {
public:
	BaseStrategy(const boost::property_tree::ptree& config) : pt_(config) {}
	~BaseStrategy() = default;
	virtual void get_position(uint32_t time_index, const double** closing_price, double** positions) = 0;
private:
	const boost::property_tree::ptree pt_;
}; // class BaseStrategy
} // namespace strategy