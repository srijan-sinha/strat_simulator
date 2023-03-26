#pragma once
#include </Users/srijansinha/Projects/strat_simulator/code/include/strategy/base_strategy.hpp>
#include <cstdint>

namespace sim {
class Simulator {
public:
	Simulator(uint32_t time_points, uint32_t num_stocks);
	~Simulator() = default;
	void run_sim(int num_threads=1);
	void add_strategy(::strategy::BaseStrategy* strat);

private:

	uint32_t time_points_;
	uint32_t num_stocks_;


}; // class Simulator
} // namespace sim