#ifndef BESTIOLECARAPACE_H
#define BESTIOLECARAPACE_H

#include "Accessoires.h"

class BestioleCarapace : public Accessoire {
private:
    Bestiole& Owner; 
    double eta;    
    double omega;    
public:
    BestioleCarapace(Bestiole& bestiole);

    void setParam();
};

#endif 
