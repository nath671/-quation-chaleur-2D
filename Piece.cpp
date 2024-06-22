#include <iostream>
#include "Piece.h"

using namespace std;

Piece::Piece(double **C, double **D, double **W, Mur *mur, Radiateur *r, Fenetre *f, Domaine2D domaine)
{
    tab_C = C;
    tab_D = D;
    tab_W = W;
    murs = mur;
    rad = r;
    fenetres = f;
    d = domaine;
}
Piece::Piece()
{
    tab_C = 0;
    tab_D = 0;
    tab_W = 0;
    murs = 0;
    rad = 0;
    fenetres = 0;
}

// l'aménagement de la piece se fait via la définition des constantes K, rho, C et W pour chaque
// carrés de discrétisation de la piece
double **Piece::Amenagement(double C_air, double D_air, Domaine2D d)
{
    double x, y;
    bool mur_present = false;
    bool radiateur_present = false;
    bool fenetres_presente = false;

    for (int j = 0; j <= d.get_Ny(); j++) // definit les constantes K, rho et C pour chaque points du domaine
    {
        tab_C[j] = new double[d.get_Nx()];
        tab_D[j] = new double[d.get_Nx()];
        tab_W[j] = new double[d.get_Nx()];

        for (int i = 0; i <= d.get_Nx(); i++)
        {
            x = d.get_xmin() + i * d.get_dx();
            y = d.get_ymin() + j * d.get_dy();

            for (int k = 0; k < murs->get_nb_murs(); k++)
            {
                // est ce que on est dans un des murs ?
                if (x >= murs[k].get_xmin() && x <= murs[k].get_xmax() &&
                    y >= murs[k].get_ymin() && y <= murs[k].get_ymax())
                {
                    tab_C[j][i] = murs[k].get_C();
                    tab_D[j][i] = murs[k].get_D();
                    tab_W[j][i] = 0;

                    mur_present = true;

                    break; // arrete la boucle sinon ca prend que en compte le mur 4
                }
                else
                {
                    mur_present = false;
                }
            }
            if (mur_present == false)
            {
                tab_C[j][i] = C_air;
                tab_D[j][i] = D_air;
                tab_W[j][i] = 0;
            }
            for (int k = 0; k < fenetres->get_nb_fenetre(); k++)
            {
                // est ce que on est dans une fenetre ?
                if (x >= fenetres[k].get_xmin() && x <= fenetres[k].get_xmax() &&
                    y >= fenetres[k].get_ymin() && y <= fenetres[k].get_ymax() &&
                    fenetres[k].get_bool() == true)
                {
                    tab_C[j][i] = fenetres[k].get_C();
                    tab_D[j][i] = fenetres[k].get_D();
                    tab_W[j][i] = 0;

                    fenetres_presente = true;

                    break;
                }
                else
                {
                    fenetres_presente = false;
                }
            }
            for (int p = 0; p < rad->get_nb_rad(); p++)
            {
                // est ce qu'on est dans un radiateur ?
                if (x >= rad[p].get_xmin() && x <= rad[p].get_xmax() &&
                    y >= rad[p].get_ymin() && y <= rad[p].get_ymax() &&
                    rad[p].get_bool() == true)
                {
                    tab_W[j][i] = rad[p].get_W();
                    tab_C[j][i] = rad[p].get_C();
                    tab_D[j][i] = rad[p].get_D();

                    radiateur_present = true;

                    break;
                }
                else
                {
                    radiateur_present = false;
                }
            }
            if (radiateur_present == false)
            {
                tab_W[j][i] = 0;
            }
        }
    }

    return tab_C, tab_D, tab_W;
}
