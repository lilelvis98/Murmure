#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <fstream>
#include <string>

#include "Salle.h"
#include "ZoneGen.h"
#include "Zone.h"
#include "Perso.h"
#include "Modele.h"
#include "ModeleSalle.h"

class Fichier
{
private:
    std::string chemin;
    std::string index_file;

    void creation_index(std::string dir_name, std::ofstream& index);
    //std::string file_only(char  * file);
public:

    Fichier();

    void creation_index();

    void charger(Salle & s);

    void charger(ZoneGen & z);

    void charger(Zone & z);

    void charger(Perso & p);

    void charger(Modele & m, std::string nom);

    void charger(ModeleSalle & m, std::string nom);
};

#endif // FICHIER_H_INCLUDED
