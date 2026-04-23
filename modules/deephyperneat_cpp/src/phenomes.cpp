#include "deephyperneat/phenomes.hpp"

#include <stdexcept>
#include <unordered_set>

namespace dhn {
FeedForwardCPPN::FeedForwardCPPN(std::vector<int> inputs, std::vector<int> outputs, std::vector<NodeEval> evals)
    : input_nodes_(std::move(inputs)), output_nodes_(std::move(outputs)), evals_(std::move(evals)) {
    for (int i : input_nodes_) values_[i] = 0.0;
    for (int o : output_nodes_) values_[o] = 0.0;
}

std::unordered_map<int, double> FeedForwardCPPN::activate(const std::vector<double>& inputs) {
    if (inputs.size() != input_nodes_.size()) throw std::runtime_error("Input size mismatch for CPPN");
    for (size_t i = 0; i < inputs.size(); ++i) values_[input_nodes_[i]] = inputs[i];
    for (const auto& eval : evals_) {
        double sum = 0.0;
        for (const auto& [node_id, w] : eval.incoming) sum += values_[node_id] * w;
        values_[eval.node] = eval.activation(sum);
    }
    return values_;
}

FeedForwardSubstrate::FeedForwardSubstrate(std::vector<int> inputs, int bias, std::vector<int> outputs, std::vector<NodeEval> evals)
    : input_nodes_(std::move(inputs)), bias_node_(bias), output_nodes_(std::move(outputs)), evals_(std::move(evals)) {
    for (int i : input_nodes_) values_[i] = 0.0;
    values_[bias_node_] = 0.0;
    for (int o : output_nodes_) values_[o] = 0.0;
}

std::vector<double> FeedForwardSubstrate::activate(const std::vector<double>& inputs_with_bias) {
    if (inputs_with_bias.size() != input_nodes_.size() + 1) throw std::runtime_error("Input size mismatch for substrate");
    for (size_t i = 0; i < input_nodes_.size(); ++i) values_[input_nodes_[i]] = inputs_with_bias[i];
    values_[bias_node_] = inputs_with_bias.back();

    for (auto it = evals_.rbegin(); it != evals_.rend(); ++it) {
        double sum = 0.0;
        for (const auto& [node_id, w] : it->incoming) sum += values_[node_id] * w;
        values_[it->node] = it->activation(sum);
    }

    std::vector<double> out;
    out.reserve(output_nodes_.size());
    for (int o : output_nodes_) out.push_back(values_[o]);
    return out;
}

bool creates_cycle(const std::vector<std::pair<int, int>>& connections, std::pair<int, int> candidate) {
    const auto [i, o] = candidate;
    if (i == o) return true;

    std::unordered_set<int> visited{o};
    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& [a, b] : connections) {
            if (visited.count(a) && !visited.count(b)) {
                if (b == i) return true;
                visited.insert(b);
                changed = true;
            }
        }
    }
    return false;
}
}  // namespace dhn
