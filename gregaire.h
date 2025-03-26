#pragma once
#include "IComportement.h"
#include "Bestiole.h"
#include "Milieu.h"

class Gregaire : public IComportement {
public:
    Gregaire();
    ~Gregaire();

    void Deplacer(Bestiole & b, Milieu & env) override;
};
