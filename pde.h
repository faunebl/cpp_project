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
    Matrix P_matrix;
    Matrix Q_matrix;
    Matrix V_vector;;

    void initialize_matrices(double dt, double dx, double volatility, double risk_free_rate, double theta);
    void compute_boundary_conditions(double dt, double dx, double risk_free_rate, double theta);

public:
    PDEPricer(double maturity, int time_steps, double multiplier, double volatility, int space_steps,
              double risk_free_rate, double theta);

    std::vector<double> solve() const;
};

#endif // PDE_H