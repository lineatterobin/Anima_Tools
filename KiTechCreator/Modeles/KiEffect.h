#ifndef KIEFFECT_H
#define KIEFFECT_H

class KiEffect
{
public:
    KiEffect();

    bool secondaire() const;
    void setSecondaire(bool secondaire);

private:
    bool _secondaire;
};

#endif // KIEFFECT_H
