#ifndef SpellTreeModel_H
#define SpellTreeModel_H

#include <QObject>
#include <QAbstractItemModel>
#include <QDomDocument>
#include <Librairies/Modeles/DomItem.h>
#include <SpellBook/IHM/SpellView.h>

class SpellTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SpellTreeModel(QDomDocument document, QObject *parent = 0);
    ~SpellTreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int, Qt::Orientation,
                        int = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void sort();
    void sortBooks(const QModelIndex &parent_ = QModelIndex());
    void sortSpells(const QModelIndex &parent_ = QModelIndex());

    QDomNode addBook(const QString &name_);
    void addSpell(SpellView* spell_, QDomNode book_);
    void removeSpell(const QModelIndex &index_);

    void save(QString fileName_);

private:

    QDomDocument _domDocument;
    DomItem* _rootItem;
};

#endif // SpellTreeModel_H
