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

int KiTechnique::kiAGI() const
{
    return _kiAGI;
}

void KiTechnique::setKiAGI(int kiAGI)
{
    _kiAGI = kiAGI;
}

int KiTechnique::kiDEX() const
{
    return _kiDEX;
}

void KiTechnique::setKiDEX(int kiDEX)
{
    _kiDEX = kiDEX;
}

int KiTechnique::kiCON() const
{
    return _kiCON;
}

void KiTechnique::setKiCON(int kiCON)
{
    _kiCON = kiCON;
}

int KiTechnique::kiFOR() const
{
    return _kiFOR;
}

void KiTechnique::setKiFOR(int kiFOR)
{
    _kiFOR = kiFOR;
}

int KiTechnique::kiPOU() const
{
    return _kiPOU;
}

void KiTechnique::setKiPOU(int kiPOU)
{
    _kiPOU = kiPOU;
}

int KiTechnique::kiWIL() const
{
    return _kiWIL;
}

void KiTechnique::setKiWIL(int kiWIL)
{
    _kiWIL = kiWIL;
}

int KiTechnique::kiExtraAGI() const
{
    return _kiExtraAGI;
}

void KiTechnique::setKiExtraAGI(int kiExtraAGI)
{
    _kiExtraAGI = kiExtraAGI;
}

int KiTechnique::kiExtraDEX() const
{
    return _kiExtraDEX;
}

void KiTechnique::setKiExtraDEX(int kiExtraDEX)
{
    _kiExtraDEX = kiExtraDEX;
}

int KiTechnique::kiExtraCON() const
{
    return _kiExtraCON;
}

void KiTechnique::setKiExtraCON(int kiExtraCON)
{
    _kiExtraCON = kiExtraCON;
}

int KiTechnique::kiExtraFOR() const
{
    return _kiExtraFOR;
}

void KiTechnique::setKiExtraFOR(int kiExtraFOR)
{
    _kiExtraFOR = kiExtraFOR;
}

int KiTechnique::kiExtraPOU() const
{
    return _kiExtraPOU;
}

void KiTechnique::setKiExtraPOU(int kiExtraPOU)
{
    _kiExtraPOU = kiExtraPOU;
}

int KiTechnique::kiExtraWIL() const
{
    return _kiExtraWIL;
}

void KiTechnique::setKiExtraWIL(int kiExtraWIL)
{
    _kiExtraWIL = kiExtraWIL;
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
}

MaintenanceType KiTechnique::maintenanceType() const
{
    return _maintenanceType;
}

void KiTechnique::setMaintenanceType(const MaintenanceType &maintenanceType)
{
    _maintenanceType = maintenanceType;
}

ReductionType KiTechnique::reductionType() const
{
    return _reductionType;
}

void KiTechnique::setReductionType(const ReductionType &reductionType)
{
    _reductionType = reductionType;
}

int KiTechnique::redAGI() const
{
    return _redAGI;
}

void KiTechnique::setRedAGI(int redAGI)
{
    _redAGI = redAGI;
}

int KiTechnique::redDEX() const
{
    return _redDEX;
}

void KiTechnique::setRedDEX(int redDEX)
{
    _redDEX = redDEX;
}

int KiTechnique::redCON() const
{
    return _redCON;
}

void KiTechnique::setRedCON(int redCON)
{
    _redCON = redCON;
}

int KiTechnique::redFOR() const
{
    return _redFOR;
}

void KiTechnique::setRedFOR(int redFOR)
{
    _redFOR = redFOR;
}

int KiTechnique::redPOU() const
{
    return _redPOU;
}

void KiTechnique::setRedPOU(int redPOU)
{
    _redPOU = redPOU;
}

int KiTechnique::redWIL() const
{
    return _redWIL;
}

void KiTechnique::setRedWIL(int redWIL)
{
    _redWIL = redWIL;
}
