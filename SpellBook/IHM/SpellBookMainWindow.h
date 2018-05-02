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
    void addSpellView(SpellTreeView* treeView_, const QModelIndex& index_, bool enabled_);

signals:

public slots:

    void loadSpellPreview(const QModelIndex& index_);
    void addSpellViewExplorer(const QModelIndex &index_);
    void addSpellViewList(const QModelIndex &index_);
    void closeSpellView(const int& index_);

private:

    void initCentralWidget();

    void initDockWidgets();

    void initConnections();

    void hideRowSpellTreeView(SpellTreeView* treeview_, const bool& hasXMLHeader_);

    QTabWidget* _centralWidget;
    QDockWidget* _spellExplorer;
    QDockWidget* _spellList;

    SpellView* _spellPreview;

};

#endif // SPELLBOOKMAINWINDOW_H
