#include <iostream>
#include "Fenetre.h"

using namespace std;

int Fenetre::nb_fenetre = 0;

Fenetre::Fenetre(double C, double D, double x_min, double x_max, double y_min, double y_max, bool open)
{
    C_fenetre = C;
    D_fenetre = D;
    xmin = x_min;
    xmax = x_max;
    ymin = y_min;
    ymax = y_max;
    ouverte = open;
    nb_fenetre++;
}
Fenetre::Fenetre()
{
    C_fenetre = 0;
    D_fenetre = 0;
    xmin = 0;
    xmax = 0;
    ymin = 0;
    ymax = 0;
    ouverte = 0;
}
Fenetre::~Fenetre()
{
    nb_fenetre--;
}