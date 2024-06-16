#include <iostream>
#include "Mur.h"

using namespace std;

int Mur::nb_murs = 0;

Mur::Mur(double C, double D, double x_min, double x_max, double y_min, double y_max)
{
    C_mur = C;
    D_mur = D;
    xmin = x_min;
    xmax = x_max;
    ymin = y_min;
    ymax = y_max;
    nb_murs++;
}
Mur::Mur()
{
    C_mur = 0;
    D_mur = 0;
    xmin = 0;
    xmax = 0;
    ymin = 0;
    ymax = 0;
}
Mur::~Mur()
{
    nb_murs--;
}