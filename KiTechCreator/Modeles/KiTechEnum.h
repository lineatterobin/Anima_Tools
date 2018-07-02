#ifndef KITECHENUM_H
#define KITECHENUM_H

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

enum class MaintenanceType {
   AUCUN,
   MAINTIEN,
   SOUTIEN
};

enum class ReductionType {
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
