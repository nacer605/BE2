#ifndef BESTIOLECAMOUFLAGE_H
#define BESTIOLECAMOUFLAGE_H

#include "Accessoires.h"

class BestioleCamouflage : public Accessoire {
private:
    Bestiole& Owner; // Pointeur vers la Bestiole possédant ce camouflage
    double phi;      // Capacité de camouflage (ψ)

public:
    BestioleCamouflage(Bestiole& bestiole);

    // Pour BestioleCamouflage, param1 représente φ (phi) et param2 est ignoré.
    void setParam();

};

#endif // BESTIOLECAMOUFLAGE_H
