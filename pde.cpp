// pde.cpp
#include "pde.h"
#include <iostream>
#include <stdexcept>

PDEPricer::PDEPricer(double maturity, int time_steps, double multiplier, double volatility, int space_steps,
                     const std::vector<double>& boundary_conditions_lower,
                     const std::vector<double>& boundary_conditions_upper,
                     const std::vector<double>& terminal_condition,
                     const Matrix& a_matrix,
                     const Matrix& b_matrix,
                     const Matrix& c_matrix,
                     const Matrix& d_matrix)
    : time_grid(create_time_grid(maturity, time_steps)),
      space_grid(create_space_grid(multiplier, volatility, space_steps)),
      boundary_conditions_lower(boundary_conditions_lower),
      boundary_conditions_upper(boundary_conditions_upper),
      terminal_condition(terminal_condition),
      a_matrix(a_matrix),
      b_matrix(b_matrix),
      c_matrix(c_matrix),
      d_matrix(d_matrix) {
    if (boundary_conditions_lower.size() != space_grid.size() ||
        boundary_conditions_upper.size() != space_grid.size() ||
        terminal_condition.size() != space_grid.size()) {
        throw std::invalid_argument("Boundary and terminal conditions must match space grid size.");
    }
}

std::vector<double> PDEPricer::solve() const {
    int time_steps = time_grid.size() - 1;
    int space_steps = space_grid.size();

    std::vector<double> current_solution = terminal_condition;

    for (int t = time_steps - 1; t >= 0; --t) {
        std::vector<double> next_solution(space_steps);

        for (int i = 1; i < space_steps - 1; ++i) {
            next_solution[i] = a_matrix[i][i] * current_solution[i] +
                              b_matrix[i][i - 1] * current_solution[i - 1] +
                              b_matrix[i][i + 1] * current_solution[i + 1] +
                              c_matrix[i][i] * current_solution[i] +
                              d_matrix[i][i];
        }

        next_solution[0] = boundary_conditions_lower[t];
        next_solution[space_steps - 1] = boundary_conditions_upper[t];

        current_solution = next_solution;
    }

    return current_solution;
}