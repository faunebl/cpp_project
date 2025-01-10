// pde.cpp
#include "pde.h"
#include <iostream>
#include <stdexcept>

PDEPricer::PDEPricer(double maturity, int time_steps, double multiplier, double volatility, int space_steps,
                     double risk_free_rate)
    : time_grid(create_time_grid(maturity, time_steps)),
      space_grid(create_space_grid(multiplier, volatility, space_steps)),
      boundary_conditions_lower(space_steps, 0.0),
      boundary_conditions_upper(space_steps, 0.0),
      terminal_condition(space_steps, 0.0),
      a_matrix(space_steps, space_steps),
      b_matrix(space_steps, space_steps),
      c_matrix(space_steps, space_steps),
      d_matrix(space_steps, space_steps) {
    double dt = maturity / time_steps;
    double dx = (2 * multiplier * volatility) / (space_steps - 1);

    // Log initialization
    std::cout << "Initializing PDEPricer with parameters:\n";
    std::cout << "  Maturity: " << maturity << "\n";
    std::cout << "  Time steps: " << time_steps << "\n";
    std::cout << "  Multiplier: " << multiplier << "\n";
    std::cout << "  Volatility: " << volatility << "\n";
    std::cout << "  Space steps: " << space_steps << "\n";
    std::cout << "  Risk-free rate: " << risk_free_rate << "\n";

    // Initialize boundary and terminal conditions for a European call option
    for (size_t i = 0; i < space_grid.size(); ++i) {
        terminal_condition[i] = std::max(space_grid[i] - 1.0, 0.0); // payoff: max(S - K, 0), assume K = 1
    }
    boundary_conditions_lower = std::vector<double>(time_steps + 1, 0.0);
    boundary_conditions_upper = std::vector<double>(time_steps + 1, multiplier * volatility - 1.0);

    initialize_matrices(dt, dx, volatility, risk_free_rate);
}

void PDEPricer::initialize_matrices(double dt, double dx, double volatility, double risk_free_rate) {
    size_t n = space_grid.size();
    for (size_t i = 1; i < n - 1; ++i) {
        double sigma2 = volatility * volatility;
        double x = space_grid[i];

        a_matrix[i][i] = 1.0 / dt + sigma2 * x * x / (dx * dx) + risk_free_rate;
        b_matrix[i][i - 1] = -0.5 * sigma2 * x * x / (dx * dx) - risk_free_rate * x / (2 * dx);
        b_matrix[i][i + 1] = -0.5 * sigma2 * x * x / (dx * dx) + risk_free_rate * x / (2 * dx);
        c_matrix[i][i] = 0.0; // No off-diagonal time terms in this simple scheme
        d_matrix[i][i] = -risk_free_rate; // Discounting

        // Log matrix coefficients
        std::cout << "Matrix coefficients at i = " << i << ":\n";
        std::cout << "  a_matrix[i][i]: " << a_matrix[i][i] << "\n";
        std::cout << "  b_matrix[i][i-1]: " << b_matrix[i][i - 1] << "\n";
        std::cout << "  b_matrix[i][i+1]: " << b_matrix[i][i + 1] << "\n";
        std::cout << "  c_matrix[i][i]: " << c_matrix[i][i] << "\n";
        std::cout << "  d_matrix[i][i]: " << d_matrix[i][i] << "\n";
    }
}

std::vector<double> PDEPricer::solve() const {
    int time_steps = time_grid.size() - 1;
    int space_steps = space_grid.size();

    std::vector<double> current_solution = terminal_condition;

    for (int t = time_steps - 1; t >= 0; --t) {
        std::vector<double> next_solution(space_steps, 0.0);

        for (int i = 1; i < space_steps - 1; ++i) {
            next_solution[i] = a_matrix[i][i] * current_solution[i] +
                              b_matrix[i][i - 1] * current_solution[i - 1] +
                              b_matrix[i][i + 1] * current_solution[i + 1] +
                              c_matrix[i][i] * current_solution[i] +
                              d_matrix[i][i];
        }

        next_solution[0] = boundary_conditions_lower[t];
        next_solution[space_steps - 1] = boundary_conditions_upper[t];

        // Log intermediate solution
        std::cout << "Time step t = " << t << ", intermediate solution:\n";
        for (double value : next_solution) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        current_solution = next_solution;
    }

    return current_solution;
}