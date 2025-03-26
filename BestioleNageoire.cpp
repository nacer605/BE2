#include "BestioleNageoire.h"
#include "Bestiole.h" // La classe Bestiole est supposée être développée ailleurs

#include <iostream>
#include <random>


#include <fstream>
#include "json.hpp"

BestioleNageoire::BestioleNageoire(Bestiole& bestiole) : Owner(bestiole) {

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

    double boost_max = j["BestioleNageoire"]["boost_max"]; 

    std::uniform_real_distribution<> dis1(1, boost_max);

    boost = dis1(gen);
}

void BestioleNageoire::setParam() {
    double currentSpeed = Owner.getVitesse();
    Owner.setVitesse(currentSpeed*boost);
}

