/**
 * \file JeuSFML.crpp
 * \brief code source de JeuSFML
 * \author Quentin.V & Gary.S
 * \version 0.1
 * \date 24 avril 2017
 *
 */

#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "CaseSalle.h"
#include "Config.h"

#include "CaseSFML.h"
#include "CarteAffSFML.h"
#include "JeuSFML.h"



JeuSFML::JeuSFML()
{
    mode_jeu = 3;
    //jeu.get_zone().afficher_zone();
    // cherche les parametres de l'utilisateur (resolution)
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "Murmure",sf::Style::Fullscreen,settings);
    //window.create(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "Murmure",sf::Style::Close);
    //FPS = 100;
    //window.setMouseCursorVisible(false);
    view = window.getView();
    //temps_frame = sf::seconds((float) 1/FPS); // en seconde
    //window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(500);

    //window.setMouseCursorVisible(false);
    /////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////////

    salle_act_x = -1;
    salle_act_y = -1;
    /////////////////////////////////////////////////////////////////////////
    buffer.create(desktop.width, desktop.height);
    buffer_salle.create(desktop.width, desktop.height);
    buffer_carte.create(desktop.width, desktop.height);

    /////////////////////////////////////////////////////////////////////////
    val_max_deplacement = 100;

    /////////////////////////////////////////////////////////////////////////
    if(desktop.width/17 <desktop.height/9){scale_salle = desktop.width/17;}
    else{scale_salle = desktop.height/9;}

    posx0salle = (desktop.width -17*scale_salle)/2;
    posy0salle = 0;

    /////////////////////////////////////////////////////////////////////////
    scale_carte_largeur = desktop.width/11;
    scale_carte_hauteur = desktop.height/11;

    posx0carte = (desktop.width - 11*scale_carte_largeur)/2;
    posy0carte = (desktop.height - 11*scale_carte_hauteur)/2;
}

JeuSFML::~JeuSFML()
{
    for(std::list<ProjectileSFML *>::iterator it_sfml = projectilesfml.begin(); it_sfml != projectilesfml.end(); ++it_sfml)
    {
        delete (*it_sfml);
        it_sfml = projectilesfml.erase(it_sfml);
    }
    for(std::list<EnnemiSFML *>::iterator it_sfml = ennemisfml.begin(); it_sfml != ennemisfml.end(); ++it_sfml)
    {
        delete (*it_sfml);
        it_sfml = ennemisfml.erase(it_sfml);
    }
}

void JeuSFML::init()
{
    jeu.initialiser_jeu("Green", 10);

    textures.charger_textures_caseSFML();
    textures.charger_textures_carteAffSFML();
    textures.charger_texture_perso();
    textures.charger_texture_projectile();
    textures.charger_texture_ennemi();
    textures.charger_texture_clef();
    textures.charger_menu_principal();
    textures.charger_curseur_menu();
    //textures.charger_texture_curseur();
    init_caseSFML();
    init_persoSFML();
    init_texte();
    init_clefSFML();
    init_menuSFML();
}

void JeuSFML::init_caseSFML()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<17;j++)
        {
            casesfml[j + 17*i].init(posx0salle + j*scale_salle,
                                          posy0salle + i*scale_salle,
                                          scale_salle,
                                          scale_salle);
        }
    }
}

void JeuSFML::init_carteAffSFML()
{

}

void JeuSFML::init_projectileSFML()
{

}

void JeuSFML::init_ennemiSFML()
{

}

void JeuSFML::init_clefSFML()
{
    //clefsfml.init(jeu.retourne_clef(), textures.retourne_texture_clef(), scale_salle);
}

