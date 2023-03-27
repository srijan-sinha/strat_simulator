#pragma once
#include "code/include/strategy/base_strategy.hpp"

namespace strategy {
class SampleStrategy2 : public BaseStrategy {
public:
	SampleStrategy2(const boost::property_tree::ptree& config);
	~SampleStrategy2() = default;
	void get_position(uint32_t time_index, const double** closing_price, double** positions) override;
	
}; // class SampleStrategy2
} // namespace strategy