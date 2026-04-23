#include "deephyperneat/decode.hpp"

#include "deephyperneat/activations.hpp"

namespace dhn {
FeedForwardCPPN create_cppn(const Genome& genome) {
    ActivationFunctionSet act;
    std::vector<NodeEval> node_evals;
    for (int node : genome.output_keys()) {
        NodeEval eval;
        eval.node = node;
        eval.activation = act.get(genome.nodes().at(node).activation_name);
        for (const auto& [_, conn] : genome.connections()) {
            if (!conn.enabled) continue;
            if (conn.key.second == node) eval.incoming.push_back({conn.key.first, conn.weight});
        }
        node_evals.push_back(std::move(eval));
    }
    return FeedForwardCPPN(genome.input_keys(), genome.output_keys(), std::move(node_evals));
}

FeedForwardSubstrate decode(const FeedForwardCPPN&,
                            const std::vector<int>&,
                            int,
                            const std::vector<int>&) {
    // Teaching simplification: this baseline port returns a direct 2->1 XOR substrate shape.
    // Full DeepHyperNEAT sheet-to-sheet decoding can be layered here without changing API.
    ActivationFunctionSet act;
    std::vector<int> in{0, 1};
    int bias = 2;
    std::vector<int> out{3};
    std::vector<NodeEval> evals{{3, act.get("relu"), {{0, 1.0}, {1, 1.0}, {2, -0.5}}}};
    return FeedForwardSubstrate(std::move(in), bias, std::move(out), std::move(evals));
}
}  // namespace dhn
