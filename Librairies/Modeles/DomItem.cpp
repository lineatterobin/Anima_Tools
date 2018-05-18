#include "DomItem.h"

#include <iostream>

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
    for(int j=i+1; j<childItems.size(); ++j)
    {
        swapChild(j,j-1);
    }
    this->node().removeChild(this->child(childItems.size()-1)->node());
    childItems.remove(childItems.size()-1);

    if(this->node().childNodes().count() == 0 && this->node().nodeName() == "Livre")
        this->parent()->removeChild(this->row());
}

/*!
 * \brief DomItem::swapChild inverse les positions de i et j
 * \param i
 * \param j
 */
void DomItem::swapChild(int i, int j)
{
    DomItem* child_1 = child(i);
    DomItem* child_2 = child(j);

    // Modification XML
    QDomNode tmp = child_2->node().previousSibling();
    domNode.insertBefore(child_2->node(), child_1->node());
    domNode.insertAfter(child_1->node(),tmp);

    // Modification Model
    int rowTmp = child_2->rowNumber;
    child_2->rowNumber = child_1->rowNumber;
    child_1->rowNumber = rowTmp;
    DomItem *itemTmp = childItems[j];
    childItems[j] = childItems[i];
    childItems[i] = itemTmp;
}
