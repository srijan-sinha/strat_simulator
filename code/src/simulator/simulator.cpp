#include "code/include/simulator/simulator.hpp"
#include "code/include/strategy/sample_strategy_1.hpp"
#include "code/include/strategy/sample_strategy_2.hpp"
#include "code/include/strategy/strategy_utils.h"
#include <iomanip>
#include <limits>
#include <cstring>
#include <iostream>

namespace sim {
Simulator::Simulator(const boost::property_tree::ptree& config)
		: config_(config),
		closing_prices_file_(config.get<std::string>("closing_prices_file")),
		holdings_output_folder_(config.get<std::string>("holdings_output_folder")),
		start_time_(config.get<std::string>("start_time", "2021-04-01 00:00:00")),
		end_time_(config.get<std::string>("end_time", "2022-05-01 00:00:00")),
		num_instruments_(config.get<int>("num_instruments", 0)),
		num_extra_threads_(config.get<int>("num_extra_threads", 1)),
		parser_(closing_prices_file_.c_str()),
		threads_(num_extra_threads_),
		data_avail_for_thread_(num_extra_threads_),
		data_points_(num_instruments_, std::numeric_limits<double>::min()) {
	load_strategies();
	for (auto& avail: data_avail_for_thread_) {
		avail.store(0, std::memory_order_release);
	}
}

Simulator::~Simulator() {
	for (auto& [_, ofs] : output_fds_) {
		ofs.flush();
		ofs.close();
	}
	for (auto& th: threads_) {
		th.join();
	}
	parser_.close();
}

void Simulator::run_sim() {
	copy_header_to_output();

	if (num_extra_threads_ == 0) {
		while(parser_.read_next_line()) {
			++ts_num_;
			timestamps_.push_back(parser_.get_timestamp());
			if (timestamps_.at(ts_num_ - 1) < start_time_) continue;
			if (timestamps_.at(ts_num_ - 1) > end_time_) break;

			parser_.get_data(data_points_);
			for (auto [strat_name, strat]: strats_) {
				dump_holdings_to_file(strat_name, ts_num_);
				strat->get_position(ts_num_, data_points_, curr_position_[strat_name]);
			}
		}
	} else {
		for (int th = 0; th < num_extra_threads_; ++th) {
			std::thread thr([=, this]() {
				while (true) {
					while(data_avail_for_thread_[th].load(std::memory_order_acquire) != 1
							&& !data_finished_) {}
					if (data_finished_) break;
					for (int i = 0; i < strats_.size(); ++i) {
						if (i % num_extra_threads_ == th) {
							auto& strat_name = strats_[i].first;
							auto* strat = strats_[i].second;
							dump_holdings_to_file(strat_name, ts_num_);
							strat->get_position(ts_num_, data_points_, curr_position_[strat_name]);
						}
					}
					data_avail_for_thread_[th].store(0, std::memory_order_release);
				}
			});
			std::swap(thr, threads_.at(th));
		}

		while(parser_.read_next_line()) {
			while(!get_if_all_data_avail_false()) {}
			++ts_num_;
			timestamps_.push_back(parser_.get_timestamp());
			if (timestamps_.at(ts_num_ - 1) < start_time_) continue;
			if (timestamps_.at(ts_num_ - 1) > end_time_) break;

			parser_.get_data(data_points_);
			set_all_data_avail_true();
		}
		data_finished_ = true;
	}

	parser_.close();
}

void Simulator::load_strategies() {
	for (const auto [strat_name, strat_pt] : config_.get_child("algos")) {
		auto strat_type = strategy::utils::get_strat_type_from_string(strat_pt.get<std::string>("strat_type"));
		std::cout << "Adding strategy: " << strat_name << std::endl;
		add_strategy(strat_name, strat_type, strat_pt);
	}
}

void Simulator::add_strategy(std::string strat_name, strategy::strat_types type,
		const boost::property_tree::ptree& config) {
	output_fds_.insert({strat_name, std::ofstream{std::string(holdings_output_folder_ + strat_name + ".csv")}});
	output_fds_[strat_name] << std::setprecision(16);
	curr_position_.emplace(strat_name, std::vector<double>(num_instruments_, std::numeric_limits<double>::min()));
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

void Simulator::copy_header_to_output() {
	if (!parser_.get_header(headers_))
		throw std::runtime_error("Unable to read headers!");
	for (auto [strat_name, _] : strats_) {
		output_fds_[strat_name] << boost::algorithm::join(headers_, ",") << std::endl;
	}
}

void Simulator::dump_holdings_to_file(std::string strat_name, int timestamp_index) {
	output_fds_[strat_name] << timestamps_[timestamp_index-1];
	for (auto val : curr_position_[strat_name]) {
		if (val == std::numeric_limits<double>::min())
			output_fds_[strat_name] << ",";
		else
			output_fds_[strat_name] << "," << val;
	}
	output_fds_[strat_name] << std::endl;
}

bool Simulator::get_if_all_data_avail_false() {
	for (auto& avail: data_avail_for_thread_) {
		if (avail.load(std::memory_order_acquire) == 1) return false;
	}
	return true;
}

void Simulator::set_all_data_avail_true() {
	for (auto& avail: data_avail_for_thread_) avail.store(1, std::memory_order_release);
}

} // namespace sim
