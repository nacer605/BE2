#ifndef MULTIPLE_H
#define MULTIPLE_H

#include "IComportement.h"
#include "Bestiole.h"
#include "Milieu.h"

class Multiple : public IComportement {
public:
    // Constructeur et destructeur par défaut
    Multiple() = default;
    ~Multiple() = default;

    // Surcharge de la méthode Deplacer() de l'interface IComportement
    void Deplacer(Bestiole& bestiole, Milieu& milieu) override final;
};

#endif // MULTIPLE_H