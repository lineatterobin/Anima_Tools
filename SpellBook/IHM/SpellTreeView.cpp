#include "SpellTreeView.h"

#include <QFile>
#include <iostream>
#include <QMessageBox>
#include <QInputDialog>

#include <SpellBook/IHM/SpellBookMainWindow.h>

SpellTreeView::SpellTreeView(QWidget* parent_) : QTreeView(parent_),
    _readOnly(false),
    _maxDepth(2),
    _contextMenu(NULL),
    _indexCustomMenu(),
    _xmlPath("")
{
    _contextMenu = new QMenu(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomMenuRequest(QPoint)));

    QMenu* addMenu = new QMenu(this);
    addMenu->setTitle("Ajouter à ...");
    connect(addMenu, SIGNAL(triggered(QAction*)), this, SLOT(addSpellTo(QAction*)));
    _contextMenu->addAction("Ouvrir", this, SLOT(openSpell()));
    _contextMenu->addAction("Renommer", this, SLOT(renameBiblio()));
    _contextMenu->addSeparator();
    _contextMenu->addMenu(addMenu);
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
    SpellTreeModel* newModel = NULL;
    if (!xmlPath_.isEmpty())
    {
        QFile file(xmlPath_);
        if (file.open(QIODevice::ReadOnly))
        {
            if (document.setContent(&file))
            {
                newModel = new SpellTreeModel(document, this);
                this->setModel(newModel);
                _xmlPath = xmlPath_;
                this->parent()->setObjectName(this->model()->index(1,0).data().toString());
            }
            file.close();
        }
    }
    else
    {
        QDomProcessingInstruction process = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"ISO-8859-1\"");
        document.appendChild(process);
        QDomElement bibliotheque = document.createElement("Biblio");
        bibliotheque.setAttribute("Name", this->parent()->objectName());
        document.appendChild(bibliotheque);
        newModel = new SpellTreeModel(document, this);
        this->setModel(newModel);
    }
    QObject::connect(newModel, SIGNAL(nameBilioChanged(QString)), this, SLOT(renameObject(QString)));
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
        emit dataChanged();

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
        if(action->text() == "Renommer")
        {
            if(isBiblio(_indexCustomMenu) && !this->isReadOnly())
            {
                action->setEnabled(true);
                action->setVisible(true);
            }
            else
            {
                action->setEnabled(false);
                action->setVisible(false);
            }
        }
        if(action->text() == "Ajouter à ...")
        {
            action->setEnabled(true);
            action->setVisible(true);
            QMenu* submenu = action->menu();
            submenu->clear();
            SpellBookMainWindow* mainW = (SpellBookMainWindow*)this->parent()->parent()->parent();
            QList<SpellDockWidget*> list = mainW->getList();
            Q_FOREACH (SpellDockWidget* widget, list)
            {
                SpellTreeView* treeview = widget->getTree();
                if(!treeview->isReadOnly() && widget->objectName() != this->parent()->parent()->objectName())
                {
                    QAction *action = new QAction(widget->objectName());
                    action->setData(list.indexOf(widget));
                    submenu->addAction(action);
                }
            }
            if(submenu->isEmpty())
            {
                QAction* action = new QAction("Vide");
                action->setEnabled(false);
                submenu->addAction(action);
            }
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
    if(isSpell(_indexCustomMenu) && !isReadOnly())
    {
        this->model()->removeSpell(_indexCustomMenu);
    }
    else if(isBook(_indexCustomMenu) && !isReadOnly())
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
            emit dataChanged();
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

void SpellTreeView::addSpellTo(QAction* action_)
{
    SpellBookMainWindow* mainW = (SpellBookMainWindow*)this->parent()->parent()->parent();
    QList<SpellDockWidget*> list = mainW->getList();
    SpellTreeView* target_ = list.at(action_->data().toInt())->getTree();
    if(isBook(_indexCustomMenu) && !target_->isReadOnly())
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setMinimumSize(250,150);
        msgBox.setText("Vous avez demandé l'ajout d'un livre de sort.");
        msgBox.setInformativeText("Voulez-vous vraiment ajouter l'ensemble des sorts de ce livre ?");
        QPushButton *oui = msgBox.addButton("Confirmer", QMessageBox::AcceptRole);
        QPushButton *cancel = msgBox.addButton("Annuler", QMessageBox::RejectRole);
        msgBox.setDefaultButton(oui);
        msgBox.exec();

        if(msgBox.clickedButton() == (QAbstractButton*)oui)
        {
            // Oui was clicked
            for(int i=0; i < this->model()->rowCount(_indexCustomMenu); ++i)
            {
                SpellView* spellView = new SpellView(this);
                spellView->loadData(this->model()->index(i,0,_indexCustomMenu), this->model());

                target_->addSpell(spellView);
            }
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
    if(isSpell(_indexCustomMenu) && !target_->isReadOnly())
    {
        SpellView* spellView = new SpellView(this);
        spellView->loadData(_indexCustomMenu, this->model());

        target_->addSpell(spellView);
    }
}

void SpellTreeView::openSpell()
{
    if(isSpell(_indexCustomMenu))
    {
        emit openRequest(_indexCustomMenu);
    }
}

void SpellTreeView::renameBiblio()
{
    bool ok;
    SpellBookMainWindow* mainW = (SpellBookMainWindow*)this->parent()->parent()->parent();
    QString text = QInputDialog::getText(0, "Renommer", "Nouveau nom :", QLineEdit::Normal, "", &ok);
    if(ok)
    {
        if(mainW->spellListExist(text) != -1)
        {
                QMessageBox* msgBox = new QMessageBox();
                msgBox->setIcon(QMessageBox::Warning);
                msgBox->setMinimumSize(250, 150);
                QString msg = "Une liste nommée \"" + text + "\" existe déjà.";
                msgBox->setText(msg);
                msgBox->exec();
                msgBox->deleteLater();
                return;
        }
        else if(text != "")
        {
            this->model()->rename(text);
            emit dataChanged();
        }
        else
        {
            QMessageBox* msgBox = new QMessageBox();
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->setMinimumSize(250, 150);
            QString msg = "Impossible de renommer avec un nom vide.";
            msgBox->setText(msg);
            msgBox->exec();
            msgBox->deleteLater();
            return;
        }
    }
}

void SpellTreeView::renameObject(const QString& name_)
{
    this->parent()->parent()->setObjectName(name_);
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

void SpellTreeView::setXmlPath(QString xmlPath_)
{
    _xmlPath = xmlPath_;
    emit pathChanged();
}

QString SpellTreeView::xmlPath()
{
    return _xmlPath;
}

bool SpellTreeView::isBiblio(const QModelIndex& index_)
{
    return (this->model()->type(index_) == "Biblio");
}

bool SpellTreeView::isBook(const QModelIndex &index_)
{
    return (this->model()->type(index_) == "Livre");
}

bool SpellTreeView::isSpell(const QModelIndex &index_)
{
    return (this->model()->type(index_) == "Sort");
}
