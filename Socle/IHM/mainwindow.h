#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
     * \brief paintEvent : Gestion redessin
     * \param e Event de redessin
     */
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    /*!
     * \brief _buttonslayout : grille du menu
     */
    QGridLayout *_buttonslayout;

    QPushButton *_btnTest;

};

#endif // MAINWINDOW_H
