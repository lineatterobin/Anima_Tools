#include "DomItem.h"

DomItem::DomItem(QDomNode &node, int row, DomItem *parent)
{
    domNode = node;
    rowNumber = row;
    parentItem = parent;
}

DomItem::~DomItem()
{
    QHash<int,DomItem*>::iterator it;
    for (it = childItems.begin(); it != childItems.end(); ++it)
        delete it.value();
}

DomItem *DomItem::parent()
{
    return parentItem;
}

int DomItem::row()
{
    return rowNumber;
}

QDomNode DomItem::node() const
{
    return domNode;
}

DomItem *DomItem::child(int i)
{
    if (childItems.contains(i))
        return childItems[i];

    if (i >= 0 && i < domNode.childNodes().count()) {
        QDomNode childNode = domNode.childNodes().item(i);
        DomItem *childItem = new DomItem(childNode, i, this);
        childItems[i] = childItem;
        return childItem;
    }
    return 0;
}

void DomItem::removeChild(int i)
{
    this->node().removeChild(this->child(i)->node());
    childItems.remove(i);
}

void DomItem::swapChild(int i, int j)
{
    DomItem* child_1 = child(i);
    DomItem* child_2 = child(j);
    QDomNode tmp = child_2->domNode;
    child_2->domNode = child_1->domNode;
    child_1->domNode = tmp;
}
