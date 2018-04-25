#ifndef SPELLBOOKMAINWINDOW_H
#define SPELLBOOKMAINWINDOW_H

#include <SpellBook/IHM/SpellView.h>

#include <QMainWindow>
#include <QToolBar>
#include <QVBoxLayout>
#include <QDockWidget>

class SpellBookMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SpellBookMainWindow(QString styleSheet_);

    ~SpellBookMainWindow();

    void setTheme(QString styleSheet_);

signals:

public slots:

private:
    void initToolBar();

    void initAllWidgets();

    void initAllConnections();

    void addSpellView();

    QTabWidget* _centralWidget;

    SpellView* _spellPreview;

};

#endif // SPELLBOOKMAINWINDOW_H
