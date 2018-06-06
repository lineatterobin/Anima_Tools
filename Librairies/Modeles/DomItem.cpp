#include "DomItem.h"

DomItem::DomItem(QDomNode &node, int row, DomItem *parent)
{
    _domNode = node;
    _rowNumber = row;
    _parentItem = parent;
}

DomItem::~DomItem()
{
    QHash<int,DomItem*>::iterator it;
    for (it = _childItems.begin(); it != _childItems.end(); ++it)
        delete it.value();
}

DomItem *DomItem::parent()
{
    return _parentItem;
}

int DomItem::row()
{
    return _rowNumber;
}

QDomNode DomItem::node() const
{
    return _domNode;
}

DomItem *DomItem::child(int i)
{
    if (_childItems.contains(i))
        return _childItems[i];

    if (i >= 0 && i < _domNode.childNodes().count()) {
        QDomNode childNode = _domNode.childNodes().item(i);
        DomItem *childItem = new DomItem(childNode, i, this);
        _childItems[i] = childItem;
        return childItem;
    }
    return 0;
}

void DomItem::removeChild(int i)
{
    //On déplace l'élément à supprimer à la fin du QHash.
    for(int j=i+1; j<_childItems.size(); ++j)
    {
        swapChild(j,j-1);
    }

    //On supprime le fils dans le QDomDocument.
    this->node().removeChild(this->child(_childItems.size()-1)->node());
    //On supprime le fils dans le QHash.
    _childItems.remove(_childItems.size()-1);

}

void DomItem::swapChild(int i, int j)
{
    DomItem* child_1 = child(i);
    DomItem* child_2 = child(j);

    // Modification QDomDocument
    QDomNode tmp = child_2->node().previousSibling();
    _domNode.insertBefore(child_2->node(), child_1->node());
    _domNode.insertAfter(child_1->node(),tmp);

    // Modification interne
    int rowTmp = child_2->_rowNumber;
    child_2->_rowNumber = child_1->_rowNumber;
    child_1->_rowNumber = rowTmp;
    DomItem *itemTmp = _childItems[j];
    _childItems[j] = _childItems[i];
    _childItems[i] = itemTmp;
}
