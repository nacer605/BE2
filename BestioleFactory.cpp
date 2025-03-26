#include "BestioleFactory.h"
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

#include <cstdlib>   // rand()
#include <ctime> // pour std::time
#include <iostream>
#include <random>

BestioleFactory::BestioleFactory() {
    id_counter = 0;

    std::ifstream inputFile("param.json");
    if (!inputFile.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier!" << std::endl;
        return;
    }
    nlohmann::json j;
    inputFile >> j;

    //Probabilités de comportement
    PROBA_GRÉGAIRE = j["Simulation"]["PROBA_GRÉGAIRE"];
    PROBA_KAMIKAZE = j["Simulation"]["PROBA_KAMIKAZE"];
    PROBA_PEUREUSE = j["Simulation"]["PROBA_PEUREUSE"];
    PROBA_PRÉVOYANTE = j["Simulation"]["PROBA_PRÉVOYANTE"];
    PROBA_MULTIPLE = j["Simulation"]["PROBA_MULTIPLE"];

    //Probabilités de caractéristiques
    PROBA_OREILLE = j["Simulation"]["PROBA_OREILLE"];
    PROBA_YEUX = j["Simulation"]["PROBA_YEUX"];
    PROBA_NAGEOIRE = j["Simulation"]["PROBA_NAGEOIRE"];
    PROBA_CARAPACE = j["Simulation"]["PROBA_CARAPACE"];
    PROBA_CAMOUFLAGE = j["Simulation"]["PROBA_CAMOUFLAGE"];

    //Caractéristiques
    VITESSE_MAX = j["Simulation"]["VITESSE_MAX"];
    AGE_MAX = j["Simulation"]["AGE_MAX"];
    TAILLE = j["Simulation"]["TAILLE"];
    RESISTANCE_MAX = j["Simulation"]["RESISTANCE_MAX"];
    REDUCTION_RESISTANCE = j["Simulation"]["REDUCTION_RESISTANCE"];
    std::cout<<"Factory crée"<<std::endl;
}

BestioleFactory::~BestioleFactory(){
    std::cout<<"Factory supprimé"<<std::endl;
}



Bestiole* BestioleFactory::CreerBestiole(int x_lim,int y_lim) {
    
    int comportement = 0; // 0: grégaire, 1: kamikaze, 2: peureuse, 3: prévoyante, 4: multiple

    // Calcul des probabilités cumulées
    double cumulative_prob_1 = PROBA_GRÉGAIRE;
    double cumulative_prob_2 = cumulative_prob_1 + PROBA_KAMIKAZE;
    double cumulative_prob_3 = cumulative_prob_2 + PROBA_PEUREUSE;
    double cumulative_prob_4 = cumulative_prob_3 + PROBA_PRÉVOYANTE;
    double cumulative_prob_5 = cumulative_prob_4 + PROBA_MULTIPLE;

    if (cumulative_prob_5 != 1) {
        std::cerr << "Erreur: les probabilités de comportement ne somment pas à 1" << std::endl;
        return nullptr;
    }
    // Générez un nombre aléatoire entre 0 et RAND_MAX pour les comportements
    double random_value_comp = static_cast<double>(std::rand()) / RAND_MAX;
    if (random_value_comp < cumulative_prob_1) {
        comportement = 0; // Grégaire
    } else if (random_value_comp < cumulative_prob_2) {
        comportement = 1; // Kamikaze
    } else if (random_value_comp < cumulative_prob_3) {
        comportement = 2; // Peureuse
    } else if (random_value_comp < cumulative_prob_4) {
        comportement = 3; // Prévoyante
    } 
    else {
        comportement = 4; // Multiple
    }
    bool yeux = PROBA_YEUX > static_cast<double>(std::rand()) / RAND_MAX;
    bool oreille = PROBA_OREILLE > static_cast<double>(std::rand()) / RAND_MAX;
    bool nageoire = PROBA_NAGEOIRE > static_cast<double>(std::rand()) / RAND_MAX;
    bool carapace = PROBA_CARAPACE > static_cast<double>(std::rand()) / RAND_MAX;
    bool camouflage = PROBA_CAMOUFLAGE > static_cast<double>(std::rand()) / RAND_MAX;

    int id = id_counter++;
    double vitesse = (rand() % VITESSE_MAX)+0.3; // On ne veut pas de vitesse nulle
    double x = rand() % x_lim;
    double y = rand() % y_lim;
    double orientation = (rand() % 360) * 3.14159 / 180;
    double taille = TAILLE;
    int age_limite = rand() % AGE_MAX;
    double resistance = (rand() % RESISTANCE_MAX);
    std::cout << "Création de la bestiole " << id << " avec comportement " << comportement << " et age limite "<< age_limite << std::endl;
    return new Bestiole(id ,vitesse, x, y, orientation, taille, age_limite, resistance, yeux, oreille, nageoire, carapace, camouflage ,comportement);
}
