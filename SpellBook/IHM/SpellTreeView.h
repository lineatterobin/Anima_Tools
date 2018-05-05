#ifndef SPELLTREEVIEW_H
#define SPELLTREEVIEW_H

#include <QTreeView>
#include <SpellBook/Modeles/SpellTreeModel.h>
#include <SpellBook/IHM/SpellView.h>

class SpellTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit SpellTreeView(QWidget *parent_);

    void hideTreeSpellData(const QModelIndex& startIndex_, int currentDepth_ = 0);

    void loadTreeData(QString xmlPath_);

    void addSpell(SpellView* spell_);

    // Accesseurs
    void setReadOnly(const bool& readOnly_);
    bool isReadOnly();

    void setMaxDepth(const int &max_);
    int maxDepth();
    SpellTreeModel* model();

    void refresh();

    void sort();

private:

    bool _readOnly;
    int _maxDepth;

};

#endif // SPELLTREEVIEW_H
