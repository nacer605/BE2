#ifndef BESTIOLENAGEOIRE_H
#define BESTIOLENAGEOIRE_H

#include "Accessoires.h"

class BestioleNageoire : public Accessoire {
private:
    double boost; 
    Bestiole& Owner; 

public:
    BestioleNageoire(Bestiole& owner);

    void setParam();
};

#endif // BESTIOLENAGEOIRE_H
