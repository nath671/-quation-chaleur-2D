#include <iostream>
#include "Air.h"

using namespace std;

Air::Air()
{
    v0 = 0;
    vx = 0;
    vy = 0;
}
Air::Air(double v_0, double **VX, double **VY, Domaine2D D)
{
    v0 = v_0;
    vx = VX;
    vy = VY;
    d = D;
}

double **Air::vitesses(Domaine2D d, Mur *m, Fenetre *f, Radiateur *r)
{
    double **tab_v0 = new double *[d.get_Ny()];
    double x, y;
    bool est_dans_mur;

    // remplissage des constantes pour chaque points de l'espace (nulle dans les murs et non nul dans la piece)
    // non nul egalement dans les fenetres
    for (int j = 0; j <= d.get_Ny(); j++)
    {
        tab_v0[j] = new double[d.get_Nx()];

        for (int i = 0; i <= d.get_Nx(); i++)
        {
            x = d.get_xmin() + i * d.get_dx();
            y = d.get_ymin() + j * d.get_dy();

            est_dans_mur = false;

            for (int k = 0; k < m->get_nb_murs(); k++)
            {
                // mur ?
                if (x >= m[k].get_xmin() and x <= m[k].get_xmax() and
                    y >= m[k].get_ymin() and y <= m[k].get_ymax())
                {
                    tab_v0[j][i] = 0;

                    est_dans_mur = true;

                    break;
                }
            }
            if (est_dans_mur == false)
            {
                tab_v0[j][i] = v0;
            }

            for (int k = 0; k < f->get_nb_fenetre(); k++)
            {
                // fenetre ?
                if (x >= f[k].get_xmin() and x <= f[k].get_xmax() and
                    y >= f[k].get_ymin() and y <= f[k].get_ymax() and f[k].get_bool() == true)
                {
                    tab_v0[j][i] = v0;
                }
            }

            // si aucune fenetre n'est ouverte alors pas de vitesse dans la piece
            if (f[0].get_bool() == false and f[1].get_bool() == false)
            {
                tab_v0[j][i] = 0;
            }
        }
    }

    // calcul des vitesses
    for (int j = 0; j <= d.get_Ny(); j++)
    {
        vx[j] = new double[d.get_Nx()];
        vy[j] = new double[d.get_Nx()];

        for (int i = 0; i <= d.get_Nx(); i++)
        {
            x = d.get_xmin() + i * d.get_dx();
            y = d.get_ymin() + j * d.get_dy();

            vx[j][i] = tab_v0[j][i]; // flux laminaire constant vers la droite
            vy[j][i] = tab_v0[j][i];

            // vx[j][i] = -tab_v0[j][i] / 2 * (x - 3.5);
            // vy[j][i] = tab_v0[j][i] / 2 * (y - 1.5);
        }
    }

    for (int j = 0; j <= d.get_Ny(); j++)
    {
        delete[] tab_v0[j];
    }
    delete[] tab_v0;

    return vx, vy;
}