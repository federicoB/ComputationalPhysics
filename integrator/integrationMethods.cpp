//
// Created by fede on 07/06/16.
//

//Reference for methods https://en.wikipedia.org/wiki/Numerical_integration#Quadrature_rules_based_on_interpolating_functions

#include "integrationMethods.h"

double rectangle(double leftExtreme, double rightExtreme, int numberOfSegments,
                 double (*functionToIntegrate)(const double &)) {
    //declare a variable sum for containing the sum of the areas of the rectangles
    double sum = 0;
    //determine the rectangle base subdividing the length of the interval for the desired numberOfSegments
    double rectangleBase = (rightExtreme - leftExtreme) / numberOfSegments;
    //for the numberOfSegments
    for (int i = 0; i < numberOfSegments; i++) {
        //determine the x-coordinate, left-bottom vertex of the rectangle
        double leftBottomVertexPosition = (leftExtreme + (rectangleBase * i)) / 2;
        //determine the area of the rectangle
        sum += rectangleBase * functionToIntegrate(leftBottomVertexPosition);
    }
    //return the calculated sum
    return sum;
}


double trapezoidal(double leftExtreme, double rightExtreme, int numberOfSegments,
                   double (*functionToIntegrate)(const double &)) {
    //declare a variable sum for containing the sum of the areas of the trapezoids
    double sum = 0.0;
    //determine the trapezoid base subdividing the length of the interval for the desired numberOfSegments
    double trapezoidBase = (rightExtreme - leftExtreme) / numberOfSegments;
    //for all the numberOfSegments
    for (int i = 0; i < numberOfSegments; i++) {
        //determine the position of the bottom-left vertex of the trapezoid
        double bottomLeftVertex = leftExtreme + (trapezoidBase * i);
        //determine the position of the bottom-right vertex of the trapezoid
        double bottomRightVertex = leftExtreme + (trapezoidBase * (i + 1));
        //determine the area with the formula: ((small base + big base)*height)/2
        double area =
                ((functionToIntegrate(bottomLeftVertex) + functionToIntegrate(bottomRightVertex)) * trapezoidBase) / 2;
        //increase the sum of the areas
        sum += area;
    }
    //return the calculated sum
    return sum;
}

//reference https://en.wikipedia.org/wiki/Simpson%27s_rule#Composite_Simpson.27s_rule

double simpson(double leftExtreme, double rightExtreme, int numberOfSegments,
               double (*functionToIntegrate)(const double &)) {
    //declare a variable sum for containing the sum of the areas of the parabola
    double sum = 0.0;
    //determine the segment length base subdividing the length of the interval for the desired numberOfSegments
    double segmentLength = (rightExtreme - leftExtreme) / numberOfSegments;
    //for all the numberOfSegments
    for (int i = 0; i <= numberOfSegments; i++) {
        double point1 = leftExtreme + segmentLength * i;
        double point2 = leftExtreme + segmentLength * i + segmentLength/2;
        double point3 = leftExtreme + segmentLength * (i+1);
        sum += functionToIntegrate(point1) + 4 * functionToIntegrate(point2) + functionToIntegrate(point3);
    }
    sum = sum * (segmentLength / 6);
    return sum;
}