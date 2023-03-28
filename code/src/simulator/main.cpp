#include "code/include/simulator/simulator.hpp"
#include "code/include/utils/parser.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <cstring>

int main(int argc, char* argv[]) {
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(std::string(argv[1]), pt);
	auto* simulator = new sim::Simulator(pt);
	simulator->run_sim();
	delete simulator;
}