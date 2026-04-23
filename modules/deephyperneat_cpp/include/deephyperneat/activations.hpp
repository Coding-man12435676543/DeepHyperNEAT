#pragma once

/*
This file defines activation functions used by both CPPNs and substrates.
Teaching note: activation functions are the non-linear pieces that make networks expressive.
The registry lets evolution store activation names in genes and resolve them at runtime.
*/

#include <functional>
#include <string>
#include <unordered_map>

namespace dhn {
using Activation = std::function<double(double)>;

class ActivationFunctionSet {
public:
    ActivationFunctionSet();
    void add(const std::string& name, Activation fn);
    const Activation& get(const std::string& name) const;

private:
    std::unordered_map<std::string, Activation> functions_;
};
}  // namespace dhn
