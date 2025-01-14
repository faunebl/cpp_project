#include <iostream>
#include <cmath>
#include "pde.h"
#include "utils.h"
#include "black_scholes.h"

int main() {
    // Parameters
    double maturity = 1.0;
    double volatility = 0.2;
    double risk_free_rate = 0.05;
    double multiplier = 5.0;
    double S0 = 1.0;
    double K = 1.0;
    double theta = 0.5;
    bool is_call = true;

    // Black-Scholes reference price
    double bs_price = black_scholes_price(S0, K, maturity, risk_free_rate, volatility, is_call);

    // Convergence study
    std::vector<int> steps = {10, 50, 100, 200, 400}; // Time and space steps
    std::vector<double> errors;

    std::cout << "Black-Scholes Price: " << bs_price << "\n";

    for (int n : steps) {
        int m = n; // Using the same value for space steps for simplicity
        PDEPricer pde_pricer(maturity, n, multiplier, volatility, m, risk_free_rate, theta);

        // Solve PDE
        std::vector<double> pde_solution = pde_pricer.solve();

        // Approximate price at S0 (middle of the space grid)
        double pde_price = pde_solution[m / 2];
        double error = std::abs(bs_price - pde_price);
        errors.push_back(error);

        std::cout << "Time Steps: " << n << ", Space Steps: " << m
                  << ", PDE Price: " << pde_price << ", Error: " << error << "\n";
    }

    // Save data to file
    std::string datafile = "convergence_data.csv";
    save_data_to_file(datafile, steps, errors);

    // Plot using gnuplot
    std::string output_image = "convergence_graph.png";
    plot_with_gnuplot(datafile, output_image);

    std::cout << "Convergence graph saved to " << output_image << ".\n";

    return 0;
}