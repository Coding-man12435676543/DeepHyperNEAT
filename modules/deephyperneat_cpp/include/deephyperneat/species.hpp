#pragma once

/*
This file handles species partitioning.
Teaching note: speciation protects innovation by grouping similar genomes,
so new structures can mature before direct competition with dominant lineages.
*/

#include "deephyperneat/genome.hpp"

#include <unordered_map>
#include <vector>

namespace dhn {

struct Species {
    int key{};
    int representative{};
    std::vector<int> members;
    double adjusted_fitness{0.0};
    double max_fitness{0.0};
    int last_improved{0};
};

class SpeciesSet {
public:
    explicit SpeciesSet(double threshold);
    void speciate(const std::unordered_map<int, Genome>& population);
    std::unordered_map<int, Species>& data() { return species_; }
    const std::unordered_map<int, Species>& data() const { return species_; }

private:
    double distance(const Genome& a, const Genome& b) const;

    double threshold_;
    int next_species_key_{1};
    std::unordered_map<int, Species> species_;
};

}  // namespace dhn
