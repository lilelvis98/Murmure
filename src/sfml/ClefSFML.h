#ifndef CLEFSFML_H_INCLUDED
#define CLEFSFML_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Clef.h"

class ClefSFML
{
private:
    sf::Sprite clefsfml;

    Clef* cle;
public:
    ClefSFML();

    void init(Clef* p_cle,const sf::Texture &p_texture, const int &taille_case);

    sf::Sprite get_clefsfml();

};

#endif // CLEFSFML_H_INCLUDED