void JeuSFML::init_texte()
{
    police_test.loadFromFile("data/res/Font/Ubuntu-B.ttf");

    text_fps.setFont(police_test);
    text_fps.setPosition(0, 9*scale_salle);
    text_fps.setCharacterSize(24);
    text_fps.setFillColor(sf::Color::White);

    text_posx.setFont(police_test);
    text_posx.setPosition(2 * scale_salle, 9*scale_salle );
    text_posx.setCharacterSize(24);
    text_posx.setFillColor(sf::Color::White);

    text_posy.setFont(police_test);
    text_posy.setPosition(2 * scale_salle, 9*scale_salle + 24);
    text_posy.setCharacterSize(24);
    text_posy.setFillColor(sf::Color::White);

    text_mouseposx.setFont(police_test);
    text_mouseposx.setPosition(4 * scale_salle, 9*scale_salle);
    text_mouseposx.setCharacterSize(24);
    text_mouseposx.setFillColor(sf::Color::White);

    text_mouseposy.setFont(police_test);
    text_mouseposy.setPosition(4 * scale_salle, 9*scale_salle + 24);
    text_mouseposy.setCharacterSize(24);
    text_mouseposy.setFillColor(sf::Color::White);

    text_projectiles.setFont(police_test);
    text_projectiles.setPosition(7 * scale_salle, 9*scale_salle);
    text_projectiles.setCharacterSize(24);
    text_projectiles.setFillColor(sf::Color::White);

    text_ennemis.setFont(police_test);
    text_ennemis.setPosition(7 * scale_salle, 9*scale_salle + 24);
    text_ennemis.setCharacterSize(24);
    text_ennemis.setFillColor(sf::Color::White);

    text_pv.setFont(police_test);
    text_pv.setPosition(12 * scale_salle, 9*scale_salle + 24);
    text_pv.setCharacterSize(24);
    text_pv.setFillColor(sf::Color::White);

    ecran_fin.setFont(police_test);
    ecran_fin.setPosition(4 * scale_salle, 3*scale_salle + 24);
    ecran_fin.setCharacterSize(70);
    ecran_fin.setFillColor(sf::Color::White);
    ecran_fin.setString("VOUS ETES MORT, FIN DU JEU");
}

/*
void JeuSFML::init_curseur()
{
    curseur.setTexture(textures.retourne_texture_curseur());
}*/

void JeuSFML::init_persoSFML()
{
    jeu.changer_perso("Green");
    persosfml.charge_perso(jeu.retourne_perso_ptr(), textures.retourne_texture_perso(),scale_salle);
    //jeu.definir_position_perso(jeu.get_perso().get_pos_x(), jeu.get_perso().get_pos_y());
}

void JeuSFML::init_menuSFML()
{
    menusfml.init_menu(textures.retourne_texture_menu(), scale_salle);
    menusfml.init_curseur_menu(textures.retourne_texture_curseur_menu(), scale_salle);
}

void JeuSFML::SFML_boucle()
{
    clock.restart();
    timer_arme1_perso.restart();
    timer_arme2_perso.restart();
    timer_devmode_salles.restart();
    timer_acutalise_perso.restart();

    //init();
    //charger_salle();
    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::KeyPressed)
            {
                // si appuie sur "echap" -> ferme la fenetre(*it_sfml)->get_position().get_x()
                if((event.key.code == sf::Keyboard::Escape))
                {
                    window.close();
                }

                if(event.key.code == sf::Keyboard::M)
                {
                    mode_jeu = 1;
                }

                if(event.key.code == sf::Keyboard::P)
                {
                    mode_jeu = 2;
                }
            }


        }

        //
        afficher();

        window.setView(view);
        buffer.display();
        sprite_buffer.setTexture(buffer.getTexture());
        window.draw(sprite_buffer);
        //sf::Sprite sprite(buffer.getTexture());
        //static_sprite_buffer.setTexture(buffer.getTexture());
        //window.draw(sprite);
        window.display();
    }
}

void JeuSFML::afficher()
{
    switch(mode_jeu)
    {
    case 1:
        temps_frame = clock.restart();
        buffer.clear();
        window.clear();
        avancer_jeu();
        dessiner_salle();
        dessiner_clef();
        dessiner_projectiles();
        dessiner_ennemis();
        dessiner_perso();
        //dessiner_curseur();
        ecrire_texte();
        break;
    case 2:
        dessiner_carte();
        break;
    case 3:
        recupere_mouvements_menu();
        dessiner_menu();
        break;
    case 4:
        window.clear(sf::Color::Black);
        buffer.draw(ecran_fin);
        //std::cout << "kkekk" << std::endl;
        break;
    default:
        dessiner_salle();
        break;
    }
}

