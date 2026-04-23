#include "deephyperneat/reporters.hpp"

#include <iostream>

namespace dhn {
void report_generation(int generation, double best, double avg) {
    std::cout << "Generation " << generation << " | best=" << best << " | avg=" << avg << '\n';
}
}  // namespace dhn
