#ifndef CLEF_H_INCLUDED
#define CLEF_H_INCLUDED

#include "Coord2D.h"

class Clef
{
private:
    char type_clef; /**< le type de clef -- pour le moment, un seul type : 'b' comme boss*/
    Coord2D position;
    bool par_terre;

    int case_x_apparition;
    int case_y_apparition;

public:
    Clef();

    Clef(int case_app_x, int case_app_y);

    void ramasser();

    int get_case_x_apparition();

    int get_case_y_apparition();

    bool get_par_terre();
};

#endif // CLEF_H_INCLUDED
