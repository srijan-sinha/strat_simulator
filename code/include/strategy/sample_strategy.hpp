#pragma once
#include "code/include/strategy/base_strategy.hpp"

namespace strategy {
class SampleStrategy(BaseStrategy) {
public:
    SampleStrategy();
    ~SampleStrategy() = default;
    void get_position(uint32_t time_index, const double** closing_price, double** positions) override;
}; // class SampleStrategy
} // namespace strategy