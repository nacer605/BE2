#include "Bestiole.h"


#include "Milieu.h"

#include "Capteur.h"
#include "gregaire.h"
#include "Kamikaze.h"
#include "Peureuse.h"
#include "prevoyant.h"
#include "Multiple.h"

#include "BestioleYeux.h"
#include "BestioleOreille.h"

#include "BestioleNageoire.h"
#include "BestioleCamouflage.h"
#include "BestioleCarapace.h"

#include <cstdlib>
#include <cmath>
#include <vector>


const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;

#include <cmath>
#include <iostream>



Bestiole::Bestiole(int id, double v, double x, double y, double o, double t, int a_lim, double res, bool yeux, bool oreille, bool nageoire, bool carapace, bool camouflage, int comportement)
: id(id), vitesse(v), position_x(x), position_y(y), orientation(o), taille(t), age(0), 
age_limite(a_lim), estVivant(true), resistance(res), detectabilite(0), 
yeux(yeux), oreille(oreille), nageoire(nageoire), carapace(carapace), camouflage(camouflage),
Capteurs(),cumulX(0), cumulY(0), couleur(new T[3]), icomportement(nullptr),num_comportement(comportement)
{
    if (comportement == 0) {  // Grégaire
        couleur[0] = 0; couleur[1] = 255; couleur[2] = 0; // vert
        icomportement = new Gregaire() ;
    }
    else if (comportement == 1) {  // Kamikaze
        couleur[0] = 255; couleur[1] = 0; couleur[2] = 0; // rouge
        icomportement = new Kamikaze();
    }

    else if (comportement == 2) {  // Peureuse
        couleur[0] = 255; couleur[1] = 255; couleur[2] = 0; // jaune
        icomportement = new Peureuse(); 

    }
    else if (comportement == 3) {  // Prévoyante
        couleur[0] = 0; couleur[1] = 0; couleur[2] = 255; // bleu
        icomportement = new Prevoyant() ;

    }
    else if (comportement == 4) {  // Multiple
        couleur[0] = 128; couleur[1] = 0; couleur[2] = 128; // violet
        icomportement = new Multiple();
    }
    else {  // Comportement inconnu → couleur aléatoire
        couleur[0] = rand() % 230;
        couleur[1] = rand() % 230;
        couleur[2] = rand() % 230;
    }
    Capteurs = std::vector<Capteur*>();  // initialise ton attribut, pas une variable locale
    if (Bestiole::yeux) {
        Capteurs.push_back(new BestioleYeux(*this));
    }
    if (Bestiole::oreille) {
        Capteurs.push_back(new BestioleOreille(*this));
    }
    if (nageoire) {
        BestioleNageoire tempNageoire(*this);  // Objet temporaire
        tempNageoire.setParam();  
    }
    if (carapace) {
        BestioleCarapace tempCarapace(*this);  // Objet temporaire
        tempCarapace.setParam(); 
    }
    if (camouflage) {
        BestioleCamouflage tempCamouflage(*this);  // Objet temporaire
        tempCamouflage.setParam();  
    }
}

// Destructeur
Bestiole::~Bestiole()
{
    cout << "dest Bestiole (" << id << ")" << endl;
    if (couleur != nullptr) {
        delete[] couleur;
    }
    for (auto capt : Capteurs) {
        if (capt != nullptr)
            delete capt;
    }
    if (icomportement != nullptr) {
        delete icomportement;
    }
}

// Constructeur par copie
Bestiole::Bestiole( const Bestiole & b )
{
    cout << "const Bestiole (" << id << ") par copie" << endl;
    id = b.id;
    //position et vitesse
    position_x = b.position_x;
    position_y = b.position_y;
    cumulX = cumulY = 0.;
    orientation = b.orientation;
    vitesse = b.vitesse;
    //états de la bestiole
    taille = b.taille;
    resistance = b.resistance;
    detectabilite = b.detectabilite;
    age = b.age;
    estVivant = b.estVivant;
    //accessoire 
    nageoire = b.nageoire;
    carapace = b.carapace;
    camouflage = b.camouflage;
    //capteurs
    Capteurs = b.Capteurs;
    //comportement
    icomportement = b.icomportement;
    num_comportement = b.num_comportement;

    couleur = new T[ 3 ];
    memcpy( couleur, b.couleur, 3*sizeof(T) );
}

void Bestiole::viellir() {
    age++;
}

bool Bestiole::getVivant() const {
    if (age >= age_limite ) {
        cout << "Bestiole #" << id << " est morte par âge" << endl;
        return false;
    }
    else if (resistance <= 0) {
        cout << "Bestiole #" << id << " est morte par collision" << endl;
        return false;
    }
    else {
        return true;
    }
}

Bestiole* Bestiole::clonage() {
    return new Bestiole(*this);
}

void Bestiole::Bouge( int xLim, int yLim )
{

   double         nx, ny;
   double         dx = cos(orientation)*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;


   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = position_x + dx + cx;
   ny = position_y + dy + cy;

   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      position_x = static_cast<int>( nx );
      cumulX += nx - position_x;
   }

   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      position_y = static_cast<int>( ny );
      cumulY += ny - position_y;
   }

}

void Bestiole::Percussion(Bestiole* autre) {
    if (std::abs(position_x - autre->position_x) < 1 &&
        std::abs(position_y - autre->position_y) < 1) {

        std::cout << " Collision détectée entre Bestiole #" << id
                  << " et Bestiole " << autre->id << std::endl;

        // réduction de résistance
        resistance -= 10;
        autre->resistance -= 10;
    }
}

double Bestiole::get_x() const{
    return (*this).position_x;
}
double Bestiole::get_y() const{
    return (*this).position_y;
}
double Bestiole::getVitesse() const {
    return (*this).vitesse;
}
double Bestiole::getOrientation() const {
    return (*this).orientation;
}
void Bestiole::setOrientation(double o){
    (*this).orientation = o;
}
void Bestiole::setVitesse(double v){
    (*this).vitesse = v;
}

void Bestiole::setDetectabilite(double phi){
    (*this).detectabilite = phi;
}

void Bestiole::setResistance(double res ){
    (*this).resistance += res;
}

int Bestiole::getId(){
    return (*this).id;
}

void Bestiole::executeComportement(Milieu& monMilieu){
    icomportement->Deplacer(*this,monMilieu);
}

int Bestiole::get_num_comportement(){
    return (*this).num_comportement;
}

void Bestiole::action( Milieu& monMilieu )
{

   Bouge(monMilieu.getLargeur(), monMilieu.getLongueur());

}


void Bestiole::draw( UImg & support )
{

   double         xt = position_x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = position_y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( position_x, position_y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

}

std::vector<bool> Bestiole::Detection(Milieu& monMilieu){
    std::vector<Bestiole*> listeBestiole = monMilieu.getBestioles();
    std::vector<Capteur*> listeCapteurs = Capteurs;

    std::vector<bool> boolDetection(listeBestiole.size(),false);

    for (Capteur* capt:listeCapteurs){
        if (capt!=nullptr){
            std::vector<bool> detection = capt->detecter(monMilieu);
            for (size_t i = 0; i < boolDetection.size(); ++i) {
                if (!boolDetection[i] && detection[i]) {
                    boolDetection[i] = true;
                }
            }
        }
    }

    return boolDetection;
}
