#ifndef PEUREUSE
#define PEUREUSE

#include "IComportement.h"
#include "Bestiole.h"
#include "Milieu.h"


class Peureuse : public IComportement {
    public :
        Peureuse();
        ~Peureuse();
        void Deplacer(Bestiole& Bestiole,Milieu& milieu) override final;
};

#endif