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

private:
    QString _name;
    int _level;
    Books _book;
    QString _description;
    int _initialCost;
    int _intermediaireCost;
    int _avanceeCost;
    int _arcaneCost;
    int _initialRequirement;
    int _intermediaireRequirement;
    int _avanceeRequirement;
    int _arcaneRequirement;
    int _initialMaintenance;
    int _intermediaireMaintenance;
    int _avanceeMaintenance;
    int _arcaneMaintenance;
    MTypes _maintenanceType;
    int _initialRMys;
    int _intermediaireRMys;
    int _avanceeRMys;
    int _arcaneRMy;
    bool _hasRMys;
    QString _commentaires;
    QString _source;
    ETypes _effectType;
    QString _initialEffect;
    QString _intermediaireEffect;
    QString _avanceeEffect;
    QString _arcaneEffect;
    ATypes _action;
};

#endif // SPELL_H
