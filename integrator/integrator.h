//
// Created by fede on 20/03/16.
//

#ifndef INTEGRATORE_INTEGRATORE_H
#define INTEGRATORE_INTEGRATORE_H

double f(const double &x);

double rettangoli(double a, double b, int N);

double trapezi(double a, double b, int N);

double simpson(double a, double b, int N);

#endif //INTEGRATORE_INTEGRATORE_H
