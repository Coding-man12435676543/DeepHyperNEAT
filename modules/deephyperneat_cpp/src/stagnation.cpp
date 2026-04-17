#include "deephyperneat/stagnation.hpp"

namespace dhn {
Stagnation::Stagnation(int max_stagnation) : max_stagnation_(max_stagnation) {}

std::unordered_map<int, bool> Stagnation::update(const SpeciesSet& set, int generation) {
    std::unordered_map<int, bool> result;
    for (const auto& [sid, species] : set.data()) {
        result[sid] = (generation - species.last_improved) >= max_stagnation_;
    }
    return result;
}
}  // namespace dhn