void JeuSFML::ecrire_texte()
{
    text_fps_stringstream.str("");
    fps_actuel = (int) 1/temps_frame.asSeconds();
    text_fps_stringstream << fps_actuel << " FPS";
    //text_fps_string = std::to_string(fps_actuel) + " FPS";
    text_fps.setString(text_fps_stringstream.str());
    buffer.draw(text_fps);
    //std::cout << text_fps_stringstream.str() << std::endl;sf::Texture *texture_carte;
    text_fps_stringstream.str("");
    text_fps_stringstream << "POS X : " << jeu.get_perso().get_pos_x();
    text_posx.setString(text_fps_stringstream.str());

    text_fps_stringstream.str("");
    text_fps_stringstream << "POS Y : " << jeu.get_perso().get_pos_y();
    text_posy.setString(text_fps_stringstream.str());

    text_fps_stringstream.str("");
    text_fps_stringstream << "POS X SOURIS : " << sf::Mouse::getPosition(window).x;
    text_mouseposx.setString(text_fps_stringstream.str());

    text_fps_stringstream.str("");
    text_fps_stringstream << "POS Y SOURIS : " << sf::Mouse::getPosition(window).y;
    text_mouseposy.setString(text_fps_stringstream.str());

    text_fps_stringstream.str("");
    text_fps_stringstream << "NB DE PROJ. : " << projectilesfml.size() << " GESTSALLE : " << jeu.retourne_projectiles()->size();
    text_projectiles.setString(text_fps_stringstream.str());

    text_fps_stringstream.str("");
    text_fps_stringstream << "NB ENNEMIS SFML: " << ennemisfml.size() << " GESTSALLE : " << jeu.retourne_ennemis()->size();
    text_ennemis.setString(text_fps_stringstream.str());

    text_fps_stringstream.str("");
    text_fps_stringstream << "PV : " << persosfml.get_perso_ptr()->get_pv_actuel() << "/" << persosfml.get_perso_ptr()->get_pv_max();
    text_pv.setString(text_fps_stringstream.str());


    buffer.draw(text_posx);
    buffer.draw(text_posy);
    buffer.draw(text_mouseposx);
    buffer.draw(text_mouseposy);
    buffer.draw(text_projectiles);
    buffer.draw(text_ennemis);
    buffer.draw(text_pv);
}


void JeuSFML::dessiner_salle()
{
    //sf::Sprite sprite(buffer.getTexture());
    buffer.draw(sprite_salle);
}


void JeuSFML::dessiner_carte()
{
    CarteAffSFML c;
    bool salle_act;
    //salle_act = ((salle_act_x == jeu.get_zone().get_salle_actuelle_x())&&(salle_act_y == jeu.get_zone().get_salle_actuelle_y()))
    sf::Texture *texture_carte;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            if((i == jeu.get_zone().get_salle_actuelle_x())&&(j == jeu.get_zone().get_salle_actuelle_y()))
            {
                salle_act = true;
            }
            else
            {
                salle_act = false;
            }
            texture_carte = &textures.retourne_texture_carteAffSFML(jeu.get_zone().get_salle(i, j).get_config(), salle_act);
            c.init(posx0carte +i*scale_carte_largeur,
                   posy0carte +j*scale_carte_hauteur,
                   scale_carte_largeur,
                   scale_carte_hauteur,
                   texture_carte->getSize().y,
                   texture_carte->getSize().x);
            buffer_carte.draw(c.get_cartesallesfml(),
                              texture_carte);
        }
    }
    buffer_carte.display();
    sprite_carte.setTexture(buffer_carte.getTexture());
    buffer.draw(sprite_carte);
}

void JeuSFML::dessiner_perso()
{
    buffer.draw(persosfml.get_persosfml());
}

void JeuSFML::dessiner_projectiles()
{
    for(std::list<ProjectileSFML *>::iterator it_sfml = projectilesfml.begin(); it_sfml != projectilesfml.end(); ++it_sfml)
    {
        buffer.draw((*it_sfml)->retourne_projectilesfml());
    }
}

