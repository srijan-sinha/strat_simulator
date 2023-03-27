#include "code/include/simulator/simulator.hpp"
#include "code/include/strategy/sample_strategy_1.hpp"
#include "code/include/strategy/sample_strategy_2.hpp"
#include "code/include/strategy/strategy_utils.h"
#include <boost/property_tree/json_parser.hpp>
#include <cstring>

namespace sim {
Simulator::Simulator(const char* filename) {
	boost::property_tree::read_json(std::string(filename), pt_);
	load_config();
	parser_ = new utils::Parser(closing_prices_csv_path_.c_str());
}

Simulator::~Simulator() {
	delete parser_;
}

void Simulator::run_sim() {}

void Simulator::load_config() {
	closing_prices_csv_path_ = pt_.get<std::string>("closing_prices_file");
	holdings_csv_path_ = pt_.get<std::string>("holdings_file");
	start_time_ = pt_.get<std::string>("start_time", "2021-04-01 00:00:00");
	end_time_ = pt_.get<std::string>("end_time", "2022-04-30 23:00:00");
	num_threads_ = pt_.get<int>("num_threads", 1);
	for (const auto [strat_name, strat_pt] : pt_.get_child("algos")) {
		auto strat_type = strategy::utils::get_strat_type_from_string(strat_pt.get<std::string>("strat_type"));
		std::cout << "Adding strategy: " << strat_name << std::endl;
		add_strategy(strat_name, strat_type, strat_pt);
	}
}

void Simulator::add_strategy(std::string strat_name, strategy::strat_types type,
		const boost::property_tree::ptree& config) {
	switch (type) {
		case strategy::SAMPLE1: {
			strats_.push_back({strat_name, new strategy::SampleStrategy1(config)});
			break;
		}
		case strategy::SAMPLE2: {
			strats_.push_back({strat_name, new strategy::SampleStrategy2(config)});
			break;
		}
		default: {
			std::cout << "Bad strategy type. Ignoring" << std::endl;
		}
	}
}
} // namespace sim
