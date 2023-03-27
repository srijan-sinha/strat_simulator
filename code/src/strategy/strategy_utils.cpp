#include "code/include/strategy/strategy_utils.h"

namespace strategy::utils {
strategy::strat_types get_strat_type_from_string(std::string type) {
	boost::algorithm::to_upper(type);
	if (type == "SAMPLE1") {
		return strat_types::SAMPLE1;
	}
	return strat_types::SAMPLE2;
}
} // namespace strategy::utils