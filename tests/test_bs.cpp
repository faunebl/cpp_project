#include <cmath>
#include <iostream>
#include "black_scholes.h"

int main() {
    // Parameters
    double S = 100.0;   // Spot price
    double K = 100.0;   // Strike price
    double T = 1.0;     // Time to maturity (in years)
    double r = 0.05;    // Risk-free rate
    double sigma = 0.2; // Volatility
    bool is_call = true; // True for call, false for put

    // Price calculation
    double price = black_scholes_price(S, K, T, r, sigma, is_call);
    std::cout << "The Black-Scholes price of the "
              << (is_call ? "call" : "put") << " option is: " << price << std::endl;

    return 0;
}
