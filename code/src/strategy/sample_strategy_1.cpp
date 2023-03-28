#include "code/include/strategy/sample_strategy_1.hpp"
#include <limits>

namespace strategy {
SampleStrategy1::SampleStrategy1(const boost::property_tree::ptree& config) : BaseStrategy(config) {}

// SampleStrategy1::~SampleStrategy1()

void SampleStrategy1::get_position(uint32_t time_index,
	const std::vector<double>& closing_price,
	std::vector<double>& positions) {
	if (!prev_close.size()) {
		prev_close.insert(prev_close.begin(), closing_price.begin(), closing_price.end());
		for (int i = 0; i < positions.size(); ++i)
			positions[i] = std::numeric_limits<double>::min();
		return;
	}
	for (int i = 0; i < positions.size(); ++i) {
		positions[i] = calc_position(closing_price.at(i),
				prev_close.at(i));
	}
	std::copy(closing_price.begin(), closing_price.end(), prev_close.begin());
}

inline double SampleStrategy1::calc_position(double close_price, double prev_close_price) {
	if (close_price == std::numeric_limits<double>::min()
			|| prev_close_price == std::numeric_limits<double>::min())
		return std::numeric_limits<double>::min();
	return (-1 * (close_price - prev_close_price) / prev_close_price) * 10000;
}
} // namespace strategy