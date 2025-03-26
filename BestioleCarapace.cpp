#include "BestioleCarapace.h"
#include "Bestiole.h"

#include <iostream>
#include <random>


#include <fstream>
#include "json.hpp"

BestioleCarapace::BestioleCarapace(Bestiole& bestiole) : Owner(bestiole){
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

    double omega_max = j["BestioleCarapace"]["omega_max"]; 
    double eta_max = j["BestioleCarapace"]["eta_max"]; 

    std::uniform_real_distribution<> dis1(1, eta_max);
    std::uniform_real_distribution<> dis2(1, omega_max);


    // Générer un nombre
    eta = dis1(gen);
    omega = dis2(gen);
}

void BestioleCarapace::setParam() {
    Owner.setResistance(omega);
    Owner.setVitesse(Owner.getVitesse()*eta);
}
