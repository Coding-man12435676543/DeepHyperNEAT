/*
This example demonstrates the C++ DeepHyperNEAT workflow end-to-end.
Teaching note: it mirrors the Python XOR study by evaluating genomes on XOR,
then letting the population run mutation/speciation/reproduction until fitness goal.
*/

#include "deephyperneat/decode.hpp"
#include "deephyperneat/population.hpp"

#include <cmath>
#include <iostream>
#include <vector>

int main() {
    using namespace dhn;

    Population pop(/*size=*/50, /*seed=*/123);

    const std::vector<std::pair<double, double>> xor_inputs{{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    const std::vector<double> xor_expected{0, 1, 1, 0};

    auto task = [&](std::unordered_map<int, Genome>& genomes) {
        for (auto& [_, genome] : genomes) {
            auto cppn = create_cppn(genome);
            auto substrate = decode(cppn, {1, 2}, 1, {1, 3});
            double err = 0.0;
            for (size_t i = 0; i < xor_inputs.size(); ++i) {
                auto out = substrate.activate({xor_inputs[i].first, xor_inputs[i].second, 1.0});
                const double d = out.front() - xor_expected[i];
                err += (d * d) / 4.0;
            }
            genome.fitness = 1.0 - err;
        }
    };

    auto winner = pop.run(task, /*goal=*/0.98, /*generations=*/50);
    std::cout << "Winner genome: " << winner.key() << " fitness=" << winner.fitness << "\n";
    return 0;
}
