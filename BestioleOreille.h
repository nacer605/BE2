#ifndef BESTIOLEOREILLE_
#define BESTIOLEOREILLE_

#include "Capteur.h"
#include "Milieu.h"
#include "Bestiole.h"

using namespace std;


class BestioleOreille : public Capteur
{
    public:
        ~BestioleOreille() override = default; 
        BestioleOreille(const Bestiole& b);
        std::vector<bool> detecter(const Milieu& monMilieu) override;
    private:
        const Bestiole& owner;
        double delta;
        double gamma;
};


#endif