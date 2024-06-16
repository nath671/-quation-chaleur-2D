#ifndef EquationChaleur_h
#define EquationChaleur_h
#include <iostream>
#include "Piece.h"
#include "Air.h"
#include "Domaine2D.h"

using namespace std;

// ========================= CLASSE EQUATION DE LA CHALEUR 2D =======================================
class EquationChaleur2D
{
private:
    double T_init, T_bords;
    int N_t;   // """"nombre de temps de discrétisation""""
    double dt; // pas de temps

public:
    // constructeurs
    EquationChaleur2D(double, double, double, double);
    EquationChaleur2D();

    // autres méthodes
    double ***resoudre(double ***, Domaine2D, Piece, Air);
};
#endif