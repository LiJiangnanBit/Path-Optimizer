//
// Created by ljn on 20-1-26.
//

#include "tools/tools.hpp"
#include "tools/spline.h"
#include "data_struct/data_struct.hpp"

namespace PathOptimizationNS {

double time_s(const clock_t &begin, const clock_t &end) {
    return static_cast<double>(end - begin) / CLOCKS_PER_SEC;
}

double time_ms(const clock_t &begin, const clock_t &end) {
    return static_cast<double>(end - begin) / CLOCKS_PER_SEC * 1000;
}

bool isEqual(double a, double b) {
    return fabs(a - b) < 0.000001;
}

double getHeading(const tk::spline &xs, const tk::spline &ys, double s) {
    double x_d1 = xs.deriv(1, s);
    double y_d1 = ys.deriv(1, s);
    return atan2(y_d1, x_d1);
}

double getCurvature(const tk::spline &xs, const tk::spline &ys, double tmp_s) {
    double x_d1 = xs.deriv(1, tmp_s);
    double y_d1 = ys.deriv(1, tmp_s);
    double x_d2 = xs.deriv(2, tmp_s);
    double y_d2 = ys.deriv(2, tmp_s);
    return (x_d1 * y_d2 - y_d1 * x_d2) / pow(pow(x_d1, 2) + pow(y_d1, 2), 1.5);
}

double distance(const State &p1, const State &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

State local2Global(const State &reference, const State &target) {
    double x = target.x * cos(reference.z) - target.y * sin(reference.z) + reference.x;
    double y = target.x * sin(reference.z) + target.y * cos(reference.z) + reference.y;
    double z = reference.z + target.z;
    return {x, y, z, target.k, target.s};
}

State global2Local(const State &reference, const State &target) {
    double dx = target.x - reference.x;
    double dy = target.y - reference.y;
    double x = dx * cos(reference.z) + dy * sin(reference.z);
    double y = -dx * sin(reference.z) + dy * cos(reference.z);
    double z = target.z - reference.z;;
    return {x, y, z, target.k, 0};
}

}
