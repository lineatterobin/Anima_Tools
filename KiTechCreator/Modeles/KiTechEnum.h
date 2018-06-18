#ifndef KITECHENUM_H
#define KITECHENUM_H

#include <QObject>
#include <QString>

class KiTechEnum : public QObject
{
    Q_OBJECT
public:

    enum MaintenanceTypes {
       AUCUN,
       MAINTIEN,
       SOUTIEN
    }; Q_ENUM(MaintenanceTypes) typedef enum MaintenanceTypes MTypes;
};
#endif // KITECHENUM_H
