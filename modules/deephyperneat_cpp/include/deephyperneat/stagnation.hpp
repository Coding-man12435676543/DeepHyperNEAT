#pragma once

/*
This file marks stale species.
Teaching note: stagnation control removes species that stop improving,
freeing evolutionary resources for promising niches.
*/

#include "deephyperneat/species.hpp"

#include <unordered_map>

namespace dhn {

class Stagnation {
public:
    explicit Stagnation(int max_stagnation = 15);
    std::unordered_map<int, bool> update(const SpeciesSet& set, int generation);

private:
    int max_stagnation_;
};

}  // namespace dhn
