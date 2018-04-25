#ifndef SPELL_H
#define SPELL_H

#include <QObject>
#include <QString>


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
    LIBRE
}; typedef enum Books Books;


enum MaintenanceTypes {
    NO,
    ROUND,
    DAYLY
}; typedef enum MaintenanceTypes MTypes;


enum EffectTypes {
    AUTO,
    EFFECT
}; typedef enum EffectTypes ETypes;


enum ActionTypes {
    PASSIVE,
    ACTIVE
}; typedef enum ActionTypes ATypes;

class Spell : public QObject
{
    Q_OBJECT
public:
    explicit Spell(QObject *parent = nullptr);

    ~Spell();

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
