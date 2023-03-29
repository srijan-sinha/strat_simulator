#pragma once
#include "code/include/strategy/base_strategy.hpp"

namespace strategy {
class SampleStrategy1 : public BaseStrategy {
public:
	SampleStrategy1(const boost::property_tree::ptree& config);
	~SampleStrategy1() = default;
	void get_position(uint32_t time_index,
			const std::vector<double>& closing_price,
			std::vector<double>& positions) override;

private:
	/**
	Calculates the position using an algorithm given the current and previous closing prices
	@param[in] close_price current closing price for the instruments
	@param[in] prev_close_price previous closing price for the instruments
	@return position as calculated by the algorithm
	*/
	inline double calc_position(double close_price, double prev_close_price);

private:
	std::vector<double> prev_close; // vector of previous closing prices for all instruments
}; // class SampleStrategy1
} // namespace strategy