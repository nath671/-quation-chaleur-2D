#include <iostream>
#include "Radiateur.h"

using namespace std;

int Radiateur::nb_radiateurs = 0;

Radiateur::Radiateur(double w, double C, double D, double x_min, double x_max, double y_min, double y_max, bool allume)
{
    W = w;
    C_rad = C;
    D_rad = D;
    xmin = x_min;
    xmax = x_max;
    ymin = y_min;
    ymax = y_max;
    is_on = allume;
    nb_radiateurs++;
}
Radiateur::Radiateur()
{
    W = 0;
    C_rad = 0;
    D_rad = 0;
    xmin = 0;
    xmax = 0;
    ymin = 0;
    ymax = 0;
    is_on = 0;
}
Radiateur::~Radiateur()
{
    nb_radiateurs--;
}