//BSD License

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "../integrator/integrationMethods.h"


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
#define angularSpeed 6.28


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


typedef struct Coordinata {
    double x, y, v_x, v_y, R;
} Coordinata;


std::vector<Coordinata> euler(const Coordinata &coordinata, const double u_angolare, const double dt,
                              const size_t nsteps) {
    std::vector<Coordinata> coordinate_evolute;
    coordinate_evolute.push_back(coordinata);

    Coordinata coordinata_evoluta;
    double time = 0;
    double (*speedFunctionX)(const double &) = &dx_dt;
    double (*speedFunctionY)(const double &) = &dy_dt;
    double (*accellerationFunctionX)(const double &) = &dv_x_dt;
    double (*accellerationFunctionY)(const double &) = dv_y_dt;
    for (size_t n = 1; n < nsteps; n++) {
        double time2 = time + dt;
        Coordinata previusCoordinate = coordinate_evolute.at(n - 1);
        coordinata_evoluta.x = previusCoordinate.x + rectangle(time, time2, 1, speedFunctionX);
        coordinata_evoluta.y = previusCoordinate.y + rectangle(time, time2, 1, speedFunctionY);;
        coordinata_evoluta.v_x = previusCoordinate.v_x + rectangle(time, time2, 100, accellerationFunctionX);
        coordinata_evoluta.v_y = previusCoordinate.v_y + rectangle(time, time2, 100, accellerationFunctionY);
        coordinata_evoluta.R = sqrt(pow(coordinata.x, 2) + pow(coordinata.y, 2));
        coordinate_evolute.push_back(coordinata_evoluta);
        time = time2;
    }
    return coordinate_evolute;
}


int main(void) {
    Coordinata coordinata;
    size_t nsteps = 1000;
    double dt = 0.01;
    coordinata.x = 1.0;
    coordinata.y = 0;
    coordinata.v_x = 0;
    coordinata.v_y = 1.0;
    coordinata.R = sqrt(pow(coordinata.x, 2) + pow(coordinata.y, 2));

    std::vector<Coordinata> coordinate_evolute = euler(coordinata, angularSpeed, dt, nsteps);
    //create an output stream to a file
    std::ofstream outputFile("traiettoria.txt");
    if (outputFile.is_open()) {
        //set the output in scientific notation
        outputFile.setf(std::ios_base::scientific);
        //set the decimal precision to 4
        outputFile.precision(4);
        for (size_t i = 0; i < coordinate_evolute.size(); i++)
            outputFile <<
            coordinate_evolute[i].x << "\t" << coordinate_evolute[i].y << "\t" << coordinate_evolute[i].R
            << std::endl;
    }
    outputFile.close();
    return 0;
}


