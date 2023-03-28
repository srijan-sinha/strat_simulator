#include "code/include/strategy/sample_strategy_2.hpp"

namespace strategy {
SampleStrategy2::SampleStrategy2(const boost::property_tree::ptree& config) : BaseStrategy(config) {}

// SampleStrategy2::~SampleStrategy2()

void SampleStrategy2::get_position(uint32_t time_index,
        const std::vector<double>& closing_price,
        std::vector<double>& positions) {}
} // namespace strategy