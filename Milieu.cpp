#include "Milieu.h"
#include "BestioleFactory.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

int nb_iterations = 0;
int nbrBestiolesGregaires = 0;
int nbrBestiolesGregairesMortes = 0;

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };

Milieu::Milieu(int l, int w) : UImg( l, w, 1, 3 ),longueur(w), largeur(l),bestioles(){}

Milieu::~Milieu() {
    for (auto b : bestioles) {
        delete b;
    }
}

void Milieu::AjouterBestiole(Bestiole* b) {
    bestioles.push_back(b);
}

void Milieu::eliminerBestiole(Bestiole* b) {
    auto it = std::find(bestioles.begin(), bestioles.end(), b); // Trouver l'élément
    if (it != bestioles.end()) {  // Vérifier s'il existe dans le vecteur
        bestioles.erase(it);  // Supprimer du vecteur
        delete b;  // Libérer la mémoire
    }
}

void Milieu::Update( void )
{
   for ( std::vector<Bestiole*>::iterator it = bestioles.begin() ; it != bestioles.end() ; ++it )
   {
        (*it)->viellir();
        (*it)->executeComportement(*this);
   }
}
void Milieu::Step(BestioleFactory* Factory)
{
    nb_iterations++;
    int random = 0;
    if (nb_iterations%100==0){
        random = std::rand()%2;
    }
    if (random>0){
        for (int k=0;k<=random;k++){
            Bestiole* ptr_best = Factory->CreerBestiole(640,480);
            (*this).AjouterBestiole(ptr_best);
            // get_num_comportement() est implementé pour obtenir le comportement en int  à utiliser pour plus tard
        }
    }
    cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
    for (auto it = bestioles.begin(); it != bestioles.end();) {
    if ((*it)->getVivant()) {  // Si la bestiole est vivante
        (*it)->action(*this);
        (*it)->draw(*this);
        ++it;  // On passe à l'élément suivant
    } else {
        // Supprimer la bestiole morte et ne pas incrémenter l'itérateur
        if ((*it)->get_num_comportement() == 0 && nb_iterations<200){
        }
        eliminerBestiole(*it);
        // Ne pas incrémenter it car l'élément suivant a maintenant pris la place de l'élément supprimé
    }
}
}

void Milieu::percussionBestiole()
{
    for (auto it = bestioles.begin(); it != bestioles.end(); ++it) {
        for (auto it2 = it + 1; it2 != bestioles.end(); ++it2) {
                (*it)->Percussion(*it2);
            }
        }
}

std::vector<Bestiole*> Milieu::getBestioles() const{
    return (*this).bestioles;
}

int Milieu::nbBestioles() const{
    return (*this).bestioles.size();
}