void JeuSFML::dessiner_ennemis()
{
    for(std::list<EnnemiSFML *>::iterator it_sfml = ennemisfml.begin(); it_sfml != ennemisfml.end(); ++it_sfml)
    {
        if((*it_sfml)->get_ennemi()->is_vivant())
        {
            buffer.draw((*it_sfml)->get_ennemisfml());
        }
    }
}

void JeuSFML::dessiner_clef()
{
    if(persosfml.get_perso_ptr()->get_cle_boss())
    {
        buffer.draw(clefsfml.get_clefsfml());
    }
    else
    {
        if (jeu.get_salle_actuelle()->get_config() == 3)
        {
            if (jeu.retourne_clef()->get_par_terre())
            {
                buffer.draw(clefsfml.get_clefsfml());
            }
        }
    }

}

void JeuSFML::dessiner_menu()
{
    buffer.draw(menusfml.get_menusfml());
    buffer.draw(menusfml.get_curseur_menu());
}

/*
void JeuSFML::dessiner_curseur()
{
    std::cout << "loo" << std::endl;
    curseur.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    buffer.draw(curseur);
}*/

void JeuSFML::avancer_jeu()
{
    vitesse_base = (scale_salle*temps_frame.asSeconds());
    if(timer_acutalise_perso.getElapsedTime().asSeconds() >= 0)
    {
        jeu.avancer_jeu(vitesse_base,scale_salle);
        timer_acutalise_perso.restart();
    }
    recupere_mouvements();
    actualiser_perso();
    actualiser_ennemis();
    actualiser_clef();
    actualiser_projectiles();
    recupere_collisions();

    actualiser_salle();
}

void JeuSFML::actualiser_salle()
{
    if((salle_act_x != jeu.get_zone().get_salle_actuelle_x())||(salle_act_y != jeu.get_zone().get_salle_actuelle_y()))
    {
        buffer_salle.clear();
        sf::Texture *texture_salle;
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<17;j++)
            {
                texture_salle = &textures.retourne_texture_caseSFML(jeu.get_salle_actuelle()->get_case(i, j).get_type_char(),
                                                                         i,
                                                                         j);
                if(casesfml[j + 17*i].get_taille_texture() != (int) texture_salle->getSize().x)
                {
                    casesfml[j + 17*i].mettre_a_jour_taille_texture((int) texture_salle->getSize().x);
                }
                casesfml[j + 17*i].mettre_a_jour_type_case(jeu.get_salle_actuelle()->get_case(i, j).get_type_char());
                buffer_salle.draw(casesfml[j + 17*i].get_casesfml(), texture_salle);
            }
        }
        salle_act_x = jeu.get_zone().get_salle_actuelle_x();
        salle_act_y = jeu.get_zone().get_salle_actuelle_y();
        buffer_salle.display();
        sprite_salle.setTexture(buffer_salle.getTexture());
    }
}

void JeuSFML::actualiser_projectiles()
{
    std::list<Projectile *> * proj = jeu.retourne_projectiles();
    std::list<Projectile *>::iterator it_jeu;
    std::list<ProjectileSFML *>::iterator it_sfml;
    it_jeu = proj->begin();
    for(it_sfml=projectilesfml.begin(); it_sfml != projectilesfml.end(); ++it_sfml)
    {
        if(it_jeu == proj->end())
        {
            while(it_sfml != projectilesfml.end())
            {
                delete (*it_sfml);
                it_sfml = projectilesfml.erase(it_sfml);
            }
            break;
        }
        else
        {
            while((*it_jeu)->get_position() != (*it_sfml)->get_projectile()->get_position())
            {
                delete (*it_sfml);
                it_sfml = projectilesfml.erase(it_sfml);
                if(it_sfml == projectilesfml.end())
                {
                    break;
                }
            }
            if(it_sfml == projectilesfml.end())
            {
                break;
            }
            else
            {
                ++it_jeu;
            }
        }
    }
    for(std::list<Projectile *>::iterator it_jeu2 = it_jeu; it_jeu2 != proj->end(); ++it_jeu2)
    {
        ProjectileSFML *p = new ProjectileSFML();
        p->init((*it_jeu2), textures.retourne_texture_projectile((*it_jeu2)->get_id_projectile()),scale_salle);
        projectilesfml.push_back(p);
    }
    for(std::list<ProjectileSFML *>::iterator it_sfml = projectilesfml.begin(); it_sfml != projectilesfml.end(); ++it_sfml)
    {
        (*it_sfml)->mise_a_jour_position(scale_salle, posx0salle, posy0salle);
    }
}

