#include "code/include/simulator/simulator.hpp"
#include "code/include/strategy/sample_strategy_1.hpp"
#include "code/include/strategy/sample_strategy_2.hpp"
#include "code/include/strategy/strategy_utils.h"
#include <boost/property_tree/json_parser.hpp>
#include <iomanip>
#include <cstring>
#include <iostream>

namespace sim {
Simulator::Simulator(const char* filename) {
	boost::property_tree::read_json(std::string(filename), pt_);
	load_config();
	parser_ = new utils::Parser(closing_prices_csv_path_.c_str());
	if (!parser_->get_header(headers_))
		throw std::runtime_error("Unable to read headers!");
	write_headers_to_output();
}

Simulator::~Simulator() {
	for (auto& [_, ofs] : output_fds_)
		ofs.flush();
	delete parser_;
}

void Simulator::run_sim() {
	std::vector<double> curr_position(num_stocks_, 0);
	std::string timestamp;
	int ts_num = 0;

	while(parser_->read_next_line()) {
		parser_->get_timestamp(timestamp);
		if (timestamp < start_time_) continue;
		if (timestamp > end_time_) break;

		timestamps_.push_back(timestamp);
		data_points_.emplace_back();
		parser_->get_data(data_points_.at(data_points_.size() - 1));
		for (auto [strat_name, strat]: strats_) {
			strat->get_position(ts_num, data_points_, curr_position);
			dump_holdings_to_file(strat_name, ts_num, curr_position);
		}
		++ts_num;
	}
}

void Simulator::load_config() {
	closing_prices_csv_path_ = pt_.get<std::string>("closing_prices_file");
	holdings_files_path_ = pt_.get<std::string>("holdings_file");
	num_stocks_ = pt_.get<int>("num_stocks", 0);
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
	output_fds_.insert({strat_name, std::ofstream{std::string(holdings_files_path_ + strat_name + ".csv")}});
	output_fds_[strat_name] << std::setprecision(16);
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

void Simulator::dump_holdings_to_file(std::string strat_name, int timestamp_index, std::vector<double>& curr_position) {
	output_fds_[strat_name] << timestamps_[timestamp_index];
	for (auto val : curr_position) {
		output_fds_[strat_name] << "," << val;
	}
	output_fds_[strat_name] << std::endl;
}

void Simulator::write_headers_to_output() {
	for (auto [strat_name, _] : strats_) {
		output_fds_[strat_name] << boost::algorithm::join(headers_, ",") << std::endl;
	}
}

} // namespace sim
