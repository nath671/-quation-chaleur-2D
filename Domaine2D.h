#ifndef Domaine2D_h
#define Domaine2D_h

#include <iostream>

using namespace std;

// ========================= CLASSE DOMAINE 2D ===============================================
class Domaine2D
{
private:
    double x_min, x_max;
    double y_min, y_max;
    int N_x;   // nombre total de carreaux qui discrétisent le domaine selon x
    double dx; // pas ou taille d'un petit carreau selon x [ dx = (x_max - x_min) / N_x ] selon x
    int N_y;   // pareil selon y
    double dy;

public:
    // constructeurs
    Domaine2D(double, double, double, double, double, double, double, double);
    Domaine2D();

    // geteurs
    double get_xmin() { return x_min; };
    double get_xmax() { return x_max; };
    double get_ymin() { return y_min; };
    double get_ymax() { return y_max; };
    int get_Nx() { return N_x; };
    int get_Ny() { return N_y; };
    double get_dx() { return dx; };
    double get_dy() { return dy; };
};
#endif