void JeuSFML::actualiser_ennemis()
{
    std::list<Ennemi *> * ennemis = jeu.retourne_ennemis();
    std::list<Ennemi *>::iterator it_jeu;
    std::list<EnnemiSFML *>::iterator it_sfml;
    it_jeu = ennemis->begin();
    for(it_sfml=ennemisfml.begin(); it_sfml != ennemisfml.end(); ++it_sfml)
    {
        if(it_jeu == ennemis->end())
        {
            while(it_sfml != ennemisfml.end())
            {
                delete (*it_sfml);
                it_sfml = ennemisfml.erase(it_sfml);
            }
            break;
        }
        else
        {
            while((*it_jeu)->get_position() != (*it_sfml)->get_ennemi()->get_position())
            {
                delete (*it_sfml);
                it_sfml = ennemisfml.erase(it_sfml);
                if(it_sfml == ennemisfml.end())
                {
                    //std::cout << "yo le rap" << std::endl;
                    break;
                }
            }
            if(it_sfml == ennemisfml.end())
            {
                //std::cout << "OMFGGGG" << std::endl;
                break;
            }
            else
            {
                //std::cout << "plussoie" << std::endl;
                ++it_jeu;
            }
        }
    }
    for(std::list<Ennemi *>::iterator it_jeu2 = it_jeu; it_jeu2 != ennemis->end(); ++it_jeu2)
    {
        EnnemiSFML * e = new EnnemiSFML();
        e->init((*it_jeu2), textures.retourne_texture_ennemi(),scale_salle);
        //std::cout << "case x : " << (*it_jeu2)->get_case_x_apparition() << " et y : " << (*it_jeu2)->get_case_y_apparition() << std::endl;
        ennemisfml.push_back(e);
    }
    for(std::list<EnnemiSFML *>::iterator it_sfml = ennemisfml.begin(); it_sfml != ennemisfml.end(); ++it_sfml)
    {
        (*it_sfml)->mettre_a_jour_position(scale_salle, posx0salle, posy0salle);
        //std::cout << (*it_sfml)->get_ennemisfml().getPosition().x << " " << (*it_sfml)->get_ennemisfml().getPosition().y << std::endl;
    }
}

void JeuSFML::actualiser_clef()
{
    if(persosfml.get_perso_ptr()->get_cle_boss())
    {
        clefsfml.clef_possedee(scale_salle, posx0salle, posy0salle);
    }
    else
    {
        if (jeu.get_salle_actuelle()->get_config() == 3)
        {
            if (jeu.retourne_clef() != NULL)
            {
                 clefsfml.init(jeu.retourne_clef(), textures.retourne_texture_clef(), scale_salle,posx0salle, posy0salle);
            }
        }
    }

}

void JeuSFML::actualiser_perso()
{
    persosfml.mettre_a_jour(scale_salle, posx0salle, posy0salle);
}



void JeuSFML::recupere_collisions()
{
    hitboxes.perso_et_salle(&persosfml, casesfml, &jeu, scale_salle, posx0salle, posy0salle);
    hitboxes.projectiles_et_salle(&projectilesfml, casesfml);
    hitboxes.projectiles_et_ennemis(&projectilesfml, &ennemisfml);
    hitboxes.ennemis_et_salle(&ennemisfml, casesfml, scale_salle, posx0salle, posy0salle);
    hitboxes.perso_et_ennemis(&persosfml, &ennemisfml);
    if(persosfml.get_perso_ptr()->get_pv_actuel()<=0)
    {
        mode_jeu = 4;
    }
    if (jeu.get_salle_actuelle()->get_config() == 3)
    {
        hitboxes.perso_et_clef(&persosfml, &clefsfml);
    }
}

