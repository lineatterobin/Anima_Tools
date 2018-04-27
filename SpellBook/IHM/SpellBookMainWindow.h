#ifndef SPELLBOOKMAINWINDOW_H
#define SPELLBOOKMAINWINDOW_H

#include <SpellBook/IHM/SpellView.h>

#include <QMainWindow>
#include <QToolBar>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QTreeView>

class SpellBookMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SpellBookMainWindow(QString styleSheet_);

    ~SpellBookMainWindow();

    void setTheme(QString styleSheet_);

signals:

public slots:

    void loadSpellPreview(const QModelIndex& index_);
    void addSpellView(bool enabled_);

private:

    void initCentralWidget();

    void initDockWidgets();

    void initConnections();

    void loadTreeData(QTreeView *treeView_, QString xmlPath);
    void hideTreeSpellData(QTreeView* treeView_, const QModelIndex &startIndex_, int currentDepth_ = 0);

    QTabWidget* _centralWidget;
    QDockWidget* _spellExplorer;
    QDockWidget* _spellList;

    SpellView* _spellPreview;

};

#endif // SPELLBOOKMAINWINDOW_H
