#include "deephyperneat/species.hpp"

#include <cmath>
#include <limits>

namespace dhn {
SpeciesSet::SpeciesSet(double threshold) : threshold_(threshold) {}

double SpeciesSet::distance(const Genome& a, const Genome& b) const {
    double d = 0.0;
    d += std::abs(static_cast<double>(a.connections().size()) - static_cast<double>(b.connections().size()));
    d += std::abs(static_cast<double>(a.nodes().size()) - static_cast<double>(b.nodes().size()));
    return d;
}

void SpeciesSet::speciate(const std::unordered_map<int, Genome>& population) {
    if (population.empty()) {
        species_.clear();
        return;
    }

    std::unordered_map<int, Species> next;
    for (const auto& [gid, genome] : population) {
        int best_sid = -1;
        double best_dist = std::numeric_limits<double>::max();
        for (const auto& [sid, sp] : next.empty() ? species_ : next) {
            auto it = population.find(sp.representative);
            if (it == population.end()) continue;
            const double dist = distance(genome, it->second);
            if (dist < best_dist) {
                best_dist = dist;
                best_sid = sid;
            }
        }

        if (best_sid == -1 || best_dist > threshold_) {
            const int sid = next_species_key_++;
            next[sid] = Species{sid, gid, {gid}, 0.0, genome.fitness, 0};
        } else {
            next[best_sid].members.push_back(gid);
            if (genome.fitness > next[best_sid].max_fitness) next[best_sid].max_fitness = genome.fitness;
        }
    }

    species_ = std::move(next);
}
}  // namespace dhn
