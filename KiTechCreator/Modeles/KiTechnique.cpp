#include "KiTechnique.h"

KiTechnique::KiTechnique()
{

}

int KiTechnique::level() const
{
    return _level;
}

void KiTechnique::setLevel(int level)
{
    _level = level;
}

int KiTechnique::di() const
{
    return _di;
}

void KiTechnique::setDi(int di)
{
    _di = di;
}

KiTechniqueFrequency KiTechnique::freq() const
{
    return _freq;
}

void KiTechnique::setFreq(const KiTechniqueFrequency &freq)
{
    _freq = freq;
}

KiTechniqueType KiTechnique::type() const
{
    return _type;
}

void KiTechnique::setType(const KiTechniqueType &type)
{
    _type = type;
}

bool KiTechnique::combinable() const
{
    return _combinable;
}

void KiTechnique::setCombinable(bool combinable)
{
    _combinable = combinable;
}

KiMaintenanceType KiTechnique::maintenanceType() const
{
    return _maintenanceType;
}

void KiTechnique::setMaintenanceType(const KiMaintenanceType &maintenanceType)
{
    _maintenanceType = maintenanceType;
}

KiEffect KiTechnique::effetP() const
{
    return _effetP;
}

void KiTechnique::setEffetP(const KiEffect &effetP)
{
    _effetP = effetP;
}

QList<KiEffect> KiTechnique::effetsS() const
{
    return _effetsS;
}

void KiTechnique::setEffetsS(const QList<KiEffect> &effetsS)
{
    _effetsS = effetsS;
    emit effectSecAsChanged();
}

void KiTechnique::addEffetS(const KiEffect &effetS_)
{
    _effetsS.append(effetS_);
    emit effectSecAsChanged();
}

void KiTechnique::removeEffetS(const int &index_)
{
    _effetsS.removeAt(index_);
    emit effectSecAsChanged();
}

QMap<CaracKi, int> KiTechnique::kiCost() const
{
    return _kiCost;
}

void KiTechnique::setKiCost(const QMap<CaracKi, int> &kiCost)
{
    _kiCost = kiCost;
}

QMap<CaracKi, int> KiTechnique::kiExtraCost() const
{
    return _kiExtraCost;
}

void KiTechnique::setKiExtraCost(const QMap<CaracKi, int> &kiExtraCost)
{
    _kiExtraCost = kiExtraCost;
}

KiReductionType KiTechnique::reductionType() const
{
    return _reductionType;
}

void KiTechnique::setReductionType(const KiReductionType &reductionType)
{
    _reductionType = reductionType;
}

QMap<CaracKi, int> KiTechnique::kiRed() const
{
    return _kiRed;
}

void KiTechnique::setKiRed(const QMap<CaracKi, int> &kiRed)
{
    _kiRed = kiRed;
}
