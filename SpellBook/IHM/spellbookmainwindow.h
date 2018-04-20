#ifndef SPELLBOOKMAINWINDOW_H
#define SPELLBOOKMAINWINDOW_H

#include <QMainWindow>

class SpellBookMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SpellBookMainWindow(QString styleSheet_);

    void setTheme(QString styleSheet_);

signals:

public slots:

private:
    void initToolBar();

    void initAllWidgets();

    void initAllConnections();
};

#endif // SPELLBOOKMAINWINDOW_H
