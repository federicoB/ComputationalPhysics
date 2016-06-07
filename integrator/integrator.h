//
// Created by fede on 20/03/16.
//

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

//Reference for methods https://en.wikipedia.org/wiki/Numerical_integration#Quadrature_rules_based_on_interpolating_functions

double rectangle(double leftExtreme, double rightExtreme, int numberOfSegments, double (*functionToIntegrate)(const double &));

double trapezoidal(double leftExtreme, double rightExtreme, int numberOfSegments, double (*functionToIntegrate)(const double &));

//reference https://en.wikipedia.org/wiki/Simpson%27s_rule#Composite_Simpson.27s_rule

double simpson(double a, double b, int N, double (*functionToIntegrate)(const double &));

#endif //INTEGRATOR_H
