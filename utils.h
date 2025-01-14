// utility functions 
#ifndef TIMEGRID_H
#define TIMEGRID_H

#include <vector>
#include <stdexcept>

std::vector<double> create_time_grid(double maturity, int time_steps);
std::vector<double> create_space_grid(double multiplier, double volatility, int space_steps);
void save_data_to_file(const std::string& filename, const std::vector<int>& steps, const std::vector<double>& errors);
void plot_with_gnuplot(const std::string& datafile, const std::string& output_image);

#endif // TIMEGRID_H