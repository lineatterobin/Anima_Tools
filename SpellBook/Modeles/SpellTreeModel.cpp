#include "SpellTreeModel.h"

#include <iostream>

SpellTreeModel::SpellTreeModel(QDomDocument document, QObject *parent)
    : QAbstractItemModel(parent), _domDocument(document)
{
    _rootItem = new DomItem(_domDocument, 0);
}

SpellTreeModel::~SpellTreeModel()
{
    delete _rootItem;
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

QVariant SpellTreeModel::headerData(int, Qt::Orientation, int) const
{
    return QVariant();
}

QModelIndex SpellTreeModel::index(int row, int column, const QModelIndex &parent)
const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DomItem *parentItem;

    if (!parent.isValid())
        parentItem = _rootItem;
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
        parentItem = _rootItem;
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

    if (!parentItem || parentItem == _rootItem)
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
    {
        if(node.nodeName() == "Biblio" || node.nodeName() == "Livre")
            return node.attributes().item(0).nodeValue();
        else
            return node.nodeValue();
    }

    QDomNamedNodeMap attributeMap = node.attributes();

    QDomNode child = node.firstChild();

    if(index.column() == 0)
    {
        if(node.nodeName() == "Sort")
            return attributeMap.item(0).nodeValue() + " " + node.firstChild().firstChild().nodeValue().split("\n").join(' ');
        else if(node.nodeName() == "Biblio" || node.nodeName() == "Livre")
            return node.attributes().item(0).nodeValue();
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

void SpellTreeModel::sort()
{
    emit layoutAboutToBeChanged();
    sortBooks();
    sortSpells();
    emit layoutChanged();
}


void SpellTreeModel::sortSpells(const QModelIndex &parent_)
{
    DomItem* parentItem;
    if (!parent_.isValid())
        parentItem = _rootItem->child(1);
    else
        parentItem = static_cast<DomItem*>(parent_.internalPointer());

    QDomNode node = parentItem->node();
    for(int j=0; j < node.childNodes().count() ; ++j)
    {
        DomItem* childItem = parentItem->child(j);
        for(int i=0; i < childItem->node().childNodes().count() ; ++i)
        {
            //sort
            if(childItem->child(i)->node().nodeName() == "Sort")
            {
                int c = i;
                while(c > 0)
                {
                    if( QString::compare(childItem->child(c)->node().attributes().item(0).nodeValue(), childItem->child(c-1)->node().attributes().item(0).nodeValue()) < 0)
                        childItem->swapChild(c-1,c);
                    else
                        break;

                    c = c-1;
                }
            }
        }
    }
}

void SpellTreeModel::sortBooks(const QModelIndex &parent_)
{
    DomItem* parentItem;
    if (!parent_.isValid())
        parentItem = _rootItem->child(1);
    else
        parentItem = static_cast<DomItem*>(parent_.internalPointer());

    QDomNode node = parentItem->node();

    for(int i=0; i < node.childNodes().count() ; ++i)
    {
        //sort
        if(parentItem->child(i)->node().nodeName() == "Livre")
        {
            int c = i;
            while(c > 0)
            {
                if( QString::compare(parentItem->child(c)->node().attributes().item(0).nodeValue(), parentItem->child(c-1)->node().attributes().item(0).nodeValue()) < 0)
                    parentItem->swapChild(c-1,c);
                else
                    break;

                c = c-1;
            }
        }
    }
}

QDomNode SpellTreeModel::addBook(const QString &name_)
{
    QDomNode biblio = _domDocument.namedItem("Biblio");
    QDomNode livre = biblio.firstChild();
    while((QString::compare(livre.attributes().item(0).nodeValue(), name_) != 0 ) && !(livre.nextSibling().isNull()))
    {
        livre = livre.nextSibling();
    }

    if(QString::compare(livre.attributes().item(0).nodeValue(), name_) != 0)
    {
        // On crée le livre.
        QDomElement livreElt = _domDocument.createElement("Livre");
        livreElt.setAttribute("Name", name_);
        biblio.appendChild(livreElt);
        livre = livreElt;
    }

    return livre;
}

void SpellTreeModel::addSpell(SpellView *spell_, QDomNode book_)
{
    QDomNode sort = book_.firstChild();
    while((QString::compare(sort.attributes().item(0).nodeValue(), spell_->getName()) != 0 ) && !(sort.nextSibling().isNull()))
    {
        sort = sort.nextSibling();
    }

    if(QString::compare(sort.attributes().item(0).nodeValue(), spell_->getName()) != 0)
    {
        // On crée le sort.
        QDomElement sortElt = _domDocument.createElement("Sort");
        sortElt.setAttribute("Level", QString("%1").arg(spell_->getLevel(), 3, 10, QChar('0')));

        // On rempli les informations du sorts.
        QDomElement name = _domDocument.createElement("name");
        name.appendChild(_domDocument.createTextNode(spell_->getName()));
        sortElt.appendChild(name);

        QDomElement initial = _domDocument.createElement("initial");
        QDomElement req = _domDocument.createElement("requirement");
        req.appendChild(_domDocument.createTextNode(QString::number(spell_->getRequirementInitial())));
        QDomElement cost = _domDocument.createElement("cost");
        cost.appendChild(_domDocument.createTextNode(QString::number(spell_->getCostInitial())));
        QDomElement maintien = _domDocument.createElement("maintien");
        maintien.appendChild(_domDocument.createTextNode(QString::number(spell_->getMaintenanceInitial())));
        QDomElement effets = _domDocument.createElement("effets");
        effets.appendChild(_domDocument.createTextNode(spell_->getEffectInitial()));
        initial.appendChild(req);
        initial.appendChild(cost);
        initial.appendChild(maintien);
        initial.appendChild(effets);
        sortElt.appendChild(initial);

        QDomElement intermediaire = _domDocument.createElement("intermediaire");
        req = _domDocument.createElement("requirement");
        req.appendChild(_domDocument.createTextNode(QString::number(spell_->getRequirementIntermediaire())));
        cost = _domDocument.createElement("cost");
        cost.appendChild(_domDocument.createTextNode(QString::number(spell_->getCostIntermediaire())));
        maintien = _domDocument.createElement("maintien");
        maintien.appendChild(_domDocument.createTextNode(QString::number(spell_->getMaintenanceIntermediaire())));
        effets = _domDocument.createElement("effets");
        effets.appendChild(_domDocument.createTextNode(spell_->getEffectIntermediaire()));
        intermediaire.appendChild(req);
        intermediaire.appendChild(cost);
        intermediaire.appendChild(maintien);
        intermediaire.appendChild(effets);
        sortElt.appendChild(intermediaire);

        QDomElement avancee = _domDocument.createElement("avancee");
        req = _domDocument.createElement("requirement");
        req.appendChild(_domDocument.createTextNode(QString::number(spell_->getRequirementAvancee())));
        cost = _domDocument.createElement("cost");
        cost.appendChild(_domDocument.createTextNode(QString::number(spell_->getCostAvancee())));
        maintien = _domDocument.createElement("maintien");
        maintien.appendChild(_domDocument.createTextNode(QString::number(spell_->getMaintenanceAvancee())));
        effets = _domDocument.createElement("effets");
        effets.appendChild(_domDocument.createTextNode(spell_->getEffectAvancee()));
        avancee.appendChild(req);
        avancee.appendChild(cost);
        avancee.appendChild(maintien);
        avancee.appendChild(effets);
        sortElt.appendChild(avancee);

        QDomElement arcane = _domDocument.createElement("arcane");
        req = _domDocument.createElement("requirement");
        req.appendChild(_domDocument.createTextNode(QString::number(spell_->getRequirementArcane())));
        cost = _domDocument.createElement("cost");
        cost.appendChild(_domDocument.createTextNode(QString::number(spell_->getCostArcane())));
        maintien = _domDocument.createElement("maintien");
        maintien.appendChild(_domDocument.createTextNode(QString::number(spell_->getMaintenanceArcane())));
        effets = _domDocument.createElement("effets");
        effets.appendChild(_domDocument.createTextNode(spell_->getEffectArcane()));
        arcane.appendChild(req);
        arcane.appendChild(cost);
        arcane.appendChild(maintien);
        arcane.appendChild(effets);
        sortElt.appendChild(arcane);

        QDomElement maintienType = _domDocument.createElement("maitien_types");
        maintienType.appendChild(_domDocument.createTextNode(QString::number(spell_->getMaintenanceType())));
        sortElt.appendChild(maintienType);

        QDomElement action = _domDocument.createElement("action");
        action.appendChild(_domDocument.createTextNode(spell_->getAction()));
        sortElt.appendChild(action);

        QDomElement effetsType = _domDocument.createElement("effets_type");
        effetsType.appendChild(_domDocument.createTextNode(spell_->getEffectType()));
        sortElt.appendChild(effetsType);

        QDomElement description = _domDocument.createElement("description");
        description.appendChild(_domDocument.createTextNode(spell_->getDescription()));
        sortElt.appendChild(description);

        QDomElement commentaire = _domDocument.createElement("commentaire");
        commentaire.appendChild(_domDocument.createTextNode(spell_->getCommentaires()));
        sortElt.appendChild(commentaire);

        QDomElement source = _domDocument.createElement("source");
        source.appendChild(_domDocument.createTextNode(spell_->getSource()));
        sortElt.appendChild(source);

        // On ajoute le sort au livre.
        book_.appendChild(sortElt);

        std::cout << _domDocument.toString().toStdString() << std::endl;
    }
    else
    {
        // On modifie le sort.
    }

}
