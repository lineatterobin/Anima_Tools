#include "KiEffect.h"

KiEffect::KiEffect()
{

}

bool KiEffect::secondaire() const
{
    return _secondaire;
}

void KiEffect::setSecondaire(bool secondaire)
{
    _secondaire = secondaire;
}
