#include <cmath>
#include <iostream>

// Black-Scholes function
double black_scholes_price(double S, double K, double T, double r, double sigma, bool is_call) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    auto normal_cdf = [](double x) -> double {
        return 0.5 * std::erfc(-x * std::sqrt(0.5));
    };

    if (is_call) {
        return S * normal_cdf(d1) - K * std::exp(-r * T) * normal_cdf(d2);
    } else {
        return K * std::exp(-r * T) * normal_cdf(-d2) - S * normal_cdf(-d1);
    }
}