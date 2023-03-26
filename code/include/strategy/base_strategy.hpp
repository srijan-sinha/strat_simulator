#pragma once
#include <cstdint>

namespace strategy {
enum strat_types : unsigned char {
    SAMPLE = 0,
    NUM_STRATEGIES
}; // enum strat_types

class BaseStrategy {
public:
    BaseStrategy();
    ~BaseStrategy() = default;
    virtual void get_position(uint32_t time_index, const double** closing_price, double** positions) = 0;
}; // class BaseStrategy
} // namespace strategy