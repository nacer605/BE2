#ifndef BESTIOLE_H
#define BESTIOLE_H

#include "UImg.h"
#include "Capteur.h"
#include "IComportement.h"


#include <iostream>

using namespace std;

class Milieu;
class Capteur;
class IComportement;

class Bestiole {
    private :
    static const double     AFF_SIZE;
    static const double     MAX_VITESSE;
    static const double     LIMITE_VUE;

private:
    int id;
    double vitesse;
    double position_x;
    double position_y;
    double orientation;
    double taille;
    int age;
    int age_limite;
    bool estVivant;
    double resistance;
    double detectabilite;
    bool yeux ;
    bool oreille ;
    bool nageoire ;
    bool carapace ;
    bool camouflage ;

    std::vector<Capteur*> Capteurs; //premier élément : Yeux, deuxième : Oreilles

    double            cumulX, cumulY;

    T               * couleur;

    IComportement* icomportement;
    int num_comportement;


public:
    //Bestiole();
    Bestiole(int id, double v, double x, double y, double o, double t, int a_lim, double res, bool yeux, bool oreille, bool nageoire, bool carapace, bool camouflage , int comportement);
    Bestiole( const Bestiole & b );
    
    ~Bestiole();
    bool getVivant() const;
    void viellir();    
    Bestiole* clonage();  
    void Bouge(int larg_max,int longueur_max);     
    void Percussion(Bestiole* autre);
    double get_x() const;
    double get_y() const;
    double getOrientation() const;
    double getVitesse() const;
    void setOrientation(double o);
    void setVitesse(double v);
    void setDetectabilite(double phi);
    void setResistance(double res);
    int getId();
    void executeComportement(Milieu& monMilieu);
    int get_num_comportement();


    std::vector<bool> Detection(Milieu& monMilieu);


    void action( Milieu & monMilieu );
    void draw( UImg & support );
  
};

#endif // 
