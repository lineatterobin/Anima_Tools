#ifndef PARTYMANAGERMAINWINDOW_H
#define PARTYMANAGERMAINWINDOW_H

#include <QMainWindow>

class PartyManagerMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PartyManagerMainWindow(QString styleSheet_);

signals:
    /*!
     * \brief changerThemeRequested : demande le changement du thème.
     */
    void changerThemeRequested();

public slots:
};

#endif // PARTYMANAGERMAINWINDOW_H
