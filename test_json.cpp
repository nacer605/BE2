#include <iostream>
#include <fstream>
#include "json.hpp"  // Inclure le fichier json.hpp téléchargé

using json = nlohmann::json;  // Utiliser l'alias json

int main() {
    // Ouvrir le fichier JSON
    std::ifstream inputFile("param.json");

    // Vérifier si le fichier s'est ouvert correctement
    if (!inputFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier!" << std::endl;
        return 1;
    }

    // Lire et analyser le fichier JSON
    json j;
    inputFile >> j;

    // Accéder aux valeurs dans le fichier JSON
    std::string name = j["name"];
    double version = j["version"];
    bool enabled = j["enabled"];
    int width = j["parameters"]["width"];
    int height = j["parameters"]["height"];

    // Afficher les valeurs
    std::cout << "Name: " << name << std::endl;
    std::cout << "Version: " << version << std::endl;
    std::cout << "Enabled: " << enabled << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    return 0;
}