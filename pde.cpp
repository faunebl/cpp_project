// pde.cpp
#include "pde.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

PDEPricer::PDEPricer(double maturity, int time_steps, double multiplier, double volatility, int space_steps,
                     double risk_free_rate, double theta)
    : time_grid(create_time_grid(maturity, time_steps)),
      space_grid(create_space_grid(multiplier, volatility, space_steps)),
      boundary_conditions_lower(time_steps + 1, 0.0),
      boundary_conditions_upper(time_steps + 1, 0.0),
      terminal_condition(space_steps, 0.0),
      P_matrix(space_steps - 2, space_steps - 2),
      Q_matrix(space_steps - 2, space_steps - 2),
      V_vector(space_steps - 2, 0.0) {
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

    // Initialize boundary and terminal conditions
    for (size_t i = 0; i < space_grid.size(); ++i) {
        terminal_condition[i] = std::max(space_grid[i] - 1.0, 0.0); // payoff: max(S - K, 0), assume K = 1
    }
    compute_boundary_conditions(dt, dx, risk_free_rate, theta);
    initialize_matrices(dt, dx, volatility, risk_free_rate, theta);
}

void PDEPricer::compute_boundary_conditions(double dt, double dx, double risk_free_rate, double theta) {
    for (size_t t = 0; t < time_grid.size(); ++t) {
        boundary_conditions_upper[t] = (space_grid.back() - 1.0) * exp(-risk_free_rate * time_grid[t]);
    }
    std::cout << "Boundary conditions (upper): ";
    for (double bc : boundary_conditions_upper) {
        std::cout << bc << " ";
    }
    std::cout << "\n";
}

void PDEPricer::initialize_matrices(double dt, double dx, double volatility, double risk_free_rate, double theta) {
    size_t n = space_grid.size();
    double sigma2 = volatility * volatility;

    for (size_t i = 1; i < n - 1; ++i) {
        double x = space_grid[i];

        // Populate P matrix
        P_matrix[i - 1][i - 1] = 1.0 / dt + theta * (2 * sigma2 * x * x / (dx * dx) + risk_free_rate);
        if (i > 1) {
            P_matrix[i - 1][i - 2] = -theta * (0.5 * sigma2 * x * x / (dx * dx) - risk_free_rate * x / (2 * dx));
        }
        if (i < n - 2) {
            P_matrix[i - 1][i] = -theta * (0.5 * sigma2 * x * x / (dx * dx) + risk_free_rate * x / (2 * dx));
        }

        // Populate Q matrix
        Q_matrix[i - 1][i - 1] = 1.0 / dt - (1 - theta) * (2 * sigma2 * x * x / (dx * dx) + risk_free_rate);
        if (i > 1) {
            Q_matrix[i - 1][i - 2] = (1 - theta) * (0.5 * sigma2 * x * x / (dx * dx) - risk_free_rate * x / (2 * dx));
        }
        if (i < n - 2) {
            Q_matrix[i - 1][i] = (1 - theta) * (0.5 * sigma2 * x * x / (dx * dx) + risk_free_rate * x / (2 * dx));
        }
    }

    // Log matrices
    std::cout << "P Matrix:\n";
    P_matrix.print();
    std::cout << "Q Matrix:\n";
    Q_matrix.print();
}

std::vector<double> PDEPricer::solve() {
    int time_steps = time_grid.size() - 1;
    int space_steps = space_grid.size();

    std::vector<double> current_solution(space_steps - 2, 0.0);
    std::vector<double> next_solution(space_steps, 0.0);

    for (int t = time_steps - 1; t >= 0; --t) {
        // Compute V vector
        for (size_t i = 1; i < space_steps - 1; ++i) {
            V_vector[i - 1] = boundary_conditions_lower[t] + boundary_conditions_upper[t];
        }

        // Solve for next solution: U_i = -P_i^{-1}(Q_i U_{i+1} + V_i)
        std::vector<double> intermediate_solution = Q_matrix * current_solution;
        for (size_t i = 0; i < V_vector.size(); ++i) {
            intermediate_solution[i] += V_vector[i];
        }
        next_solution = P_matrix.solve(intermediate_solution);

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

    std::cout << "Final solution: ";
    for (double value : current_solution) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return current_solution;
}