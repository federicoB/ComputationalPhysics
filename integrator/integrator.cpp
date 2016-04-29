//BSD License

#include <fstream>
#include <cmath>
#include <iostream>
#include "integratore.h"


double f(const double &x) {
    //sample function
    return sin(x);
}

//Reference for methods https://en.wikipedia.org/wiki/Numerical_integration#Quadrature_rules_based_on_interpolating_functions

double rectangle(double leftExtreme, double rightExtreme, int numberOfSegments) {
    //declare a variable sum for containg the sum of the areas of the rectangles
    double sum = 0;
    //determine the rectangble base subdividing the leght of the interval for the desired numberOfSegments
    double rectancleBase = (rightExtreme - leftExtreme) / numberOfSegments;
    //for the numberOfSegments
    for (int i = 0; i < numberOfSegments; i++) {
        //determine the x-cordinate, left-bottom vertex of the rectangle
        double leftBottomVertexPosition = leftExtreme + (rectancleBase * i);
        //determine the area of the rectangle
        sum += rectancleBase * f(leftBottomVertexPosition);
    }
    //return the calculated sum
    return sum;
}


double trapezoidal(double leftExtreme, double rightExtreme, int numberOfSegments) {
    //declare a variable sum for containg the sum of the areas of the traperzoids
    double sum = 0.0;
    //determine the trapezoid base subdividing the leght of the interval for the desired numberOfSegments
    double trapezoidBase = (rightExtreme - leftExtreme) / numberOfSegments;
    //for all the numberOfSegments
    for (int i = 0; i < numberOfSegments; i++) {
        //determine the position of the bottom-left vertex of the trapezoid
        double bottomLeftVertex = leftExtreme + (trapezoidBase * i);
        //determine the position of the bottom-right verted of the trapezoid
        double bottomRightVertex = leftExtreme + (trapezoidBase * (i+1));
        //determine the area with the forumala: ((small base + big base)*height)/2
        double area = ((f(bottomLeftVertex)+f(bottomRightVertex))*trapezoidBase)/2;
        //increase the sum of the areas
        sum += area;
    }
    //return the calculated sum
    return sum;
}

double simpson(double a, double b, int N) {
    //TODO implement simpson method
    return 0.0;
}

int main() {
    //create an output stream to a file
    std::ofstream outputFile("outputFile.txt");
    //if the file is open
    if (outputFile.is_open()) {
        //determine the real value of the sine on 1 (the cose is always complementary to it)
        double truth = 1.0 - cos(1.0);
        //create a legend for the output file
        outputFile << "A   \t B\t\t\tC" << std::endl;
        //loop for varius number of segments
        for (int n = 1; n < 100; n++)
        {
            //increase exponentially the number of segments
            int N = n * n;
            //set the output in scientific notation
            outputFile.setf(std::ios_base::scientific);
            //set the decimal precision to 2
            outputFile.precision(2);
            //print current number of segments
            outputFile << N << "   \t"
            //error with rectangle method
            << rectangle(0.0, 1.0, N) - truth << "\t"
            //error with trapezoidal method
            << trapezoidal(0.0, 1.0, N) - truth << "\t"
            //error with simpson method
            << simpson(0.0, 1.0, N) - truth << std::endl;
        }

    }
    //close the output file
    outputFile.close();
    return 0;
}
