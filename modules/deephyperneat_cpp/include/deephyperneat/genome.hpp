#pragma once

/*
This file defines genome data structures and mutation behavior.
Teaching note: each genome is a CPPN blueprint, and mutations alter topology/weights,
which drives open-ended architecture search in DeepHyperNEAT.
*/

#include "deephyperneat/activations.hpp"

#include <random>
#include <unordered_map>
#include <utility>
#include <vector>

namespace dhn {

struct NodeGene {
    int key{};
    bool output{false};
    double bias{0.0};
    std::string activation_name{"linear"};
};

struct ConnectionGene {
    std::pair<int, int> key;
    double weight{0.0};
    bool enabled{true};
};

class Genome {
public:
    explicit Genome(int key);

    int key() const { return key_; }
    double fitness{0.0};

    const std::vector<int>& input_keys() const { return input_keys_; }
    const std::vector<int>& output_keys() const { return output_keys_; }
    const std::unordered_map<int, NodeGene>& nodes() const { return nodes_; }
    const std::unordered_map<long long, ConnectionGene>& connections() const { return connections_; }

    std::unordered_map<int, NodeGene>& mutable_nodes() { return nodes_; }
    std::unordered_map<long long, ConnectionGene>& mutable_connections() { return connections_; }

    int complexity() const;
    void mutate(std::mt19937& rng);
    void copy_from(const Genome& other);

private:
    static long long conn_key(int a, int b);
    void configure_minimal(std::mt19937& rng);
    void mutate_add_connection(std::mt19937& rng);
    void mutate_add_node(std::mt19937& rng);
    void mutate_weight(std::mt19937& rng);

    int key_;
    int next_node_key_{0};
    std::vector<int> input_keys_;
    std::vector<int> output_keys_;
    std::unordered_map<int, NodeGene> nodes_;
    std::unordered_map<long long, ConnectionGene> connections_;
};

}  // namespace dhn
