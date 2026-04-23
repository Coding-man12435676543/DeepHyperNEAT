#pragma once

/*
This file creates new generations.
Teaching note: reproduction allocates offspring per species and mutates children,
which balances exploitation of fit genomes with exploration of new structures.
*/

#include "deephyperneat/genome.hpp"
#include "deephyperneat/species.hpp"

#include <random>
#include <unordered_map>

namespace dhn {

class Reproduction {
public:
    std::unordered_map<int, Genome> create_new_population(int size, std::mt19937& rng);
    std::unordered_map<int, Genome> reproduce(const std::unordered_map<int, Genome>& pop,
                                              SpeciesSet& species,
                                              int size,
                                              std::mt19937& rng);

private:
    int next_genome_key_{1};
};

}  // namespace dhn
