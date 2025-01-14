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

std::vector<double> create_space_grid(double multiplier, double volatility, int space_steps) {
    if (space_steps <= 0) {
        throw std::invalid_argument("Number of space steps must be positive.");
    }
    if (volatility <= 0) {
        throw std::invalid_argument("Volatility must be positive.");
    }

    std::vector<double> space_grid(space_steps);
    double boundary = multiplier * volatility + 1.0; // Ensures it's larger than K
    double delta_x = 2 * boundary / (space_steps - 1);

    for (int i = 0; i < space_steps; ++i) {
        space_grid[i] = -boundary + i * delta_x;
    }
    return space_grid;
}