#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


string comportementNom(int code) {
    switch (code) {
        case 0: return "Gregaire";
        case 1: return "Kamikaze";
        case 2: return "Peureuse";
        case 3: return "Prevoyante";
        case 4: return "Multiple";
        default: return "Inconnu";
    }
}

int main() {
    srand(time(nullptr));

    int largeur = 640;
    int hauteur = 480;
    int nbBestioles = 10;

    Milieu monMilieu(largeur, hauteur);
    BestioleFactory factory;

    cout << " Création des bestioles...\n";
    for (int i = 0; i < nbBestioles; ++i) {
        Bestiole* b = factory.CreerBestiole(80, 20);
        monMilieu.AjouterBestiole(b);
    }

    cout << "\n État initial des bestioles :\n";
    const auto& bestioles = monMilieu.getBestioles();
    for (Bestiole* b : bestioles) {
        cout << " ID #" << b->getId();
        cout << " | Vivant : " << (b->getVivant() ? "Oui" : "Non");
        cout << " | Pos(x,y) : (" << b->get_x() << ", " << b->get_y() << ")";
        cout << " | Vitesse : " << b->getVitesse();
        cout << " | Orientation : " << b->getOrientation();
        cout << " | Comportement : " << comportementNom(b->get_num_comportement()) << "\n";
    }

    cout << "\n🚀 Simulation de 5 étapes...\n";

    bool cloneEffectue = false;
    bool eliminationEffectue = false;

    for (int t = 1; t <= 5; ++t) {
        cout << "Étape " << t << "...\n";
        monMilieu.Step(&factory);

        //  Élimination manuelle à l'étape 2
        if (t == 2 && !eliminationEffectue) {
            // Copie locale des pointeurs
            std::vector<Bestiole*> copie = monMilieu.getBestioles();

            for (Bestiole* b : copie) {
                if (b->getVivant()) {
                    cout << " Élimination manuelle de la bestiole #" << b->getId() << " à l'étape 2\n";
                    b->setResistance(-10000);  // Provoque sa mort au Step suivant
                    eliminationEffectue = true;
                    break;
                }
            }
        }

        // Clonage de bestiole à l'étape 3
        if (t == 3 && !cloneEffectue) {
            const auto& bestioles = monMilieu.getBestioles();
            for (Bestiole* b : bestioles) {
                if (b->getVivant()) {
                    Bestiole* clone = b->clonage();
                    monMilieu.AjouterBestiole(clone);
                    cout << "\n Clonage à l'étape 3 : bestiole #" << b->getId()
                         << " clonée → nouvelle bestiole #" << clone->getId() << "\n";
                    cloneEffectue = true;
                    break;
                }
            }
        }
    }

    cout << "\n Résultat final :\n";

    map<string, int> stats;
    for (Bestiole* b : monMilieu.getBestioles()) {
        string type = comportementNom(b->get_num_comportement());
        stats[type]++;
    }

    for (const auto& [type, count] : stats) {
        cout << " - " << type << " : " << count << " survivant(s)\n";
    }

    return 0;
}
