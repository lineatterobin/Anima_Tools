#ifndef SPELL_H
#define SPELL_H

#include <QObject>
#include <QString>

class SpellEnum : public QObject
{
    Q_OBJECT
public:

    enum MaintenanceTypes {
        IMPOSSIBLE,
        CONTINUE,
        QUOTIDIEN
    }; Q_ENUM(MaintenanceTypes) typedef enum MaintenanceTypes MTypes;


    enum EffectTypes {
        AUTOMATIQUE,
        EFFET,
        ANIMIQUE,
        ATTAQUE,
        DEFENSE,
        DETECTION,
        EFFET_ANIMIQUE,
        ATTAQUE_ANIMIQUE
    }; Q_ENUM(EffectTypes) typedef enum EffectTypes ETypes;


    enum ActionTypes {
        PASSIVE,
        ACTIVE
    }; Q_ENUM(ActionTypes) typedef enum ActionTypes ATypes;

};

#endif // SPELL_H
