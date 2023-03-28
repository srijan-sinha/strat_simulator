#pragma once
#include "code/include/strategy/base_strategy.hpp"

namespace strategy {
class SampleStrategy1 : public BaseStrategy {
public:
	SampleStrategy1(const boost::property_tree::ptree& config);
	~SampleStrategy1() = default;
	void get_position(uint32_t time_index,
			const std::vector<std::vector<double>>& closing_price,
			std::vector<double>& positions) override;

private:
	inline double calc_position(double close_price, double prev_close_price);
}; // class SampleStrategy1
} // namespace strategy