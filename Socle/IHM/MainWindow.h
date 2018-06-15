#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SpellBook/IHM/spellbookmainwindow.h>
#include <KTC/IHM/KTCMainWindow.h>

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
    ~MainWindow();

protected:
    /*!
     * \brief closeEvent
     */
    void closeEvent(QCloseEvent *);
    /*!
     * \brief paintEvent : Gestion redessin
     * \param e Event de redessin
     */
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private slots:
    /*!
     * \brief lancerSpellBook : Lancement du module SpellBook.
     */
    void lancerSpellBook();

    /*!
     * \brief lancerKTC: Lancement du module KiTechCreator.
     */
    void lancerKTC();

    /*!
     * \brief changerTheme : Changement de thème (Jour/Nuit).
     */
    void changerTheme();

private:

    QString _styleSheet;

    Theme _theme;

    SpellBookMainWindow *_spellBookWindow;
    KTCMainWindow *_ktcMainWindow;

};

#endif // MAINWINDOW_H
