#ifndef Mur_h
#define Mur_h

#include <iostream>

using namespace std;

// ========================= CLASSE MUR ===============================================
class Mur
{
private:
    double C_mur;
    double D_mur;
    double xmin, xmax;
    double ymin, ymax;

    static int nb_murs;

public:
    Mur(double, double, double, double, double, double);
    Mur();
    ~Mur(); // destructeur

    double get_C() { return C_mur; };
    double get_D() { return D_mur; };
    double get_xmin() { return xmin; };
    double get_xmax() { return xmax; };
    double get_ymin() { return ymin; };
    double get_ymax() { return ymax; };
    double get_nb_murs() { return nb_murs; };
};
#endif