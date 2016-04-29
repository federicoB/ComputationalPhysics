//BSD License

#include <fstream>
#include <cmath>
#include <iostream>
#include "integratore.h"


double f(const double &x) {
    return sin(x);
}

//Reference for methods https://en.wikipedia.org/wiki/Numerical_integration#Quadrature_rules_based_on_interpolating_functions

double rectangle(double a, double b, int N) {
    double sum = 0.0;
    double dx = (b - a) / N;

    for (int i = 0; i < N; i++) {
        double xi = a + (dx * i);
        sum += dx * f(xi);
    }

    return sum;
}


double trapezoidal(double a, double b, int N) {
    double sum = 0.0;
    double dx = (b - a) / N;

    for (int i = 0; i < N; i++) {
        double xi = a + (dx * i);
        double xi2 = a + (dx * (i+1));
        double area = ((f(xi)+f(xi2))*dx)/2;
        sum += area;
    }

    return sum;
}

double simpson(double a, double b, int N) {
    //DA FARE
    return 0.0;
}

int main() {
    std::ofstream outputFile("outputFile.txt");
    if (outputFile.is_open()) {
        double truth = 1.0 - cos(1.0);
        outputFile << "A   \t B\t\t\tC" << std::endl;
        for (int n = 1; n < 100; n++) //calcolo degli integrali con varie discretizzazioni(segmenti)
        {
            int N = n * n; //numero di segmenti
            outputFile.setf(std::ios_base::scientific);
            outputFile.precision(2);
            outputFile << N << "   \t" << rectangle(0.0, 1.0, N) - truth /*errore con il metodo dei rectangle*/ << "\t" <<
                    trapezoidal(0.0, 1.0, N) - truth << "\t" << simpson(0.0, 1.0, N) - truth << std::endl;
        }

    }
    outputFile.close();

    return 0;
}
