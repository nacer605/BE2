#pragma once
#include "IComportement.h"
#include "Bestiole.h"
#include "Milieu.h"

class Prevoyant : public IComportement {
public:
    Prevoyant();
    ~Prevoyant();

    void Deplacer(Bestiole & b, Milieu & env) override ;
};
