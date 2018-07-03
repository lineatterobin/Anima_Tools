#ifndef KITECHENUM_H
#define KITECHENUM_H

#include <QObject>

enum class KiTechniqueFrequency {
   ACTION,
   TURN,
   MIXED
};

enum class KiTechniqueType {
    ATTAQUE,
    CONTRE_ATTAQUE,
    DEFENSE,
    VARIABLE
};

enum class KiMaintenanceType {
   AUCUN,
   MAINTIEN,
   SOUTIEN
};

enum class KiReductionType {
    AUCUNE,
    KI,
    DI
};

enum class CaracKi {
    AGI,
    DEX,
    CON,
    FOR,
    POU,
    WIL
};

#endif // KITECHENUM_H
