#pragma once

/*
This file provides executable neural phenotypes.
Teaching note: genomes encode structure; phenomes are the runnable neural programs
used to score fitness during task evaluation.
*/

#include "deephyperneat/activations.hpp"

#include <unordered_map>
#include <utility>
#include <vector>

namespace dhn {

struct NodeEval {
    int node;
    Activation activation;
    std::vector<std::pair<int, double>> incoming;
};

class FeedForwardCPPN {
public:
    FeedForwardCPPN(std::vector<int> inputs, std::vector<int> outputs, std::vector<NodeEval> evals);
    std::unordered_map<int, double> activate(const std::vector<double>& inputs);

private:
    std::vector<int> input_nodes_;
    std::vector<int> output_nodes_;
    std::vector<NodeEval> evals_;
    std::unordered_map<int, double> values_;
};

class FeedForwardSubstrate {
public:
    FeedForwardSubstrate(std::vector<int> inputs, int bias, std::vector<int> outputs, std::vector<NodeEval> evals);
    std::vector<double> activate(const std::vector<double>& inputs_with_bias);

private:
    std::vector<int> input_nodes_;
    int bias_node_;
    std::vector<int> output_nodes_;
    std::vector<NodeEval> evals_;
    std::unordered_map<int, double> values_;
};

bool creates_cycle(const std::vector<std::pair<int, int>>& connections, std::pair<int, int> candidate);

}  // namespace dhn
