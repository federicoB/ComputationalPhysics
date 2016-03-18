//BSD License

#include <cmath>
#include <vector>
#include <iostream>



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




//#derivata nel tempo del punto dello spazio delle fasi X(t)=[x0,x1], oscillatore armonico
double dx_dt(const double x0, const double x1) //derivata 
{
  return x1;
}


double dy_dt(const double y0, const double y1)
{
  return -y0;
}


typedef struct Coordinata {
  double x, y, v_x, v_y, R;
} Coordinata;


std::vector<Coordinata> euler(const Coordinata &coordinata, const double u_angolare, const double dt, const size_t nsteps)
{
  std::vector<Coordinata> coordinate_evolute;
  coordinate_evolute.push_back(coordinata);

  Coordinata coordinata_evoluta;

  for (size_t n = 1; n < nsteps; n++)
  {
    coordinata_evoluta.x = coordinate_evolute.at(n - 1).x + 0;
    coordinata_evoluta.y = coordinate_evolute.at(n - 1).y + 0;
    coordinata_evoluta.R = sqrt(coordinata_evoluta.x*coordinata_evoluta.x + coordinata_evoluta.y*coordinata_evoluta.y);

  }
  return coordinate_evolute;
}




int main(void)
{
  Coordinata coordinata;
  size_t nsteps = 1000;
  double dt = 0.01;
  double u = 6.28;

  coordinata.x = 1.0;
  coordinata.y = 0;
  coordinata.v_x = 0;
  coordinata.v_y = 1.0;
  coordinata.R = sqrt(coordinata.x*coordinata.x + coordinata.y*coordinata.y);

  std::vector<Coordinata> coordinate_evolute = euler(coordinata, u, dt, nsteps);

  for (size_t i = 0; i < coordinate_evolute.size(); i++)
    std::cout << coordinate_evolute[i].x << "\t" << coordinate_evolute[i].y << "\t" << coordinate_evolute[i].R << std::endl;

  return 0;
}


