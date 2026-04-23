#pragma once

/*
This file provides textual reporting helpers.
Teaching note: reporters make evolutionary progress visible (fitness, complexity, species),
which is essential for diagnosing search behavior and tuning mutation parameters.
*/

#include "deephyperneat/population.hpp"

namespace dhn {
void report_generation(int generation, double best, double avg);
}  // namespace dhn
