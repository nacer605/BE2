#ifndef CAPTEUR_
#define CAPTEUR_

#include "Milieu.h"

class Milieu; 

using namespace std;

class Capteur
{
    public:
        virtual ~Capteur() {}
        virtual std::vector<bool> detecter(const Milieu& monMilieu) = 0;
};



#endif

