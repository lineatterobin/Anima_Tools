#ifndef KIEFFECT_H
#define KIEFFECT_H

#include <QMap>
#include <KiTechCreator/Modeles/KiTechEnum.h>

class KiEffect
{
public:
    KiEffect();

private:
    int _cost;
    int _extraCost;
    KiMaintenanceType _maintenanceType;

    CaracKi _caracPrimaire;
    QMap<CaracKi,int> _caracCoef;
    QMap<CaracKi,int> _caracCost;
    QMap<CaracKi,int> _caracExtraCost;
};

#endif // KIEFFECT_H
