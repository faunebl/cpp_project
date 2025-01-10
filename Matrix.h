// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows;
    int cols;

public:
    Matrix(int rows, int cols);
    Matrix(const std::vector<std::vector<double>>& data);

    int get_rows() const;
    int get_cols() const;

    std::vector<double>& operator[](int index);
    const std::vector<double>& operator[](int index) const;

    Matrix inverse() const;
    bool is_invertible() const;
    double determinant() const;

    void print() const;
};

#endif // MATRIX_H



