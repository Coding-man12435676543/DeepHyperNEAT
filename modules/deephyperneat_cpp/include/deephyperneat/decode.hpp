#pragma once

/*
This file decodes CPPNs into substrate networks.
Teaching note: decoding asks the CPPN for each potential connection weight,
turning an indirect encoding into a concrete substrate graph.
*/

#include "deephyperneat/genome.hpp"
#include "deephyperneat/phenomes.hpp"

#include <vector>

namespace dhn {
FeedForwardCPPN create_cppn(const Genome& genome);
FeedForwardSubstrate decode(const FeedForwardCPPN& cppn,
                            const std::vector<int>& input_dimensions,
                            int output_dimensions,
                            const std::vector<int>& sheet_dimensions);
}  // namespace dhn
