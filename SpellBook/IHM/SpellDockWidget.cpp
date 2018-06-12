#include "SpellDockWidget.h"
#include <Socle/Constantes.h>

#include <QPushButton>
#include <iostream>

SpellDockWidget::SpellDockWidget(QWidget *parent, int listCount_, SpellEnum::TreeTypes type_, QString data_) : QDockWidget(parent),
    _treeView(NULL),
    _type(type_)
{
    QObject::connect(this, SIGNAL(objectNameChanged(QString)), this, SLOT(setWindowTitle(QString)));

    _treeView = new SpellTreeView(this);
    _treeView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    _treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    if(type_ == SpellEnum::CUSTOM)
    {
        this->setObjectName(SPELLLIST + QString::number(listCount_));
        setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
        //setFeatures(QDockWidget::NoDockWidgetFeatures);
        _treeView->loadTreeData(data_);
        std::cout << this->objectName().toStdString() << std::endl;
        setWindowTitle(this->objectName());
        _treeView->setHeaderHidden(true);
        _treeView->sort();
        _treeView->setReadOnly(false);

        QPushButton* addSpellButton = new QPushButton("Ajouter le sort");
        addSpellButton->setToolTip("Ajoute le sort actuel à la liste personnalisée");
        QObject::connect(addSpellButton, SIGNAL(pressed()), this, SLOT(addSpellButtonClickedAction()));

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(_treeView, 0);
        layout->addWidget(addSpellButton, 0, Qt::AlignCenter);

        QWidget* widget = new QWidget(this);
        widget->setLayout(layout);
        setWidget(widget);
    }
    else if (type_ == SpellEnum::SOURCE)
    {
        this->setObjectName(SPELLEXPLORER + QString::number(listCount_));
        //setWindowTitle(this->objectName());
        setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        //setFeatures(QDockWidget::NoDockWidgetFeatures);
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
}

void SpellDockWidget::addSpellButtonClickedAction()
{
    emit addSpellButtonClicked(this->_treeView);
}

SpellTreeView* SpellDockWidget::getTree()
{
    return _treeView;
}


