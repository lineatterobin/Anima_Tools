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
    SpellView *addSpellView(SpellTreeView* treeView_, const QModelIndex& index_, bool readOnly_);

signals:

public slots:

    void loadSpellPreview(const QModelIndex& index_);
    void addSpellViewExplorer(const QModelIndex &index_);
    void addSpellViewList(const QModelIndex &index_);

    void closeSpellView(const int& index_);

    void createSpellList();
    void loadSpellList();
    void saveSpellList();
    void saveAsSpellList();
    void addSpellButton();

private:

    void initToolBar();

    void initCentralWidget();

    void initDockWidgets();

    void initConnections();

    void sortTreeSpellView(SpellTreeView* treeview_);

    QTabWidget* _centralWidget;
    QDockWidget* _spellExplorer;
    QDockWidget* _spellList;

    SpellView* _spellPreview;

};

#endif // SPELLBOOKMAINWINDOW_H
