#include "gregaire.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <vector>


Gregaire::Gregaire() {}
Gregaire::~Gregaire() {}

void Gregaire::Deplacer(Bestiole & b, Milieu & env) {
    std::vector<Bestiole*> toutesB = env.getBestioles();
    std::vector<bool> bestiolesDetectables = b.Detection(env);

    double sum_x = 0.0, sum_y = 0.0;
    int count = 0;

    for (size_t i = 0; i < toutesB.size(); ++i) {
        if (!bestiolesDetectables[i] || toutesB[i] == &b) continue; 

        Bestiole* voisin = toutesB[i];

        double vitesse_x = std::cos(voisin->getOrientation()) * voisin->getVitesse();
        double vitesse_y = std::sin(voisin->getOrientation()) * voisin->getVitesse();

        sum_x += vitesse_x;
        sum_y += vitesse_y;
        ++count;
    }

    if (count > 0) {
        double moyenne_x = sum_x / count;
        double moyenne_y = sum_y / count;
        
        double nouvelleOrientation = std::atan2(moyenne_y, moyenne_x);
        b.setOrientation(nouvelleOrientation);

    }


}
