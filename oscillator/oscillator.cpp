//BSD License
//modified by Federico Bertani

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "../integrator/integrationMethods.h"


//The purpouse of this program is to make a simple application of integration mothods and test the precision of them.

/*
Immaginiamo il problema di tracciare una particella in moto circolare uniforme, circonferenza di raggio unitario.
Impostiamo il problema usando le variabili x, y e tempo. La particella, all'istante t = 0, e` nel punto (1,0).
La sua velocita` viene scritta come velocita` angolare, cioe` u = |v|/r. In questo modo abbiamo una quantita` che
non 'varia' nel tempo come v(vettore), ma che e` costante.
Usando questa notazione il moto circolare uniforme puo` essere scritto come

x = R cos(u*t) = cos(u*t)  (siccome per noi R = 1)
y = R sin(u*t) = sin(u*t)  (siccome per noi R = 1)

x' ed y', cioe` le derivate di x ed y nel tempo, si esprimono facilmente come

x' = -u * sin(u*t)
y' = u * cos(u*t)

x'' ed y'', cioe` le accelerazioni, sono altrettanto facili:

x'' = -u*u * cos(u*t) = -x
y'' = -u*u * sin(u*t) = -y

In questo problema, impostiamo le condizioni iniziali x(0), y(0), v_x(0) e v_y(0), creiamo una struttura nella quale immagazzinare
x, y, v_x e v_y, prepariamo delle funzioni che, data la struttura precedente e un intervallo dt prefissato, ci restituiscano
la struttura evoluta di quella in input e, ad ogni timestamp, scriviamo su un file questi dati intabellati (scegliete
il formato preferito, consiglio un banale file di testo a colonne per usare python/gnuplot per plottare poi i punti e vederne il comportamento)

x   y   v_x   v_y   R

(n e` il numero dello step ed R e` il raggio della circonferenza, ossia sqrt(x*x + y*y): lo scriviamo in quanto questo
e` un buon indicatore della qualita` del nostro integratore, vedremo infatti R allontanarsi dall'unita` tanto piu` velocemente
quanto piu` grande sara` il dt impostato nel problema)
*/

//angular speed
#define angularSpeed 3.14
#define numberOfSteps 1000
#define dt 0.01



//function to calculate angular speed along x at a given time
double dx_dt(const double &time) //derivata
{
    return -angularSpeed * sin(angularSpeed * time);
}

//function to calculare angular acceleration along x at a given time
double dv_x_dt(const double &time) {
    return -pow(angularSpeed, 2) * cos(angularSpeed * time);
}

//function to calculate angular speed along y at a given time
double dy_dt(const double &time) {
    return angularSpeed * cos(angularSpeed * time);
}

//function to calculate angular acceleration
double dv_y_dt(const double &time) {
    return -pow(angularSpeed, 2) * sin(angularSpeed * time);
}


typedef struct Coordinate {
    double x, y, v_x, v_y, R;
} Coordinata;


std::vector<Coordinate> euler(const Coordinate &initialCoordinate, const double u_angolare, const double deltaT,
                              const size_t nsteps) {
    //a vector for cointaing next coordinates
    std::vector<Coordinate> coordinate_evolute;
    //add the initial coordinate as first element of the vector
    coordinate_evolute.push_back(initialCoordinate);
    //declare a Coordinate variabile for cointaing data about next coordinates
    Coordinate nextCoordinate;
    //set the initial time to 0
    double time = 0;
    //get the address of the speedFunctionX into a function pointer
    double (*speedFunctionX)(const double &) = &dx_dt;
    //get the address of the speedFunctionY into a function pointer
    double (*speedFunctionY)(const double &) = &dy_dt;
    //get the address of the accellerationFunctionX into a function pointer
    double (*accellerationFunctionX)(const double &) = &dv_x_dt;
    //get the address of the accellerationFunctionY into a function pointer
    double (*accellerationFunctionY)(const double &) = dv_y_dt;
    //for each step
    for (size_t n = 1; n < nsteps; n++) {
        //calculate next time step
        double time2 = time + deltaT;
        //get the previous coordinate
        Coordinate previusCoordinate = coordinate_evolute.at(n - 1);
        //for the calculation of the next values i used an inverse formula of the Fundamental theorem of calculus
        //calculate the next coordinate x position.
        nextCoordinate.x = previusCoordinate.x + trapezoidal(time, time2, 100, speedFunctionX);
        //calculate the next coordinate y position.
        nextCoordinate.y = previusCoordinate.y + trapezoidal(time, time2, 100, speedFunctionY);
        //calculate the next coordinate x speed.
        nextCoordinate.v_x = previusCoordinate.v_x + trapezoidal(time, time2, 100, accellerationFunctionX);
        //calculate the next coordinate y speed.
        nextCoordinate.v_y = previusCoordinate.v_y + trapezoidal(time, time2, 100, accellerationFunctionY);
        //calculate the radius of the next coordinate, this is useful for examining the deviation
        nextCoordinate.R = sqrt(pow(nextCoordinate.x, 2) + pow(nextCoordinate.y, 2));
        //add the new coordinate to the vector
        coordinate_evolute.push_back(nextCoordinate);
        //advance the time
        time = time2;
    }
    //return the vector of coordinates
    return coordinate_evolute;
}


int main(void) {
    //declare an initial coordinate
    Coordinate initialCoordinate;
    //set the initial coordinate to position (1,0) with speed (0,1)
    initialCoordinate.x = 1.0;
    initialCoordinate.y = 0;
    initialCoordinate.v_x = 0;
    initialCoordinate.v_y = 1.0;
    //calculate the radius of the initial coordinate
    initialCoordinate.R = sqrt(pow(initialCoordinate.x, 2) + pow(initialCoordinate.y, 2));
    //calculate the next coordinates
    std::vector<Coordinate> coordinate_evolute = euler(initialCoordinate, angularSpeed, dt, numberOfSteps);
    //create an output stream to a file
    std::ofstream outputFile("traiettoria.txt");
    //if the file exist and is opened
    if (outputFile.is_open()) {
        //set the output in scientific notation
        outputFile.setf(std::ios_base::scientific);
        //set the decimal precision to 4
        outputFile.precision(4);
        //for each coordinate
        for (size_t i = 0; i < coordinate_evolute.size(); i++)
            //print the values of the coordinate
            outputFile <<
            coordinate_evolute[i].x << "\t" << coordinate_evolute[i].y << "\t" << coordinate_evolute[i].R
            << "\t" << coordinate_evolute[i].v_x << "\t" << coordinate_evolute[i].v_y
            << std::endl;
    }
    //close the file
    outputFile.close();
    return 0;
}


