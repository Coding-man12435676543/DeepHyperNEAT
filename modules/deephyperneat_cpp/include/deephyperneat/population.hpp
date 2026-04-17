#pragma once

/*
This file orchestrates end-to-end evolution.
Teaching note: population owns the evolutionary loop, calling task evaluation,
speciation, reproduction, and reporting each generation.
*/

#include "deephyperneat/genome.hpp"
#include "deephyperneat/reproduction.hpp"
#include "deephyperneat/species.hpp"

#include <functional>
#include <random>
#include <unordered_map>

namespace dhn {

using TaskFunction = std::function<void(std::unordered_map<int, Genome>&)>;

class Population {
public:
    Population(int size, int seed = 42);
    Genome run(const TaskFunction& task, double goal, int generations);
    const Genome& best_genome() const { return best_genome_; }

private:
    int size_;
    std::mt19937 rng_;
    Reproduction reproduction_;
    SpeciesSet species_;
    std::unordered_map<int, Genome> genomes_;
    Genome best_genome_;
    bool has_best_{false};
};

}  // namespace dhn
