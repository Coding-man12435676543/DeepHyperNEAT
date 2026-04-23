#include "deephyperneat/visualize.hpp"

#include <fstream>

namespace dhn {
void draw_net(const FeedForwardSubstrate&, const std::string& filename_prefix) {
    std::ofstream out(filename_prefix + ".txt");
    out << "DeepHyperNEAT C++ visualization placeholder.\n";
    out << "Use this output as an API-stable hook for adding Graphviz later.\n";
}
}  // namespace dhn
