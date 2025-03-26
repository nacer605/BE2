#ifndef KAMIKAZE
#define KAMIKAZE

#include "IComportement.h"
#include "Bestiole.h"
#include "Milieu.h"


class Kamikaze : public IComportement {
    public :
        Kamikaze();
        ~Kamikaze();
        void Deplacer(Bestiole& Bestiole, Milieu& milieu) override final;
};

#endif