#ifndef DOMITEM_H
#define DOMITEM_H

#include <QDomNode>
#include <QHash>

/*!
 * \brief La classe DomItem représente les items manipulé par SpellTreeModel.
 */
class DomItem
{
public:
    /*!
     * \brief DomItem : Constructeur
     * \param node : Noeud associé dans le DOMDocument.
     * \param row : Place parmis ses items frères.
     * \param parent : Item parent.
     */
    DomItem(QDomNode &node, int row, DomItem *parent = 0);

    /*!
     * \brief ~DomItem : Destructeur
     */
    ~DomItem();

    /*!
     * \brief child : retourne un pointeur sur le ième DomItem fils. (Créé s'il n'existe pas.)
     * \param i
     * \return DomItem
     */
    DomItem *child(int i);

    /*!
     * \brief parent : retourne un pointeur sur le DomItem parent.
     * \return DomItem
     */
    DomItem *parent();

    /*!
     * \brief node : retourne le QDomNode asscocié.
     * \return QDomNode
     */
    QDomNode node() const;

    /*!
     * \brief row :
     * \return int rowNumber
     */
    int row();

    /*!
     * \brief removeChild : supprime le ième fils.
     * \param i
     */
    void removeChild(int i);

    /*!
     * \brief swapChild : inverse les positions du ième et du jème fils.
     * \param i
     * \param j
     */
    void swapChild(int i, int j);

private:
    QDomNode _domNode;
    QHash<int,DomItem*> _childItems;
    DomItem *_parentItem;
    int _rowNumber;
};

#endif // DOMITEM_H
