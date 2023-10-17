// interpolant.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <vector>
#include <iostream>
#include <cmath>

class NewtonInterpolator {
public:
    NewtonInterpolator(const std::vector<double>& nodes, const std::vector<double>& y_values) {
        dd_values_ = divided_differences(nodes, y_values);
        nodes_ = nodes;
    }

    double interpolate(double x) const {
        double p = dd_values_.back();
        for (int i = nodes_.size() - 2; i >= 0; i--) {
            p = dd_values_[i] + (x - nodes_[i]) * p;
        }
        return p;
    }

private:
    std::vector<double> nodes_;
    std::vector<double> dd_values_;

    std::vector<double> divided_differences(const std::vector<double>& x_values, const std::vector<double>& y_values) {
        std::vector<double> dd_values(y_values);
        int n = x_values.size();
        for (int k = 1; k < n; k++) {
            for (int i = n - 1; i >= k; i--) {
                dd_values[i] = (dd_values[i] - dd_values[i - 1]) / (x_values[i] - x_values[i - k]);
            }
        }
        return dd_values;
    }
};

double max_error(const NewtonInterpolator& interpolator) {
    std::vector<double> x_values(1000);
    double h = 2.0 / (x_values.size() - 1);
    for (int i = 0; i < x_values.size(); i++) {
        x_values[i] = 0 + i * h;
    }

    double max_err = 0;
    for (int i = 0; i < x_values.size(); i++) {
        double p = interpolator.interpolate(x_values[i]);
        double f = std::exp(x_values[i]);
        double err = std::abs(p - f);
        if (err > max_err) {
            max_err = err;
        }
    }

    return max_err;
}