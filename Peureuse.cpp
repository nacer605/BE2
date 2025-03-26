#include "Peureuse.h"
#include <iostream>
#include <cmath>

#include <fstream>
#include "json.hpp"

Peureuse::Peureuse(){}

Peureuse::~Peureuse(){}


void Peureuse::Deplacer(Bestiole& B1,Milieu& milieu){
    std::vector<bool> best_detectés = B1.Detection(milieu);
    std::vector<Bestiole*> best_aq = milieu.getBestioles();

    std::ifstream inputFile("param.json");
    if (!inputFile.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier!" << std::endl;
        return;
    }
    nlohmann::json j;
    inputFile >> j;

    double seuil = j["Peureuse"]["seuil"]; 
    int nb_bestiole_proches = 0;
    double Fx = 0.0;
    double Fy = 0.0;
    for (std::size_t i = 0; i< best_detectés.size();i++){
        if (best_detectés[i]){
            if ((*best_aq[i]).getId()!=B1.getId()){
                nb_bestiole_proches++;
                double vitesse_x = std::cos((*best_aq[i]).getOrientation()) * (*best_aq[i]).getVitesse();
                double vitesse_y = std::sin((*best_aq[i]).getOrientation()) * (*best_aq[i]).getVitesse();
                Fx = Fx + vitesse_x;
                Fy = Fy + vitesse_y;
            }
        }
    }
    if (nb_bestiole_proches>0){
        Fx = Fx / nb_bestiole_proches;
        Fy = Fy / nb_bestiole_proches;
    }

    if (nb_bestiole_proches>seuil){
        if (Fx != 0 || Fy!= 0 ){
            double nouvel_angle = std::atan2(Fy,Fx);
            if (nouvel_angle+M_PI>M_PI){
                nouvel_angle-=M_PI;
            }
            else{
                nouvel_angle+=M_PI;
            }
            B1.setOrientation(nouvel_angle);
            int multiplicateur = j["Peureuse"]["multiplicateur_vit_peureuse"];
            B1.setVitesse(B1.getVitesse() * multiplicateur); 
    }
}
}
