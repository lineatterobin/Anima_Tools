#ifndef KTCMAINWINDOW_H
#define KTCMAINWINDOW_H

#include <QMainWindow>

class KTCMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // Constrcuteur et Destructeur
    explicit KTCMainWindow(QString styleSheet_);
    ~KTCMainWindow();

    void setTheme(QString styleSheet_);

signals:
    void changerThemeRequested();

public slots:

private:

};

#endif // KTCMAINWINDOW_H
