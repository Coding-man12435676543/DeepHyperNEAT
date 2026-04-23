#include "deephyperneat/population.hpp"

#include "deephyperneat/reporters.hpp"

namespace dhn {
Population::Population(int size, int seed)
    : size_(size), rng_(seed), species_(3.5), best_genome_(0) {
    genomes_ = reproduction_.create_new_population(size_, rng_);
}

Genome Population::run(const TaskFunction& task, double goal, int generations) {
    for (int g = 0; g < generations; ++g) {
        task(genomes_);

        double total = 0.0;
        Genome* best = nullptr;
        for (auto& [_, genome] : genomes_) {
            total += genome.fitness;
            if (!best || genome.fitness > best->fitness) best = &genome;
        }

        if (best && (!has_best_ || best->fitness > best_genome_.fitness)) {
            best_genome_ = *best;
            has_best_ = true;
        }

        report_generation(g, has_best_ ? best_genome_.fitness : 0.0, total / static_cast<double>(genomes_.size()));

        if (has_best_ && best_genome_.fitness >= goal) break;
        genomes_ = reproduction_.reproduce(genomes_, species_, size_, rng_);
    }

    return best_genome_;
}
}  // namespace dhn
