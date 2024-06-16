#ifndef Fenetre_h
#define Fenetre_h

#include <iostream>

using namespace std;

// ========================= CLASSE FENETRE ===============================================
class Fenetre // fenetre = trou dans le mur
{
private:
    double C_fenetre;
    double D_fenetre;
    double xmin, xmax;
    double ymin, ymax;
    bool ouverte; // indique si la fenetre est ouverte (true) ou non (false)

    static int nb_fenetre;

public:
    Fenetre(double, double, double, double, double, double, bool);
    Fenetre();
    ~Fenetre();

    double get_C() { return C_fenetre; };
    double get_D() { return D_fenetre; };
    double get_xmin() { return xmin; };
    double get_xmax() { return xmax; };
    double get_ymin() { return ymin; };
    double get_ymax() { return ymax; };
    double get_nb_fenetre() { return nb_fenetre; };
    bool get_bool() { return ouverte; };
};
#endif