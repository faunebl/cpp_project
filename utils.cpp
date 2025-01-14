// utils functions

#include "utils.h"
#include <fstream>
#include <iostream>


std::vector<double> create_time_grid(double maturity, int time_steps) {
    if (time_steps <= 0) {
        throw std::invalid_argument("Number of time steps must be positive.");
    }

    std::vector<double> time_grid(time_steps + 1);
    double delta_t = maturity / time_steps;
    for (int i = 0; i <= time_steps; ++i) {
        time_grid[i] = i * delta_t;
    }
    return time_grid;
}

std::vector<double> create_space_grid(double multiplier, double volatility, int space_steps) {
    if (space_steps <= 0) {
        throw std::invalid_argument("Number of space steps must be positive.");
    }
    if (volatility <= 0) {
        throw std::invalid_argument("Volatility must be positive.");
    }

    std::vector<double> space_grid(space_steps);
    double boundary = multiplier * volatility + 1.0; // Ensures it's larger than K
    double delta_x = 2 * boundary / (space_steps - 1);

    for (int i = 0; i < space_steps; ++i) {
        space_grid[i] = -boundary + i * delta_x;
    }
    return space_grid;
}

// Function to save data to a file
void save_data_to_file(const std::string& filename, const std::vector<int>& steps, const std::vector<double>& errors) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }
    outfile << "Steps,Error\n";
    for (size_t i = 0; i < steps.size(); ++i) {
        outfile << steps[i] << "," << errors[i] << "\n";
    }
    outfile.close();
}

// Function to generate a plot using gnuplot
void plot_with_gnuplot(const std::string& datafile, const std::string& output_image) {
    std::string gnuplot_cmd = 
        "gnuplot -e \"set terminal png size 800,600; "
        "set output '" + output_image + "'; "
        "set title 'Convergence of PDE Solution to Black-Scholes Price'; "
        "set xlabel 'Number of Steps (n and m)'; "
        "set ylabel 'Error (|BS Price - PDE Price|)'; "
        "set grid; "
        "plot '" + datafile + "' using 1:2 with linespoints title 'Error';\"";
    system(gnuplot_cmd.c_str());
}