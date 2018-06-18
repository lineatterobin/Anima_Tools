#ifndef KIEFFECT_H
#define KIEFFECT_H

#include <QObject>

class KiEffect : public QObject
{
    Q_OBJECT
public:
    explicit KiEffect(QObject *parent = nullptr);

signals:

public slots:
};

#endif // KIEFFECT_H