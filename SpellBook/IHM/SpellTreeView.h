#ifndef SPELLTREEVIEW_H
#define SPELLTREEVIEW_H

#include <QTreeView>
#include <QMenu>
#include <QAction>

#include <SpellBook/Modeles/SpellTreeModel.h>
#include <SpellBook/IHM/SpellView.h>

class SpellTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit SpellTreeView(QWidget *parent_);

    ~SpellTreeView();

    void hideTreeSpellData(const QModelIndex& startIndex_, int currentDepth_ = 0);

    void loadTreeData(QString xmlPath_);

    void addSpell(SpellView* spell_);

    // Accesseurs
    void setReadOnly(const bool& readOnly_);
    bool isReadOnly();

    void setMaxDepth(const int &max_);
    int maxDepth();

    void setSiblingSpellTree(SpellTreeView* treeView);

    SpellTreeModel* model();

    void setXmlPath(QString xmlPath_);
    QString xmlPath();

    void refresh();

    void sort();

public slots:
    void onCustomMenuRequest(const QPoint &point_);
    void removeSpellFrom();
    void addSpellTo();

private:

    bool _readOnly;
    int _maxDepth;
    QMenu* _contextMenu;
    QModelIndex _indexCustomMenu;

    SpellTreeView* _siblingSpellTree;

    QString _xmlPath;

};

#endif // SPELLTREEVIEW_H
