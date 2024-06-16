#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "EquationChaleur2D.h"
#include "Piece.h"
#include "Air.h"
#include "Mur.h"
#include "Fenetre.h"
#include "Domaine2D.h"
#include "Radiateur.h"

using namespace std;

// ========================= FONCTION MAIN ===========================
int main()
{
    ofstream fichier1("EDP_2D.txt");

    // ------- Définition des constantes pour les différents matériaux ------- //
    // pour l'air
    double C_air = 1010.0; // J.K⁻¹.kg⁻¹   capacité thermique massique
    double K_air = 0.026;  // W.m⁻¹.K⁻¹    conduction thermique
    double rho_air = 1.3;  // kg/m³        densité massique
    // pour le béton
    double C_beton = 880.0;    // J.K⁻¹.kg⁻¹
    double K_beton = 1.5;      // W.m⁻¹.K⁻¹
    double rho_beton = 2300.0; // kg/m³
    // pour la laine de bois
    double C_laine_bois = 2000;  // J.K⁻¹.kg⁻¹
    double K_laine_bois = 0.039; // W.m⁻¹.K⁻¹
    double rho_laine_bois = 55;  // kg/m³
    // aluminium
    double C_aluminium = 888;   // J.K⁻¹.kg⁻¹
    double K_aluminium = 237;   // W.m⁻¹.K⁻¹
    double rho_aluminium = 2.7; // kg/m³

    // coefficient de diffusion (m²/s)
    double D_air = K_air / (rho_air * C_air);
    double D_laine_bois = K_laine_bois / (rho_laine_bois * C_laine_bois);
    double D_beton = K_beton / (rho_beton * C_beton);
    double D_aluminium = K_aluminium / (rho_aluminium * C_aluminium);
    // ----------------------------------------------------------------------- //

    double T_init = 15.0;   // °C
    double T_bords = 0.0;   // °C
    double dt = 10;         // s
    double t_final = 20000; // s
    int N_t = t_final / dt;
    double x, y, t;
    int saut = 10; //(utilisé plus bas dans la boucle pour afficher les résultats dans le fichier texte)
    // dans gnuplot : imax = N_t / saut

    double dx = 0.05; // en m
    double dy = 0.05;
    double xmin = 0; // dimension du domaine
    double xmax = 4;
    double ymin = 0;
    double ymax = 3;
    int N_x = xmax / dx;
    int N_y = ymax / dy;

    Domaine2D domaine(xmin, xmax, ymin, ymax, N_x, N_y, dx, dy);
    Mur mur1(C_laine_bois, D_laine_bois, 0.1, 0.5, 0.1, 2.9);   // mur de gauche
    Mur mur2(C_laine_bois, D_laine_bois, 3.5, 3.9, 0.1, 2.9);   // mur de droite
    Mur mur3(C_laine_bois, D_laine_bois, 0.5, 3.5, 2.5, 2.9);   // mur du haut
    Mur mur4(C_laine_bois, D_laine_bois, 0.5, 3.5, 0.1, 0.5);   // mur du bas
    Fenetre fenetre_gauche(C_air, D_air, 0.1, 0.5, 1, 2, true); // true = ouvert
    Fenetre fenetre_droite(C_air, D_air, 3.5, 3.9, 1, 2, true);
    Radiateur radiateur_chaud(100, C_air, D_air, 3.25, 3.45, 0.6, 1.1, true); // W, K, C, rho, xmin, xmax, ymin, ymax, bool
    Radiateur radiateur_chaud2(50, C_air, D_air, 1.25, 1.45, 0.6, 1.1, true); // true = allumé

    // création des tableaux
    double ***Temperature = new double **[N_t + 1];
    double **tab_C = new double *[domaine.get_Ny()];
    double **tab_D = new double *[domaine.get_Ny()];
    double **tab_W = new double *[domaine.get_Ny()];
    double **vx = new double *[domaine.get_Ny()];
    double **vy = new double *[domaine.get_Ny()];
    Mur *murs = new Mur[(int)mur1.get_nb_murs()];
    Radiateur *radiateurs = new Radiateur[(int)radiateur_chaud.get_nb_rad()];
    Fenetre *fenetres = new Fenetre[(int)fenetre_gauche.get_nb_fenetre()];

    // remplissage des tableaux d'objets
    murs[0] = mur1;
    murs[1] = mur2;
    murs[2] = mur3;
    murs[3] = mur4;
    radiateurs[0] = radiateur_chaud;
    radiateurs[1] = radiateur_chaud2;
    fenetres[0] = fenetre_gauche;
    fenetres[1] = fenetre_droite;

    // création de la pièce et aménagement
    Piece chambre(tab_C, tab_D, tab_W, murs, radiateurs, fenetres, domaine);
    chambre.Amenagement(C_air, D_air, domaine);

    // -------- CONVECTION -----------//
    // ne pas dépasser 0.001 pour v0 sinon les critères de stabilités ne sont plus respectés et le programme retourne des "nan" dans le fichier texte
    double v0 = 0.0004; // vitesse initiale (en m/s)
    Air air(v0, vx, vy, domaine);
    // cette méthode calcul la vitesse en chaque point de discrétisation du domaine
    air.vitesses(domaine, murs, fenetres, radiateurs);
    // --------------------------------//

    // création de l'EDP et résolution de l'EDP
    EquationChaleur2D EDP(N_t, dt, T_init, T_bords);
    EDP.resoudre(Temperature, domaine, chambre, air);

    // affichage des résultats dans un fichier texte
    for (int n = 0; n <= N_t; n += saut)
    {
        for (int j = 0; j <= domaine.get_Ny(); j++)
        {
            for (int i = 0; i <= domaine.get_Nx(); i++)
            {
                x = domaine.get_xmin() + i * domaine.get_dx();
                y = domaine.get_ymin() + j * domaine.get_dy();

                fichier1 << y << "   " << x << "   " << Temperature[n][j][i] << endl;
            }
            fichier1 << endl;
        }
        fichier1 << endl
                 << endl;
    }

    system("gnuplot animation_convection2D.gnu"); // créer un gif

    // ------------------------ libération de la mémoire ---------------------------- //
    for (int n = 0; n <= N_t; n++)
    {
        for (int j = 0; j <= domaine.get_Ny(); j++)
        {
            delete[] Temperature[n][j];
        }

        delete[] Temperature[n];
    }
    for (int j = 0; j <= domaine.get_Ny(); j++)
    {
        delete[] tab_C[j];
        delete[] tab_D[j];
        delete[] tab_W[j];
        delete[] vx[j];
        delete[] vy[j];
    }

    delete[] Temperature;
    delete[] tab_C;
    delete[] tab_D;
    delete[] tab_W;
    delete[] radiateurs;
    delete[] murs;
    delete[] fenetres;
    delete[] vx;
    delete[] vy;

    fichier1.close();

    return 0;
}