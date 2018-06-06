#ifndef SPELLBOOKMAINWINDOW_H
#define SPELLBOOKMAINWINDOW_H

#include <SpellBook/IHM/SpellView.h>
#include <SpellBook/IHM/SpellTreeView.h>

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
    SpellView *newSpellView(const bool &readOnly_);

    QList<QDockWidget*> getList();

signals:

public slots:

    void newSpellViewButton();
    void loadSpellPreview(QModelIndex index_);
    SpellView *addSpellView(QModelIndex index_);

    void closeSpellView(const int& index_);

    void createSpellList();
    void loadSpellList();
    void saveSpellList();
    void saveAsSpellList();
    void addSpellButton();
    void updateTabName(SpellView* spellView);

private:

    void initToolBar();

    void initCentralWidget();

    void initDockWidgets();

    void initConnections();

    void sortTreeSpellView(SpellTreeView* treeview_);

    QTabWidget* _centralWidget;

    QList<QDockWidget*>* _spellList;

    SpellView* _spellPreview;

};

#endif // SPELLBOOKMAINWINDOW_H
