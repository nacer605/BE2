#include "Multiple.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "prevoyant.h"
#include "gregaire.h"

#include "Bestiole.h"
#include "Milieu.h"

void Multiple::Deplacer(Bestiole& bestiole, Milieu& milieu) {
    //choisit un comportement au hazard
    int comportement = rand() % 4;
    if (comportement == 0) {
        Gregaire gregaire;
        gregaire.Deplacer(bestiole, milieu);
    } else if (comportement == 1) {
        Kamikaze kamikaze;
        kamikaze.Deplacer(bestiole, milieu);
    } else if (comportement == 2) {
        Peureuse peureuse;
        peureuse.Deplacer(bestiole, milieu);
    } else {
        Prevoyant prevoyant;
        prevoyant.Deplacer(bestiole, milieu);
    }
}