#ifndef KITECHNIQUE_H
#define KITECHNIQUE_H

#include <QObject>

#include <KiTechCreator/Modeles/KiEffect.h>
#include <KiTechCreator/Modeles/KiTechEnum.h>

class KiTechnique : public QObject
{
    Q_OBJECT
public:
    explicit KiTechnique(QObject *parent = nullptr);

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



};

#endif // KITECHNIQUE_H
