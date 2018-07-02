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

    KiTechniqueFrequency freq() const;
    void setFreq(const KiTechniqueFrequency &freq);

    KiTechniqueType type() const;
    void setType(const KiTechniqueType &type);

    bool combinable() const;
    void setCombinable(bool combinable);

    MaintenanceType maintenanceType() const;
    void setMaintenanceType(const MaintenanceType &maintenanceType);

    KiEffect effetP() const;
    void setEffetP(const KiEffect &effetP);

    QList<KiEffect> effetsS() const;
    void setEffetsS(const QList<KiEffect> &effetsS);

    void addEffetS(const KiEffect &effetS_);
    void removeEffetS(const int &index_);

    QMap<CaracKi, int> kiCost() const;
    void setKiCost(const QMap<CaracKi, int> &kiCost);

    QMap<CaracKi, int> kiExtraCost() const;
    void setKiExtraCost(const QMap<CaracKi, int> &kiExtraCost);

    ReductionType reductionType() const;
    void setReductionType(const ReductionType &reductionType);

    QMap<CaracKi, int> kiRed() const;
    void setKiRed(const QMap<CaracKi, int> &kiRed);

signals:
    void effectSecAsChanged();

public slots:

private:
    int _level;
    int _di;
    KiTechniqueFrequency _freq;
    KiTechniqueType _type;
    bool _combinable;
    MaintenanceType _maintenanceType;

    KiEffect _effetP;
    QList<KiEffect> _effetsS;

    QMap<CaracKi,int> _kiCost;
    QMap<CaracKi,int> _kiExtraCost;

    ReductionType _reductionType;
    QMap<CaracKi, int> _kiRed;
};

#endif // KITECHNIQUE_H
