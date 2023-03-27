#pragma once
#include "code/include/strategy/base_strategy.hpp"

namespace strategy {
class SampleStrategy1 : public BaseStrategy {
public:
	SampleStrategy1(const boost::property_tree::ptree& config);
	~SampleStrategy1() = default;
	void get_position(uint32_t time_index, const double** closing_price, double** positions) override;

}; // class SampleStrategy1
} // namespace strategy