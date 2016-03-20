//BSD License

#include <fstream>
#include <cmath>
#include <iostream>
#include "integratore.h"


double f(const double &x) {
    return sin(x);
}


double rettangoli(double a, double b, int N) {
    double sum = 0.0;
    double dx = (b - a) / N;

    for (int i = 0; i < N; i++) {
        double xi = a + (dx * i);
        sum += dx * f(xi);
    }

    return sum;
}


double trapezi(double a, double b, int N) {
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

        for (int n = 1; n < 100; n++) //calcolo degli integrali con varie discretizzazioni(segmenti)
        {
            int N = n * n; //numero di segmenti
            outputFile << N << " " << rettangoli(0.0, 1.0, N) - truth /*errore con il metodo dei rettangoli*/ << " " <<
            trapezi(0.0, 1.0, N) - truth << " " << simpson(0.0, 1.0, N) - truth << std::endl;
        }

    }
    outputFile.close();

    return 0;
}
