//BSD License

#include <fstream>
#include <cmath>
#include <iostream>
#include "integrationMethods.h"

/**
 * An example function to integrate.
 */
double f(const double &x) {
    //sample function
    return sin(x);
}



int main() {
    //create an output stream to a file
    std::ofstream outputFile("outputFile.txt");
    //create a function pointer for the function to integrate
    double (*function)(const double &) = &f;
    //if the file is open
    if (outputFile.is_open()) {
        //determine the real value of definite integral of the sine from 0 to 1 with the antiderivative.
        double truth = 1 - cos(1);
        //create a legend for the output file
        outputFile << "A   \t B\t\t\tC" << std::endl;
        //loop for various number of segments
        for (int n = 1; n < 100; n++) {
            //increase exponentially the number of segments
            int N = n * n;
            //set the output in scientific notation
            outputFile.setf(std::ios_base::scientific);
            //set the decimal precision to 4
            outputFile.precision(4);
            //print current number of segments
            outputFile << N << "   \t"
            //error with rectangle method
            << rectangle(0, 1, N, function) - truth << "\t"
            //error with trapezoidal method
            << trapezoidal(0, 1, N, function) - truth << "\t"
            //error with simpson method
            << simpson(0, 1, N, function) - truth << std::endl;
        }

    }
    //close the output file
    outputFile.close();
    return 0;
}
