// pde.h
#ifndef PDE_H
#define PDE_H

#include <vector>
#include "utils.h"
#include "Matrix.h"

class PDEPricer {
private:
    std::vector<double> time_grid;
    std::vector<double> space_grid;
    std::vector<double> boundary_conditions_lower;
    std::vector<double> boundary_conditions_upper;
    std::vector<double> terminal_condition;
    Matrix a_matrix;
    Matrix b_matrix;
    Matrix c_matrix;
    Matrix d_matrix;

    void initialize_matrices(double dt, double dx, double volatility, double risk_free_rate);

public:
    PDEPricer(double maturity, int time_steps, double multiplier, double volatility, int space_steps,
              double risk_free_rate);

    std::vector<double> solve() const;
};

#endif // PDE_H