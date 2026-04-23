#include "deephyperneat/genome.hpp"

#include "deephyperneat/phenomes.hpp"

#include <algorithm>

namespace dhn {
namespace {
double uniform(std::mt19937& rng, double lo, double hi) {
    std::uniform_real_distribution<double> dist(lo, hi);
    return dist(rng);
}
int randint(std::mt19937& rng, int lo, int hi) {
    std::uniform_int_distribution<int> dist(lo, hi);
    return dist(rng);
}
}  // namespace

Genome::Genome(int key) : key_(key) {
    std::mt19937 rng(static_cast<std::mt19937::result_type>(key * 1337 + 11));
    configure_minimal(rng);
}

long long Genome::conn_key(int a, int b) { return (static_cast<long long>(a) << 32) ^ static_cast<unsigned int>(b); }

void Genome::configure_minimal(std::mt19937& rng) {
    input_keys_ = {-1, -2, -3, -4};
    output_keys_ = {0, 1};
    next_node_key_ = 2;

    nodes_[0] = NodeGene{0, true, 0.0, "linear"};
    nodes_[1] = NodeGene{1, true, 0.0, "linear"};

    for (int in : input_keys_) {
        for (int out : output_keys_) {
            ConnectionGene c{{in, out}, uniform(rng, -1.0, 1.0), true};
            connections_[conn_key(in, out)] = c;
        }
    }
}

void Genome::copy_from(const Genome& other) {
    next_node_key_ = other.next_node_key_;
    input_keys_ = other.input_keys_;
    output_keys_ = other.output_keys_;
    nodes_ = other.nodes_;
    connections_ = other.connections_;
    fitness = other.fitness;
}

int Genome::complexity() const { return static_cast<int>(nodes_.size() + connections_.size()); }

void Genome::mutate(std::mt19937& rng) {
    const double r = uniform(rng, 0.0, 1.0);
    if (r < 0.2) mutate_add_node(rng);
    else if (r < 0.7) mutate_add_connection(rng);
    mutate_weight(rng);
}

void Genome::mutate_add_node(std::mt19937& rng) {
    if (connections_.empty()) return;
    auto it = connections_.begin();
    std::advance(it, randint(rng, 0, static_cast<int>(connections_.size()) - 1));
    auto split = it->second;
    connections_.erase(it);

    const int new_node = next_node_key_++;
    nodes_[new_node] = NodeGene{new_node, false, uniform(rng, -1.0, 1.0), "relu"};

    connections_[conn_key(split.key.first, new_node)] = ConnectionGene{{split.key.first, new_node}, 1.0, true};
    connections_[conn_key(new_node, split.key.second)] = ConnectionGene{{new_node, split.key.second}, split.weight, true};
}

void Genome::mutate_add_connection(std::mt19937& rng) {
    if (nodes_.empty()) return;
    std::vector<int> targets;
    for (const auto& kv : nodes_) targets.push_back(kv.first);
    std::vector<int> sources = targets;
    sources.insert(sources.end(), input_keys_.begin(), input_keys_.end());

    const int source = sources[randint(rng, 0, static_cast<int>(sources.size()) - 1)];
    const int target = targets[randint(rng, 0, static_cast<int>(targets.size()) - 1)];
    const auto ck = conn_key(source, target);
    if (connections_.count(ck)) return;

    std::vector<std::pair<int, int>> existing;
    existing.reserve(connections_.size());
    for (const auto& kv : connections_) existing.push_back(kv.second.key);
    if (creates_cycle(existing, {source, target})) return;

    connections_[ck] = ConnectionGene{{source, target}, uniform(rng, -1.0, 1.0), true};
}

void Genome::mutate_weight(std::mt19937& rng) {
    for (auto& kv : connections_) {
        if (uniform(rng, 0.0, 1.0) < 0.9) kv.second.weight += uniform(rng, -0.1, 0.1);
    }
}
}  // namespace dhn
