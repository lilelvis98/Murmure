#include <iostream>
#include "Zone.h"
#include "SalleGen.h"

int main(int argc, char ** argv)
{
    srand(time (NULL));

    //Zone z;
    //z.zone_depuis_modele_aleatoire();

    SalleGen s_generateur(1, 0, 1, 1, 3);
    s_generateur.initialisation_gen();
    s_generateur.placer_clef();
    s_generateur.afficher_tests();

    return 0;
}

