#pragma once

/*
This visualization interface is intentionally lightweight.
Teaching note: original Python used graphviz; this C++ port keeps a stable API
and emits a readable text representation without adding heavy dependencies.
*/

#include "deephyperneat/phenomes.hpp"

#include <string>

namespace dhn {
void draw_net(const FeedForwardSubstrate& net, const std::string& filename_prefix);
}  // namespace dhn
