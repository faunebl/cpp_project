// utility functions 
#ifndef TIMEGRID_H
#define TIMEGRID_H

#include <vector>
#include <stdexcept>

std::vector<double> create_time_grid(double maturity, int time_steps);
std::vector<double> create_space_grid(double multiplier, double volatility, int space_steps);

#endif // TIMEGRID_H