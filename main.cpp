// main.cpp
#include "pde.h"
#include "Matrix.h"
#include <iostream>

int main() {
    double maturity = 1.0;
    int time_steps = 10;
    double multiplier = 3.0;
    double volatility = 0.2;
    int space_steps = 11;

    std::vector<double> boundary_conditions_lower(space_steps, 0.0);
    std::vector<double> boundary_conditions_upper(space_steps, 1.0);
    std::vector<double> terminal_condition(space_steps, 0.5);

    Matrix a_matrix(space_steps, space_steps);
    Matrix b_matrix(space_steps, space_steps);
    Matrix c_matrix(space_steps, space_steps);
    Matrix d_matrix(space_steps, space_steps);

    PDEPricer pricer(maturity, time_steps, multiplier, volatility, space_steps,
                     boundary_conditions_lower, boundary_conditions_upper,
                     terminal_condition, a_matrix, b_matrix, c_matrix, d_matrix);

    std::vector<double> prices = pricer.solve();

    std::cout << "Prices: ";
    for (double price : prices) {
        std::cout << price << " ";
    }
    std::cout << std::endl;

    return 0;
}