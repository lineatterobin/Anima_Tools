#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SpellBook/IHM/spellbookmainwindow.h>
#include <PartyManager/IHM/PartyManagerMainWindow.h>

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>

enum Theme{
    JOUR,
    NUIT
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Constructeur et Destructeur
    MainWindow();
    ~MainWindow() override;

protected:
    /*!
     * \brief closeEvent
     */
    void closeEvent(QCloseEvent *) override;
    /*!
     * \brief paintEvent : Gestion redessin
     * \param e Event de redessin
     */
    void paintEvent(QPaintEvent *) override;

private slots:
    /*!
     * \brief lancerSpellBook : Lancement du module SpellBook
     */
    void lancerSpellBook();

    /*!
     * \brief lancerPartyManager : Lancement du module PartyManager
     */
    void lancerPartyManager();

    /*!
     * \brief changerTheme : Changement de thème (Jour/Nuit).
     */
    void changerTheme();

private:

    QString _styleSheet;

    Theme _theme;

    QGridLayout *_buttonsLayout;

    QPushButton *_btnSpellBook;

    QPushButton *_btnPartyManager;

    SpellBookMainWindow *_spellBookWindow;

    PartyManagerMainWindow *_partyManagerWindow;

};

#endif // MAINWINDOW_H
