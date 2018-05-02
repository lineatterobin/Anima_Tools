#ifndef SPELLTREEVIEW_H
#define SPELLTREEVIEW_H

#include <QTreeView>

class SpellTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit SpellTreeView(QWidget *parent_);

    void hideTreeSpellData(const QModelIndex& startIndex_, int currentDepth_ = 0);
    void loadTreeData(QString xmlPath_);

};

#endif // SPELLTREEVIEW_H
