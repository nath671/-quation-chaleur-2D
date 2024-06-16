#include <iostream>
#include "Domaine2D.h"

using namespace std;

Domaine2D::Domaine2D(double xmin, double xmax, double ymin, double ymax, double Nx, double Ny, double dX, double dY)
{
    x_min = xmin;
    x_max = xmax;
    y_min = ymin;
    y_max = ymax;
    N_x = Nx;
    N_y = Ny;
    dx = dX;
    dy = dY;
}
Domaine2D::Domaine2D()
{
    x_min = 0;
    x_max = 0;
    y_min = 0;
    y_min = 0;
    N_x = 0;
    N_y = 0;
    dx = 0;
    dy = 0;
}