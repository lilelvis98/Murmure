#include <iostream>

#include "Jeu.h"

Jeu::Jeu()
{
    zone.generer_et_remplir(0);
}

Salle Jeu::get_salle()
{
    return zone.get_salle();
}

Zone Jeu::get_zone()
{
    return zone;
}

Perso Jeu::get_perso()
{
    return perso;
}

void Jeu::changer_perso(const std::string& n)
{
    perso.charger_perso(n);
}

void Jeu::deplacer_perso(const float& x, const float& y)
{
    perso.set_deplacement(x, y);
}

void Jeu::definir_position_perso(const float& x, const float& y)
{
    perso.set_position(x, y);
}

void Jeu::definir_orientation_perso(const VecteurM& v)
{
    perso.set_orientation(v);
}

void  Jeu::zone_changer_salle(const char& c)
{
    zone.changer_de_salle(c);
}

void Jeu::deplacer_perso_txt(char direction)
{
    perso.deplacer_txt(direction);
}

void Jeu::placer_perso_txt(int x, int y)
{
    perso.placer_txt(x, y);
}

void Jeu::ajouter_projectile_perso(const int& arme)
{
    // arme = 1 -> arme1 du perso
    switch(arme)
    {
    case 1:
        salle_actuelle.ajouter_projectile(perso.tirer_1());
        break;
    }
}

void Jeu::avancer_jeu(const float &vitesse_base)
{
    salle_actuelle.mise_a_jour_projectiles(vitesse_base);
}

std::list <Projectile *> * Jeu::retourne_projectiles()
{
    return salle_actuelle.get_projectiles();
}
