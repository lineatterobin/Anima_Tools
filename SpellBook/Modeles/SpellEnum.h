#ifndef SPELL_H
#define SPELL_H

#include <QObject>
#include <QString>

class Spell : public QObject
{
    Q_OBJECT
public:
    explicit Spell(QObject *parent = nullptr);
    ~Spell();

    enum Books {
        LUMIERE,
        OBSCURITE,
        CREATION,
        DESTRUCTION,
        FEU,
        EAU,
        AIR,
        TERRE,
        ESSENCE,
        ILLUSION,
        NECROMANCIE,
        ACCES_LIBRE
    }; Q_ENUM(Books)
    typedef enum Books Books;


    enum MaintenanceTypes {
        IMPOSSIBLE,
        CONTINUE,
        QUOTIDIEN
    }; Q_ENUM(MaintenanceTypes) typedef enum MaintenanceTypes MTypes;


    enum EffectTypes {
        AUTO,
        EFFET
    }; Q_ENUM(EffectTypes) typedef enum EffectTypes ETypes;


    enum ActionTypes {
        PASSIVE,
        ACTIVE
    }; Q_ENUM(ActionTypes) typedef enum ActionTypes ATypes;

};

#endif // SPELL_H
