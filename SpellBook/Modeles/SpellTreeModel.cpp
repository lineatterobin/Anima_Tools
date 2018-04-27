#include "SpellTreeModel.h"

SpellTreeModel::SpellTreeModel(QDomDocument document, QObject *parent)
    : QAbstractItemModel(parent), domDocument(document)
{
    rootItem = new DomItem(domDocument, 0);
}

SpellTreeModel::~SpellTreeModel()
{
    delete rootItem;
}

int SpellTreeModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

Qt::ItemFlags SpellTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant SpellTreeModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return QVariant();
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QModelIndex SpellTreeModel::index(int row, int column, const QModelIndex &parent)
const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DomItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DomItem*>(parent.internalPointer());

    DomItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

int SpellTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    DomItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DomItem*>(parent.internalPointer());

    return parentItem->node().childNodes().count();
}

QModelIndex SpellTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
    DomItem *parentItem = childItem->parent();

    if (!parentItem || parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant SpellTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    DomItem *item = static_cast<DomItem*>(index.internalPointer());

    QDomNode node = item->node();
    if(!node.hasChildNodes())
        return node.nodeValue();

    QDomNamedNodeMap attributeMap = node.attributes();

    QDomNode child = node.firstChild();

    if(index.column() == 0)
    {
        if(node.nodeName() == "Sort")
            return attributeMap.item(0).nodeValue() + " " + node.firstChild().firstChild().nodeValue().split("\n").join(' ');
        else if(!child.hasChildNodes())
            return node.nodeName();
        else
            return attributeMap.item(0).nodeValue();
    }
    else
    {
        return QVariant();
    }
}

