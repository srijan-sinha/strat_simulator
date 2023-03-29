#pragma once
#include "code/include/strategy/defs.h"
#include <boost/algorithm/string.hpp>

namespace strategy::utils {
/**
Converts string to strategy::strat_types enum
@param[in] type string representation
@return strat_type enum of type strategy::strat_type
*/
strategy::strat_types get_strat_type_from_string(std::string type);
} // namespace strategy::utils