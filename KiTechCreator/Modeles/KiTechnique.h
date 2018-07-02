#ifndef KITECHNIQUE_H
#define KITECHNIQUE_H

#include <QObject>

#include <KiTechCreator/Modeles/KiEffect.h>
#include <KiTechCreator/Modeles/KiTechEnum.h>

class KiTechnique : public QObject
{
    Q_OBJECT
public:
    KiTechnique();

    int level() const;
    void setLevel(int level);

    int di() const;
    void setDi(int di);

    int kiAGI() const;
    void setKiAGI(int kiAGI);

    int kiDEX() const;
    void setKiDEX(int kiDEX);

    int kiCON() const;
    void setKiCON(int kiCON);

    int kiFOR() const;
    void setKiFOR(int kiFOR);

    int kiPOU() const;
    void setKiPOU(int kiPOU);

    int kiWIL() const;
    void setKiWIL(int kiWIL);

    int kiExtraAGI() const;
    void setKiExtraAGI(int kiExtraAGI);

    int kiExtraDEX() const;
    void setKiExtraDEX(int kiExtraDEX);

    int kiExtraCON() const;
    void setKiExtraCON(int kiExtraCON);

    int kiExtraFOR() const;
    void setKiExtraFOR(int kiExtraFOR);

    int kiExtraPOU() const;
    void setKiExtraPOU(int kiExtraPOU);

    int kiExtraWIL() const;
    void setKiExtraWIL(int kiExtraWIL);

    KiEffect effetP() const;
    void setEffetP(const KiEffect &effetP);

    QList<KiEffect> effetsS() const;
    void setEffetsS(const QList<KiEffect> &effetsS);

    MaintenanceType maintenanceType() const;
    void setMaintenanceType(const MaintenanceType &maintenanceType);

    ReductionType reductionType() const;
    void setReductionType(const ReductionType &reductionType);

    int redAGI() const;
    void setRedAGI(int redAGI);

    int redDEX() const;
    void setRedDEX(int redDEX);

    int redCON() const;
    void setRedCON(int redCON);

    int redFOR() const;
    void setRedFOR(int redFOR);

    int redPOU() const;
    void setRedPOU(int redPOU);

    int redWIL() const;
    void setRedWIL(int redWIL);

signals:

public slots:

private:
    int _level;
    int _di;

    int _kiAGI;
    int _kiDEX;
    int _kiCON;
    int _kiFOR;
    int _kiPOU;
    int _kiWIL;
    int _kiExtraAGI;
    int _kiExtraDEX;
    int _kiExtraCON;
    int _kiExtraFOR;
    int _kiExtraPOU;
    int _kiExtraWIL;

    KiEffect _effetP;
    QList<KiEffect> _effetsS;

    MaintenanceType _maintenanceType;
    ReductionType _reductionType;

    int _redAGI;
    int _redDEX;
    int _redCON;
    int _redFOR;
    int _redPOU;
    int _redWIL;

};

#endif // KITECHNIQUE_H
