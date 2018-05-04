#include "SpellTreeView.h"

#include <QFile>
#include <SpellBook/Modeles/SpellTreeModel.h>

SpellTreeView::SpellTreeView(QWidget* parent_) : QTreeView(parent_),
    _readOnly(false),
    _maxDepth(3)
{
}

void SpellTreeView::hideTreeSpellData(const QModelIndex& startIndex_, int currentDepth_)
{
    QAbstractItemModel* model = this->model();
    int childCount = model->rowCount(startIndex_);

    for(int i = 0; i< childCount; ++i)
    {
        if(currentDepth_ < maxDepth())
        {
            // On descent d'un niveau.
            hideTreeSpellData(model->index(i,0,startIndex_), currentDepth_ + 1);
        }
        else
        {
            //Niveau du sort : On cache les informations des niveaux inférieurs.
            this->setRowHidden(i, startIndex_, true);
        }
    }

}

void SpellTreeView::loadTreeData(QString xmlPath_)
{
    QDomDocument document;
    if (!xmlPath_.isEmpty()) {
        QFile file(xmlPath_);
        if (file.open(QIODevice::ReadOnly)) {
            if (document.setContent(&file)) {
                SpellTreeModel *newModel = new SpellTreeModel(document, this);
                this->setModel(newModel);
            }
            file.close();
        }
    }
    else
    {
        QDomProcessingInstruction process = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
        document.appendChild(process);
        SpellTreeModel *newModel = new SpellTreeModel(document, this);
        this->setModel(newModel);
    }
}



void SpellTreeView::setReadOnly(const bool& readOnly_)
{
    _readOnly = readOnly_;
}

bool SpellTreeView::isReadOnly()
{
    return _readOnly;
}

void SpellTreeView::setMaxDepth(const int& max_)
{
    _maxDepth = max_;
}

int SpellTreeView::maxDepth()
{
    return _maxDepth;
}

SpellTreeModel* SpellTreeView::model()
{
    return (SpellTreeModel*)QTreeView::model();
}
