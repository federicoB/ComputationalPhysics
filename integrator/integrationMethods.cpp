//
// Created by fede on 07/06/16.
//

//Reference for methods https://en.wikipedia.org/wiki/Numerical_integration#Quadrature_rules_based_on_interpolating_functions

#include "integrationMethods.h"

double rectangle(double leftExtreme, double rightExtreme, int numberOfSegments,
                 double (*functionToIntegrate)(const double &)) {
    //declare a variable sum for containg the sum of the areas of the rectangles
    double sum = 0;
    //determine the rectangble base subdividing the leght of the interval for the desired numberOfSegments
    double rectancleBase = (rightExtreme - leftExtreme) / numberOfSegments;
    //for the numberOfSegments
    for (int i = 0; i < numberOfSegments; i++) {
        //determine the x-cordinate, left-bottom vertex of the rectangle
        double leftBottomVertexPosition = (leftExtreme + (rectancleBase * i)) / 2;
        //determine the area of the rectangle
        sum += rectancleBase * functionToIntegrate(leftBottomVertexPosition);
    }
    //return the calculated sum
    return sum;
}


double trapezoidal(double leftExtreme, double rightExtreme, int numberOfSegments,
                   double (*functionToIntegrate)(const double &)) {
    //declare a variable sum for containg the sum of the areas of the traperzoids
    double sum = 0.0;
    //determine the trapezoid base subdividing the leght of the interval for the desired numberOfSegments
    double trapezoidBase = (rightExtreme - leftExtreme) / numberOfSegments;
    //for all the numberOfSegments
    for (int i = 0; i < numberOfSegments; i++) {
        //determine the position of the bottom-left vertex of the trapezoid
        double bottomLeftVertex = leftExtreme + (trapezoidBase * i);
        //determine the position of the bottom-right verted of the trapezoid
        double bottomRightVertex = leftExtreme + (trapezoidBase * (i + 1));
        //determine the area with the forumala: ((small base + big base)*height)/2
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
    //declare a variable sum for containg the sum of the areas of the parabola
    double sum = 0.0;
    //determine the segmentLenght base subdividing the leght of the interval for the desired numberOfSegments
    double segmentLeght = (rightExtreme - leftExtreme) / numberOfSegments;
    bool even = false;
    double point = leftExtreme;
    //for all the numberOfSegments
    for (int i = 1; i < numberOfSegments / 2; i++) {
        double point1 = leftExtreme + segmentLeght * ((2 * i) - 2);
        double point2 = leftExtreme + segmentLeght * ((2 * i) - 1);
        double point3 = leftExtreme + segmentLeght * ((2 * i));
        sum += functionToIntegrate(point1) + 4 * functionToIntegrate(point2) + functionToIntegrate(point3);
    }
    sum = sum * (segmentLeght / 3);
    return sum;
}