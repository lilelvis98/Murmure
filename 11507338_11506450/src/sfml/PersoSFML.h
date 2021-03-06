#ifndef PERSOSFML_H_INCLUDED
#define PERSOSFML_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Perso.h"
#include "Coord2D.h"
#include "VecteurM.h"

class PersoSFML
{
private:
    sf::Sprite persosfml;

    Perso * perso;
public:
    PersoSFML();

    void charge_perso(Perso * p,const sf::Texture & texture, const int &taille_case);

    void mettre_a_jour(const float &taille_case, const int &x0, const int &y0);

    sf::Sprite get_persosfml();

    sf::Sprite * get_persosfml_ptr();

    Perso * get_perso_ptr();

    VecteurM get_taille()const;

    Coord2D get_position_hg()const;
};

#endif // PERSOSFML_H_INCLUDED