void JeuSFML::recupere_mouvements()
{
    vitesse_base_deplacement = (scale_salle*temps_frame.asSeconds()) /(val_max_deplacement/10);

    // Clavier
    // Attention l'axe Y pointe vers le bas
    float x = 0;
    float y = 0;

    if(sf::Joystick::isConnected(0))
    {
        x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        if((x >= -15)&&(x <= 15)) {x = 0;}
        y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        if((y >= -15)&&(y <= 15)) {y = 0;}
    }
    else
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {x = x - val_max_deplacement;}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {x = x + val_max_deplacement;}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {y = y - val_max_deplacement;}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {y = y + val_max_deplacement;}
    }

    x = (float) x * vitesse_base_deplacement;
    y = (float) y * vitesse_base_deplacement;
    //std::cout << x << " " << y << std::endl;
    jeu.deplacer_perso(x, y);

    x = 0;
    y = 0;

    VecteurM orientation;
    if(sf::Joystick::isConnected(0))
    {
        x = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
        if((x >= -15)&&(x <= 15)) {x = 0;}
        y = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
        if((y >= -15)&&(y <= 15)) {y = 0;}
        orientation.set_x(x);
        // Windows :
        orientation.set_y(y);
        // Linux
        //orientation.set_y(sf::Joystick::getAxisPosition(0, sf::Joystick::V));
    }
    else
    {
        sf::Vector2i souris;
        souris = sf::Mouse::getPosition(window);
        orientation.set_x(souris.x - jeu.get_perso().get_pos_x()*scale_salle/facteur);
        orientation.set_y(souris.y - jeu.get_perso().get_pos_y()*scale_salle/facteur);
    }


    jeu.definir_orientation_perso(orientation);

    if(timer_devmode_salles.getElapsedTime().asSeconds()>= 0.1)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {jeu.zone_changer_salle('g',1);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {jeu.zone_changer_salle('d',1);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {jeu.zone_changer_salle('h',1);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {jeu.zone_changer_salle('b',1);}
        timer_devmode_salles.restart();
    }


    //std::cout << "axe x : " << x << " axe y : " << y << std::endl;
    //std::cout << jeu.get_zone().get_salle_actuelle_x() << " " << jeu.get_zone().get_salle_actuelle_y() << std::endl;

    //if(timer_acutalise_perso.getElapsedTime().asSeconds() >= 1)
    //{

        //timer_acutalise_perso.restart();
    //}


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&((timer_arme1_perso.getElapsedTime().asSeconds()==0)||(timer_arme1_perso.getElapsedTime().asSeconds()>=jeu.get_perso().get_arme1()->get_cadence_tir())))
    {
        jeu.ajouter_projectile_perso(1);
        timer_arme1_perso.restart();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)&&((timer_arme2_perso.getElapsedTime().asSeconds()==0)||(timer_arme2_perso.getElapsedTime().asSeconds()>=jeu.get_perso().get_arme2()->get_cadence_tir())))
    {
        jeu.ajouter_projectile_perso(2);
        timer_arme2_perso.restart();
    }
}

void JeuSFML::recupere_mouvements_menu()
{
    char direction_mouv;
    if (timer_devmode_salles.getElapsedTime().asSeconds() >= 0.1)
    {
        if(sf::Joystick::isConnected(0))
        {
            float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            if(x <= -80) {direction_mouv = 'g';}
            else if(x >= 80) {direction_mouv = 'd';}
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
            if(y <= -80) {direction_mouv = 'b';}
            else if(y >= 80) {direction_mouv = 'h';}
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {direction_mouv = 'g';}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {direction_mouv = 'd';}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {direction_mouv = 'h';}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {direction_mouv = 'b';}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){direction_mouv = 'o';}
        }
        timer_devmode_salles.restart();
    }
    if (direction_mouv == 'o')
    {
        std::string selection = menusfml.get_selection_curseur();
        ///TODO Ajouter les autres menus
        if (selection == "jouer")
        {
            mode_jeu = 1;
        }
        else if (selection == "options")
        {
            //rien
        }
    }
    menusfml.actualiser_selection_curseur(direction_mouv, scale_salle);
}

