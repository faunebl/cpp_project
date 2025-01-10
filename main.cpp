// main.cpp
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

    return 0;
}