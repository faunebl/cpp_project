// main.cpp
#include "pde.h"
#include <iostream>

int main() {
    double maturity = 1.0;
    int time_steps = 10;
    double multiplier = 3.0;
    double volatility = 0.2;
    int space_steps = 11;
    double risk_free_rate = 0.05;

    std::cout << "Starting PDE pricing...\n";

    PDEPricer pricer(maturity, time_steps, multiplier, volatility, space_steps, risk_free_rate);

    std::vector<double> prices = pricer.solve();

    std::cout << "Final Prices: ";
    for (double price : prices) {
        std::cout << price << " ";
    }
    std::cout << std::endl;

    return 0;
}
