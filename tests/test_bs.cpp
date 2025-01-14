#include <cmath>
#include <iostream>
#include "black_scholes.h"

int main() {
    // params
    double S = 100.0;
    double K = 100.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;
    bool is_call = true;

    // calcultaing price
    double price = black_scholes_price(S, K, T, r, sigma, is_call);
    // display price
    std::cout << "The Black-Scholes price of the "
              << (is_call ? "call" : "put") << " option is: " << price << std::endl;

    return 0;
}
