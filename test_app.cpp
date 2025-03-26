#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>

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

struct BestioleStats {
    int totalInitial = 0;
    int survivantsInitial = 0;
    int nbClones = 0;
    int nbVivantsEtape3 = 0;
    vector<int> dureesVie;
    vector<pair<int, int>> positions;
    vector<tuple<int, int, bool, int>> details; // id, durée, vivant, dateNaissance
    set<int> idsTraites; // pour éviter doublons
};

int main() {
    srand(time(nullptr));

    int largeur = 640;
    int hauteur = 480;
    int nbBestioles = 500;
    int nbEtapes = 50;

    Milieu monMilieu(largeur, hauteur);
    BestioleFactory factory;

    map<int, BestioleStats> statsParComportement;
    map<int, int> dateNaissance;
    map<int, int> dateMort;
    map<int, int> comportementInit;

    cout << "✅ Création des bestioles...\n";
    for (int i = 0; i < nbBestioles; ++i) {
        Bestiole* b = factory.CreerBestiole(80, 20);
        monMilieu.AjouterBestiole(b);

        int c = b->get_num_comportement();
        statsParComportement[c].totalInitial++;
        dateNaissance[b->getId()] = 1;
        comportementInit[b->getId()] = c;
    }

    cout << "\n🚀 Simulation de " << nbEtapes << " étapes...\n";
    bool cloneEffectue = false;

    std::vector<int> v(5,0);

    for (int t = 1; t <= nbEtapes; ++t) {
        cout << "Étape " << t << "...\n";
        monMilieu.Step(&factory,v);

        for (Bestiole* b : monMilieu.getBestioles()) {
            int id = b->getId();

            if (b->getVivant()) {
                statsParComportement[b->get_num_comportement()].positions.push_back({b->get_x(), b->get_y()});
            }

            if (!b->getVivant() && dateMort.find(id) == dateMort.end()) {
                dateMort[id] = t;
            }
        }

        if (t == 3 && !cloneEffectue) {
            for (Bestiole* b : monMilieu.getBestioles()) {
                if (b->getVivant()) {
                    Bestiole* clone = factory.CreerBestiole(80, 20); // force nouvel ID !
                    *clone = *b; // copie attributs, mais ID différent
                    monMilieu.AjouterBestiole(clone);

                    int c = b->get_num_comportement();
                    statsParComportement[c].nbClones++;
                    statsParComportement[c].nbVivantsEtape3++;
                    dateNaissance[clone->getId()] = t;
                    comportementInit[clone->getId()] = c;

                    cout << "\n🧬 Clonage à l'étape 3 : bestiole #" << b->getId()
                         << " clonée → nouvelle bestiole #" << clone->getId() << "\n";
                    cloneEffectue = true;
                    break;
                }
            }
        }
    }

    cout << "\n📌 Calculs des statistiques :\n";
    for (const auto& b : monMilieu.getBestioles()) {
        int id = b->getId();
        int comp = comportementInit[id];
        int naissance = dateNaissance[id];
        int mort = b->getVivant() ? (nbEtapes + 1) : dateMort[id];
        int duree = mort - naissance;
        bool vivant = b->getVivant();

        if (statsParComportement[comp].idsTraites.count(id)) continue; // éviter doublons
        statsParComportement[comp].idsTraites.insert(id);

        if (naissance == 1 && vivant) {
            statsParComportement[comp].survivantsInitial++;
        }

        statsParComportement[comp].dureesVie.push_back(duree);
        statsParComportement[comp].details.push_back({id, duree, vivant, naissance});
    }

    for (const auto& [code, stat] : statsParComportement) {
        string nom = comportementNom(code);

        double tauxSurvie = stat.totalInitial ? 100.0 * stat.survivantsInitial / stat.totalInitial : 0.0;
        double dureeMoyenne = stat.dureesVie.empty() ? 0.0 :
            accumulate(stat.dureesVie.begin(), stat.dureesVie.end(), 0.0) / stat.dureesVie.size();
        double tauxClonage = stat.nbVivantsEtape3 ? 100.0 * stat.nbClones / stat.nbVivantsEtape3 : 0.0;

        double moyX = 0, moyY = 0;
        for (auto [x, y] : stat.positions) {
            moyX += x;
            moyY += y;
        }
        if (!stat.positions.empty()) {
            moyX /= stat.positions.size();
            moyY /= stat.positions.size();
        }

        cout << "\n🔎 Comportement : " << nom << "\n";
        cout << " - Taux de survie (nés à t=1) : " << tauxSurvie << "%\n";
        cout << " - Durée de vie moyenne : " << dureeMoyenne << " étapes\n";
        cout << " - Taux de clonage à l'étape 3 : " << tauxClonage << "%\n";
        cout << " - Position moyenne : (" << moyX << ", " << moyY << ")\n";

        cout << "   📋 Détails :\n";
        for (auto [id, duree, vivant, naissance] : stat.details) {
            cout << "     - ID #" << id << " : durée = " << duree << " | Vivant : " << (vivant ? "Oui" : "Non") << " | Né à t=" << naissance << "\n";
        }
    }

    return 0;
}
