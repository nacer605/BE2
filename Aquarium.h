#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_
#include <vector>


#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


class Milieu;
class BestioleFactory;


class Aquarium : public CImgDisplay
{

private :
   Milieu       * flotte;

   int            delay;

public :
   Aquarium( int width, int height, int _delay );
   ~Aquarium( void );

   Milieu & getMilieu( void ) { return *flotte; }
   void genererFichierMetriques(const std::vector<int>& vecteur_nbBestioles)  ;

   void run(BestioleFactory* factory,std::vector<int> vecteur_nbBestioles);

};


#endif
