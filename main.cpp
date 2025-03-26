#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"

#include <cstdlib>   // rand()
#include <ctime> // pour std::time

#include <memory>
#include <iostream>

#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;


int main()
{
   std::ifstream inputFile("param.json");
    if (!inputFile.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier!" << std::endl;
        return 0;
    }
    nlohmann::json j;
    inputFile >> j;

   std::srand(std::time(nullptr)); // Initialisation de la graine avec le temps
   int nbBestioles = j["Simulation"]["nb_bestioles_in"];
   Aquarium       ecosysteme( 640, 480, 30 );
   BestioleFactory* factory = new BestioleFactory();
   std::vector<int> vecteur_bestioles_initiales(5,0);
   for ( int i = 1; i <= nbBestioles; ++i ){
      Bestiole* ptr_best = factory->CreerBestiole(640,480);
      int comportement = (*ptr_best).get_num_comportement();
      vecteur_bestioles_initiales[comportement]+= 1;
      ecosysteme.getMilieu().AjouterBestiole(ptr_best);
   }
   ecosysteme.run(factory,vecteur_bestioles_initiales);


   delete factory;
   return 0;

}
