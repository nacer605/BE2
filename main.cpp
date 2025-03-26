#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"

#include <cstdlib>   // rand()
#include <ctime> // pour std::time

#include <memory>
#include <iostream>

using namespace std;


int main()
{
   std::srand(std::time(nullptr)); // Initialisation de la graine avec le temps
   int nbBestioles = 50;
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
