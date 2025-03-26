#include "BestioleCamouflage.h"
#include "Bestiole.h" 

#include <iostream>
#include <random>


#include <fstream>
#include "json.hpp"

BestioleCamouflage::BestioleCamouflage(Bestiole& bestiole) : Owner(bestiole) {
    std::random_device rd;
    std::mt19937 gen(rd()); 

    std::ifstream inputFile("param.json");
    if (!inputFile.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier!" << std::endl;
        return;
    }
    nlohmann::json j;
    inputFile >> j;

    double PSI_min = j["BestioleCamouflage"]["PSI_min"]; 
    double PSI_max = j["BestioleCamouflage"]["PSI_max"]; 

    // Distribution uniforme réelle entre 0 et 1
    std::uniform_real_distribution<> dis(PSI_min, PSI_max);

    // Générer un nombre
    phi = dis(gen);
}

void BestioleCamouflage::setParam() {
    // Mise à jour de l'attribut camouflage de la Bestiole
    Owner.setDetectabilite(phi);
}
