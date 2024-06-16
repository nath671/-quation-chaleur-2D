#ifndef Piece_h
#define Piece_h
#include <iostream>
#include "Domaine2D.h"
#include "Mur.h"
#include "Radiateur.h"
#include "Fenetre.h"

using namespace std;

// ========================= CLASSE PIECE =======================================
class Piece
{
private:
    double **tab_C;
    double **tab_D;
    double **tab_W;
    Mur *murs;         // tableau contenant les murs
    Radiateur *rad;    // tableau contenant les radiateurs
    Fenetre *fenetres; // tableau contenant les fenetres
    Domaine2D d;

public:
    Piece(double **, double **, double **, Mur *, Radiateur *, Fenetre *, Domaine2D);
    Piece();

    double **get_tab_C() { return tab_C; };
    double **get_tab_D() { return tab_D; };
    double **get_tab_W() { return tab_W; };

    double **Amenagement(double, double, Domaine2D);
};
#endif