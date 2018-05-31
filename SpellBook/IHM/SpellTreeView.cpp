#include "SpellTreeView.h"

#include <QFile>
#include <iostream>
#include <QMessageBox>

SpellTreeView::SpellTreeView(QWidget* parent_) : QTreeView(parent_),
    _readOnly(false),
    _maxDepth(2),
    _contextMenu(NULL),
    _indexCustomMenu(),
    _siblingSpellTree(NULL),
    _xmlPath("")
{
    _contextMenu = new QMenu(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomMenuRequest(QPoint)));
    _contextMenu->addAction("Ouvrir", this, SLOT(openSpell()));
    _contextMenu->addAction("Ajouter au Grimoire", this, SLOT(addSpellTo()));
    _contextMenu->addAction("Retirer du Grimoire", this, SLOT(removeSpellFrom()));
}

SpellTreeView::~SpellTreeView()
{
    delete this->model();
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
                _xmlPath = xmlPath_;
            }
            file.close();
        }
    }
    else
    {
        QDomProcessingInstruction process = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"ISO-8859-1\"");
        document.appendChild(process);
        QDomElement bibliotheque = document.createElement("Biblio");
        bibliotheque.setAttribute("Name", "Grimoire");
        document.appendChild(bibliotheque);
        SpellTreeModel *newModel = new SpellTreeModel(document, this);
        this->setModel(newModel);
    }
}

void SpellTreeView::addSpell(SpellView* spell_)
{
    if (spell_->getBook() == "" || spell_->getName() == "")
    {
        QMessageBox* msgBox = new QMessageBox();
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setMinimumSize(250, 150);
        QString msg = "Impossible d'ajouter un sort sans les informations suivantes : ";
        msg += "\n - Domaine\n - Nom\n";
        msgBox->setText(msg);
        msgBox->exec();
        msgBox->deleteLater();
    }
    else
    {

        //Vérifier si le Livre existe, sinon le créer
        QDomNode book = this->model()->addBook(spell_->getBook());

        //Vérifier si le sort existe, si oui le modifier si non le créer
        this->model()->addSpell(spell_, book);

        //Trier l'arbre.
        this->sort();
    }
}

void SpellTreeView::sort()
{
    this->model()->sort();
    this->setRowHidden(0, QModelIndex(), true);
    this->hideTreeSpellData(this->model()->index(1, 0));
}

void SpellTreeView::onCustomMenuRequest(const QPoint &point_)
{
    _indexCustomMenu = this->indexAt(point_);
    QList<QAction*> actions = _contextMenu->actions();
    Q_FOREACH (QAction* action, actions)
    {
        if(action->text() == "Ouvrir")
        {
            action->setEnabled(true);
            action->setVisible(true);
        }
        if(action->text() == "Ajouter au Grimoire")
        {
            action->setEnabled(this->isReadOnly());
            action->setVisible(this->isReadOnly());
        }
        if(action->text() == "Retirer du Grimoire")
        {
            action->setEnabled(!this->isReadOnly());
            action->setVisible(!this->isReadOnly());
        }

    }

    _contextMenu->exec(this->mapToGlobal(point_));
}

void SpellTreeView::removeSpellFrom()
{
    if(this->model()->index(0,0,_indexCustomMenu).data().toString() == "name" && !isReadOnly())
    {
        this->model()->removeSpell(_indexCustomMenu);
    }
    else if(_indexCustomMenu.parent().data().toString() == "Grimoire" && !isReadOnly())
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setMinimumSize(250,150);
        msgBox.setText("Le livre contient peut-être des sorts.");
        msgBox.setInformativeText("Voulez-vous vraiment supprimer ce livre ?");
        QPushButton *oui = msgBox.addButton("Confirmer", QMessageBox::AcceptRole);
        QPushButton *cancel = msgBox.addButton("Annuler", QMessageBox::RejectRole);
        msgBox.setDefaultButton(oui);
        msgBox.exec();

        if(msgBox.clickedButton() == (QAbstractButton*)oui)
        {
            // Oui was clicked
            this->model()->removeBook(_indexCustomMenu);
        }
        else if(msgBox.clickedButton() == (QAbstractButton*)cancel)
        {
            // Cancel was clicked
            return;
        }
        else
        {
            // should never be reached
            return;
        }
    }

    this->sort();

}

void SpellTreeView::addSpellTo()
{
    if(this->model()->index(0,0,_indexCustomMenu).data().toString() == "name" && !_siblingSpellTree->isReadOnly())
    {
        SpellView* spellView = new SpellView(this);
        spellView->loadData(_indexCustomMenu, this->model());

        _siblingSpellTree->addSpell(spellView);
    }
}

void SpellTreeView::openSpell()
{
    if(this->model()->index(0,0,_indexCustomMenu).data().toString() == "name")
    {
        emit openRequest(_indexCustomMenu);
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

void SpellTreeView::setSiblingSpellTree(SpellTreeView *treeView)
{
    _siblingSpellTree = treeView;
}

SpellTreeModel* SpellTreeView::model()
{
    return (SpellTreeModel*)QTreeView::model();
}

void SpellTreeView::setXmlPath(QString xmlPath_)
{
    _xmlPath = xmlPath_;
}

QString SpellTreeView::xmlPath()
{
    return _xmlPath;
}
