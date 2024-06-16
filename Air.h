#ifndef Air_h
#define Air_h
#include <iostream>
#include "Radiateur.h"
#include "Domaine2D.h"
#include "Mur.h"
#include "Fenetre.h"

using namespace std;

// ========================= CLASSE AIR =======================================
class Air // cette classe est uniquement déstiné à l'implémentation de la convection dans le programme
{
private:
    double v0;
    double **vx, **vy;
    Domaine2D d;

public:
    Air();
    Air(double, double **, double **, Domaine2D);

    double **get_vx() { return vx; };
    double **get_vy() { return vy; };

    double **vitesses(Domaine2D, Mur *, Fenetre *, Radiateur *);
};
#endif