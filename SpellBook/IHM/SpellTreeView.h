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

    // Accesseurs
    void setReadOnly(const bool& readOnly_);
    bool isReadOnly();

    void setMaxDepth(const int &max_);
    int maxDepth();

private:

    QModelIndex hasDomaine(QString name_);
    void addDomaine(QString name_);
    bool hasSpells();
    void removeDomaine(const QModelIndex& index_);

    bool _readOnly;
    int _maxDepth;

};

#endif // SPELLTREEVIEW_H
