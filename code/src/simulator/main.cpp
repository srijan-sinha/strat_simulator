#include "code/include/simulator/simulator.hpp"
#include <iostream>
int main(int argc, char* argv[]) {
	std::cout << "Yay! Compiling" << std::endl;
	auto* simulator = new sim::Simulator("./configs/sample.json");
	simulator->run_sim();
	delete simulator;
}