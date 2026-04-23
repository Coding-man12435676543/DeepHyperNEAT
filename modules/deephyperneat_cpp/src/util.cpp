#include "deephyperneat/util.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

namespace dhn {
double mean(const std::vector<double>& values) {
    if (values.empty()) return 0.0;
    return std::accumulate(values.begin(), values.end(), 0.0) / static_cast<double>(values.size());
}

double median(std::vector<double> values) {
    if (values.empty()) return 0.0;
    std::sort(values.begin(), values.end());
    const size_t n = values.size();
    if (n % 2 == 1) return values[n / 2];
    return 0.5 * (values[n / 2 - 1] + values[n / 2]);
}

double variance(const std::vector<double>& values) {
    if (values.empty()) return 0.0;
    const double m = mean(values);
    double acc = 0.0;
    for (double v : values) {
        const double d = v - m;
        acc += d * d;
    }
    return acc / static_cast<double>(values.size());
}

double stdev(const std::vector<double>& values) { return std::sqrt(variance(values)); }
}  // namespace dhn
