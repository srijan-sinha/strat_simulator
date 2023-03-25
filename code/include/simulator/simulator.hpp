#include <cstdint>

class Simulator {
public:
	void Simulator(uint32_t time_points, uint32_t num_stocks);

private:
	uint32_t time_points_;
	uint32_t num_stocks_;


}; // class Simulator