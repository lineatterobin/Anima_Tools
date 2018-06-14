#include "SpellDockWidget.h"
#include <Socle/Constantes.h>
#include <SpellBook/IHM/SpellBookMainWindow.h>

#include <QPushButton>
#include <iostream>

SpellDockWidget::SpellDockWidget(QWidget *parent, SpellEnum::TreeTypes type_, QString data_) : QDockWidget(parent),
    _treeView(NULL),
    _type(type_)
{
    QObject::connect(this, SIGNAL(objectNameChanged(QString)), this, SLOT(setWindowTitle(QString)));

    _treeView = new SpellTreeView(this);
    _treeView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    _treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QObject::connect(_treeView, SIGNAL(pathChanged()), this, SLOT(refreshFileNameLabel()));
    QObject::connect(_treeView, SIGNAL(dataChanged()), this, SLOT(fileNameLabelModified()));

    SpellBookMainWindow* mainW = (SpellBookMainWindow*)this->parent();
    int listCount = 0;


    if(type_ == SpellEnum::CUSTOM)
    {
        while(mainW->spellListExist(SPELLLIST + QString::number(listCount)) != -1)
        {
            ++listCount;
        }
        this->setObjectName(SPELLLIST + QString::number(listCount));
        setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
        _treeView->loadTreeData(data_);
        setWindowTitle(this->objectName());
        _treeView->setHeaderHidden(true);
        _treeView->sort();
        _treeView->setReadOnly(false);

        QPushButton* addSpellButton = new QPushButton("Ajouter le sort");
        addSpellButton->setToolTip("Ajoute le sort actuel à la liste personnalisée");
        QObject::connect(addSpellButton, SIGNAL(pressed()), this, SLOT(addSpellButtonClickedAction()));

        QString path = _treeView->xmlPath();
        path = path.mid(path.lastIndexOf("/")).remove(0,1);
        _fileNameLabel = new QLabel("Nom du fichier : " + path);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(_fileNameLabel);
        layout->addWidget(_treeView, 0);
        layout->addWidget(addSpellButton, 0, Qt::AlignCenter);

        QWidget* widget = new QWidget(this);
        widget->setLayout(layout);
        setWidget(widget);
    }
    else if (type_ == SpellEnum::SOURCE)
    {
        while(mainW->spellListExist(SPELLEXPLORER + QString::number(listCount)) != -1)
        {
            ++listCount;
        }
        this->setObjectName(SPELLEXPLORER + QString::number(listCount));
        setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        _treeView->loadTreeData(data_);
        _treeView->setHeaderHidden(true);
        _treeView->sort();
        _treeView->setReadOnly(true);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(_treeView, 0);

        QWidget* widget = new QWidget(this);
        widget->setLayout(layout);
        setWidget(widget);
    }
    else //never reach
    {
        return;
    }

    QObject::connect(_treeView->model(), SIGNAL(saved()), this, SLOT(fileNameLabelSaved()));

}

SpellDockWidget::SpellDockWidget(QString name_, QWidget *parent) : SpellDockWidget(parent)
{
    if(name_ != "")
        _treeView->model()->rename(name_);
}

void SpellDockWidget::addSpellButtonClickedAction()
{
    emit addSpellButtonClicked(this->_treeView);
}

void SpellDockWidget::refreshFileNameLabel()
{
    QString path = _treeView->xmlPath();
    path = path.mid(path.lastIndexOf("/")).remove(0,1);
    _fileNameLabel->setText("Nom du fichier : " + path);
}

void SpellDockWidget::fileNameLabelModified()
{
    QString text = _fileNameLabel->text();
    if (text.indexOf("*") == -1)
        _fileNameLabel->setText(text + "*");
}

void SpellDockWidget::fileNameLabelSaved()
{
    _fileNameLabel->setText(_fileNameLabel->text().remove("*"));
}

void SpellDockWidget::closeEvent(QCloseEvent *event_)
{
    if(event_->type() == QEvent::Close)
    {
        emit closeRequest(this);
    }
    else
    {
        event_->accept();
    }

}

QLabel *SpellDockWidget::getFileNameLabel() const
{
    return _fileNameLabel;
}

SpellTreeView* SpellDockWidget::getTree()
{
    return _treeView;
}


