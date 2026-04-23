#include "deephyperneat/activations.hpp"

#include <cmath>
#include <stdexcept>

namespace dhn {
ActivationFunctionSet::ActivationFunctionSet() {
    add("sigmoid", [](double x) { return 1.0 / (1.0 + std::exp(-x)); });
    add("sin", [](double x) { return std::sin(x); });
    add("cos", [](double x) { return std::cos(x); });
    add("relu", [](double x) { return x > 0.0 ? x : 0.0; });
    add("linear", [](double x) { return x; });
    add("gauss", [](double x) { return std::exp(-5.0 * x * x); });
    add("sharp_gauss", [](double x) { return std::exp(-100.0 * x * x); });
    add("sharp_gauss2", [](double x) { const double d = x - 2.0; return std::exp(-100.0 * d * d); });
}

void ActivationFunctionSet::add(const std::string& name, Activation fn) { functions_[name] = std::move(fn); }

const Activation& ActivationFunctionSet::get(const std::string& name) const {
    auto it = functions_.find(name);
    if (it == functions_.end()) {
        throw std::runtime_error("Unknown activation: " + name);
    }
    return it->second;
}
}  // namespace dhn
