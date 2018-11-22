#ifndef PARTYMANAGERMAINWINDOW_H
#define PARTYMANAGERMAINWINDOW_H

#include <QMainWindow>

class PartyManagerMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PartyManagerMainWindow(QString styleSheet_);
    ~PartyManagerMainWindow();

    /*!
     * \brief setTheme : affecte le stylesheet_ à la fenêtre.
     * \param styleSheet_
     */
    void setTheme(QString styleSheet_);

signals:
    /*!
     * \brief changerThemeRequested : demande le changement du thème.
     */
    void changerThemeRequested();

public slots:

private:

    /*!
     * \brief initToolBar : Initialise la barre d'outils.
     */
    void initToolBar();

    /*!
     * \brief initCentralWidget : Initialise le widget central.
     */
    void initCentralWidget();

    /*!
     * \brief initDockWidgets : Initialise les DockWidgets (liste de sorts et liste personnalisée).
     */
    void initDockWidgets();

    /*!
     * \brief initConnections : Initialise les connections (SIGNAL and SLOT).
     */
    void initConnections();

    QTabWidget* _centralWidget;
};

#endif // PARTYMANAGERMAINWINDOW_H
