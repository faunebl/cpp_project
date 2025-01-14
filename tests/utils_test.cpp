// utils_test.cpp
// tests for the utility functions (only first two, the last two need the rest of the code to run)
#include "utils.h"
#include <iostream>

int main() {
    std::cout << "Testing time grid creation:\n";
    double maturity = 1.0;
    int time_steps = 10;
    std::vector<double> time_grid = create_time_grid(maturity, time_steps);

    std::cout << "Time grid: ";
    for (double t : time_grid) {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    std::cout << "\nTesting space grid creation:\n";
    double multiplier = 3.0;
    double volatility = 0.2;
    int space_steps = 11;
    std::vector<double> space_grid = create_space_grid(multiplier, volatility, space_steps);

    std::cout << "Space grid: ";
    for (double x : space_grid) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}