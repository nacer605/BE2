#include "BestioleYeux.h"
#include "Milieu.h"
#include "Bestiole.h"
#include <cmath>

#include <fstream>
#include "json.hpp"

using namespace std;

/*
J'utilise des angles en radians pour les calculs
*/

BestioleYeux::BestioleYeux(const Bestiole& bestiole) : owner(bestiole)
{
    std::ifstream inputFile("param.json");
    if (!inputFile.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier!" << std::endl;
        return;
    }
    nlohmann::json j;
    inputFile >> j;
    double alpha_min = j["Yeux"]["alpha_min"];
    double alpha_max = j["Yeux"]["alpha_max"];
    double delta_min = j["Yeux"]["delta_min"];
    double delta_max = j["Yeux"]["delta_max"];
    double gamma_min = j["Yeux"]["gamma_min"];
    double gamma_max = j["Yeux"]["gamma_max"];
    alpha = (alpha_max - alpha_min) * ((double)rand() / RAND_MAX) + alpha_min;
    delta = (delta_max - delta_min) * ((double)rand() / RAND_MAX) + delta_min;
    gamma = (gamma_max - gamma_min) * ((double)rand() / RAND_MAX) + gamma_min;
}

std::vector<bool> BestioleYeux::detecter(const Milieu& milieu)
{
    std::vector<bool> res;
    std::vector<Bestiole*> bestioleEnv = milieu.getBestioles();

    for (int i = 0; i < bestioleEnv.size(); i++)
    {
        double distance = sqrt(pow(owner.get_x() - (*bestioleEnv[i]).get_x(), 2) + pow(owner.get_y()  - (*bestioleEnv[i]).get_y(), 2));
        double angle = std::abs(owner.getOrientation() - (*bestioleEnv[i]).getOrientation());
        if (distance <= delta && angle <= alpha/2 && (double)rand() / RAND_MAX <= gamma) //alpha/2 car on prend la valeur absolue de l'angle entre les deux vecteurs vitesse
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