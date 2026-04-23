#include "deephyperneat/reproduction.hpp"

#include <algorithm>

namespace dhn {
std::unordered_map<int, Genome> Reproduction::create_new_population(int size, std::mt19937&) {
    std::unordered_map<int, Genome> pop;
    for (int i = 0; i < size; ++i) {
        const int gid = next_genome_key_++;
        pop.emplace(gid, Genome(gid));
    }
    return pop;
}

std::unordered_map<int, Genome> Reproduction::reproduce(const std::unordered_map<int, Genome>& pop,
                                                        SpeciesSet& species,
                                                        int size,
                                                        std::mt19937& rng) {
    species.speciate(pop);

    std::vector<const Genome*> ranked;
    ranked.reserve(pop.size());
    for (const auto& [_, genome] : pop) ranked.push_back(&genome);
    std::sort(ranked.begin(), ranked.end(), [](const Genome* a, const Genome* b) { return a->fitness > b->fitness; });

    std::unordered_map<int, Genome> next;
    if (!ranked.empty()) {
        // Elitism: carry one champion directly.
        next.emplace(ranked.front()->key(), *ranked.front());
    }

    std::uniform_int_distribution<int> pick(0, static_cast<int>(std::max<size_t>(1, ranked.size())) - 1);
    while (static_cast<int>(next.size()) < size && !ranked.empty()) {
        const Genome* parent = ranked[pick(rng)];
        const int child_id = next_genome_key_++;
        Genome child(child_id);
        child.copy_from(*parent);
        child.mutate(rng);
        next.emplace(child_id, std::move(child));
    }

    return next;
}
}  // namespace dhn
