#ifndef ACCESSOIRE_H
#define ACCESSOIRE_H

// Déclaration anticipée de la classe Bestiole (définie ailleurs)
class Bestiole;

class Accessoire {
public:
    virtual ~Accessoire() {}
    // Pour BestioleCamouflage, seul le premier paramètre sera utilisé.
    // Pour BestioleCarapace, le premier représente η et le second ω.
    virtual void setParam() = 0;
};

#endif // ACCESSOIRE_H
