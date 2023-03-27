#pragma once
#include "code/include/strategy/defs.h"
#include <boost/algorithm/string.hpp>

namespace strategy::utils {
strategy::strat_types get_strat_type_from_string(std::string type);
} // namespace strategy::utils