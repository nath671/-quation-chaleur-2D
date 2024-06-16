#ifndef Radiateur_h
#define Radiateur_h

#include <iostream>

using namespace std;

// ========================= CLASSE RADIATEUR =======================================
class Radiateur
{
private:
    double W; // quantité de chaleur délivrée
    double C_rad, D_rad;
    double xmin, xmax;
    double ymin, ymax;
    bool is_on; // indique si le radiateur est allumé (true) ou éteint (false)

    static int nb_radiateurs;

public:
    Radiateur(double, double, double, double, double, double, double, bool);
    ~Radiateur();
    Radiateur();

    double get_W() { return W; };
    double get_D() { return D_rad; };
    double get_C() { return C_rad; };
    double get_xmin() { return xmin; };
    double get_xmax() { return xmax; };
    double get_ymin() { return ymin; };
    double get_ymax() { return ymax; };
    double get_nb_rad() { return nb_radiateurs; };
    bool get_bool() { return is_on; };
};
#endif