#include "code/include/strategy/sample_strategy_1.hpp"

namespace strategy {
SampleStrategy1::SampleStrategy1(const boost::property_tree::ptree& config) : BaseStrategy(config) {}

// SampleStrategy1::~SampleStrategy1()

void SampleStrategy1::get_position(uint32_t time_index,
	const std::vector<std::vector<double>>& closing_price,
	std::vector<double>& positions) {
	if (time_index < 1) {
		return;
	}
	for (int i = 0; i < closing_price.at(time_index).size(); ++i) {
		positions[i] = calc_position(closing_price.at(time_index).at(i),
				closing_price.at(time_index - 1).at(i));
	}
}

inline double SampleStrategy1::calc_position(double close_price, double prev_close_price) {
	return (-1 * (close_price - prev_close_price) / prev_close_price) * 10000;
}
} // namespace strategy