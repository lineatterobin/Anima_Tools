#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SpellBook/IHM/spellbookmainwindow.h>

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>

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
     * \brief lancerSpellBook : Lancement du module SpellBook
     */
    void lancerSpellBook();

private:

    QString _styleSheet;

    /*!
     * \brief _buttonsLayout : grille de boutons
     */
    QGridLayout *_buttonsLayout;

    QPushButton *_btnSpellBook;

    SpellBookMainWindow *_spellBookWindow;

};

#endif // MAINWINDOW_H
