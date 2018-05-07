#ifndef DOMITEM_H
#define DOMITEM_H

#include <QDomNode>
#include <QHash>

class DomItem
{
public:
    DomItem(QDomNode &node, int row, DomItem *parent = 0);
    ~DomItem();
    DomItem *child(int i);
    DomItem *parent();
    QDomNode node() const;
    int row();

    void removeChild(int i);
    void swapChild(int i, int j);

private:
    QDomNode domNode;
    QHash<int,DomItem*> childItems;
    DomItem *parentItem;
    int rowNumber;
};

#endif // DOMITEM_H
