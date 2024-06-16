#include <iostream>
#include "EquationChaleur2D.h"
#include "Piece.h"
#include "Air.h"


using namespace std;

EquationChaleur2D::EquationChaleur2D(double Nt, double Dt, double T_i, double T_b)
{
    N_t = Nt;
    dt = Dt;
    T_init = T_i;
    T_bords = T_b;
}
EquationChaleur2D::EquationChaleur2D()
{
    N_t = 0;
    dt = 0;
    T_init = 0;
    T_bords = 0;
}

double ***EquationChaleur2D::resoudre(double ***Temperature, Domaine2D d, Piece p, Air a)
{
    // n est l'indice correspondant au temps
    // j est l'indice correspondant à y
    // i est l'indice correspondant à x

    // ------------ création de tout les tableaux ------------- //
    for (int n = 0; n <= N_t; n++)
    {
        Temperature[n] = new double *[d.get_Ny()];

        for (int j = 0; j <= d.get_Ny(); j++)
        {
            Temperature[n][j] = new double[d.get_Nx()];
        }
    }

    // Température initiale dans la piece (à t = 0) sans les bords
    for (int j = 1; j < d.get_Ny(); j++)
    {
        for (int i = 1; i < d.get_Nx(); i++)
        {
            Temperature[0][j][i] = T_init;
        }
    }

    // conditions aux bords pour tout temps (température à l'extérieur de la pièce)
    for (int n = 0; n <= N_t; n++)
    {
        for (int i = 0; i <= d.get_Nx(); i++) // bords du bas et du haut
        {
            Temperature[n][0][i] = T_bords;
            Temperature[n][d.get_Ny()][i] = T_bords;
        }
        for (int j = 0; j <= d.get_Ny(); j++) // bords de gauche et de droite
        {
            Temperature[n][j][0] = T_bords;
            Temperature[n][j][d.get_Nx()] = T_bords;
        }
    }

    // remplissage du reste du tableau
    for (int n = 1; n <= N_t; n++)
    {
        for (int j = 1; j < d.get_Ny(); j++)
        {
            for (int i = 1; i < d.get_Nx(); i++)
            {
                Temperature[n][j][i] = Temperature[n - 1][j][i] + (dt * p.get_tab_W()[j][i]) / p.get_tab_C()[j][i] + (p.get_tab_D()[j][i] * dt) * ((Temperature[n - 1][j][i + 1] - 2 * Temperature[n - 1][j][i] + Temperature[n - 1][j][i - 1]) / (d.get_dx() * d.get_dx()) + (Temperature[n - 1][j + 1][i] - 2 * Temperature[n - 1][j][i] + Temperature[n - 1][j - 1][i]) / (d.get_dy() * d.get_dy())) -
                                       dt * (a.get_vx()[j][i] / (2 * d.get_dx()) * (Temperature[n - 1][j][i + 1] - Temperature[n - 1][j][i - 1]) + a.get_vy()[j][i] * (2 * d.get_dy()) * (Temperature[n - 1][j + 1][i] - Temperature[n - 1][j - 1][i]));
            }
        }
    }

    return Temperature;
}