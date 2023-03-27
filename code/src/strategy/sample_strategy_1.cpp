#include "code/include/strategy/sample_strategy_1.hpp"

namespace strategy {
SampleStrategy1::SampleStrategy1(const boost::property_tree::ptree& config) : BaseStrategy(config) {}

// SampleStrategy1::~SampleStrategy1()

void SampleStrategy1::get_position(uint32_t time_index, const double** closing_price, double** positions) {
    
}
} // namespace strategy