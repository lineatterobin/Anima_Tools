#ifndef SpellTreeModel_H
#define SpellTreeModel_H

#include <QObject>
#include <QAbstractItemModel>
#include <QDomDocument>
#include <Librairies/Modeles/DomItem.h>

class SpellTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SpellTreeModel(QDomDocument document, QObject *parent = 0);
    ~SpellTreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    QDomDocument domDocument;
    DomItem *rootItem;
};

#endif // SpellTreeModel_H