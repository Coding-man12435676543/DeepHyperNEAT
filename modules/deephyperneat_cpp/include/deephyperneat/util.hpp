#pragma once

/*
This utility file centralizes small statistical helpers.
Teaching note: evolutionary algorithms repeatedly summarize fitness distributions,
so these helpers reduce duplication and keep math behavior consistent.
*/

#include <vector>

namespace dhn {
double mean(const std::vector<double>& values);
double median(std::vector<double> values);
double variance(const std::vector<double>& values);
double stdev(const std::vector<double>& values);
}  // namespace dhn
