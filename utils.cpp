// utils functions

#include "utils.h"

std::vector<double> create_time_grid(double maturity, int time_steps) {
    if (time_steps <= 0) {
        throw std::invalid_argument("Number of time steps must be positive.");
    }

    std::vector<double> time_grid(time_steps + 1);
    double delta_t = maturity / time_steps;
    for (int i = 0; i <= time_steps; ++i) {
        time_grid[i] = i * delta_t;
    }
    return time_grid;
}