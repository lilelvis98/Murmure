#include <iostream>

#include <SFML/Graphics.hpp>

#include "CaseSalle.h"

#include "CaseSFML.h"
#include "JeuSFML.h"

JeuSFML::JeuSFML()
{
    // cherche les parametres de l'utilisateur (resolution)
    desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "Murmure",sf::Style::Fullscreen);

    if(desktop.width/21 <desktop.height/15){scale = desktop.width/21;}
    else{scale = desktop.height/15;}
    //std::cout << desktop.width << " " << desktop.height << " " << desktop.bitsPerPixel << std::endl;
    posx0 = (desktop.width -21*scale)/2;
    posy0 = (desktop.height - 15*scale)/2;

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        afficher_salle();

        window.display();
    }
}

void JeuSFML::afficher_salle()
{
    CaseSalle c;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<21;j++)
        {
            c=jeu.get_salle().get_case(i,j);
            CaseSFML C(posx0 +j*scale,
                                   posy0 +i*scale,
                                   scale,
                                   scale,
                                   c.get_type_string());
            window.draw(C.get_casesfml(),C.get_states());
        }
    }
}