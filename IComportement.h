#ifndef ICOMP
#define ICOMP

#include "Bestiole.h"

class Bestiole;
class Milieu;


class IComportement{
    public : 
    virtual void Deplacer(Bestiole& b, Milieu& env) = 0;
    virtual ~IComportement(){};

};
#endif