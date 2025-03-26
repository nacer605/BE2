#include "BestioleOreille.h"
#include "Milieu.h"
#include "Bestiole.h"

#include <fstream>
#include "json.hpp"

using namespace std;

/*
J'initialise les attributs de la classe BestioleOreille avec un nombre aléatoire entre les bornes 
delta_min et delta_max et gamma_min et gamma_max.

*/

class Bestiole;

BestioleOreille::BestioleOreille(const Bestiole& bestiole) : owner(bestiole)
{
    std::ifstream inputFile("param.json");
    if (!inputFile.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier!" << std::endl;
        return;
    }
    nlohmann::json j;
    inputFile >> j;
    double delta_min = j["Oreille"]["delta_min"];
    double delta_max = j["Oreille"]["delta_max"];
    double gamma_min = j["Oreille"]["gamma_min"];
    double gamma_max = j["Oreille"]["gamma_max"];
    delta = (delta_max - delta_min) * ((double)rand() / RAND_MAX) + delta_min;
    gamma = (gamma_max - gamma_min) * ((double)rand() / RAND_MAX) + gamma_min;
}

std::vector<bool> BestioleOreille::detecter(const Milieu& milieu)
{
    std::vector<Bestiole*> bestioleEnv = milieu.getBestioles();
    std::vector<bool> res;
    for (int i = 0; i < milieu.getBestioles().size(); i++)
    {
        double distance = sqrt(pow(owner.get_x() - (*bestioleEnv[i]).get_x(), 2) + pow(owner.get_y()  - (*bestioleEnv[i]).get_y(), 2));
        if (distance <= delta && (double)rand() / RAND_MAX <= gamma)
        {
            res.push_back(true);
        }
        else
        {
            res.push_back(false);
        }
    }
    return res;
}