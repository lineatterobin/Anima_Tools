#include "PartyListWidget.h"

PartyListWidget::PartyListWidget(QWidget *parent_) : QDockWidget(parent_),
    _listWidget(new QListWidget(this))
{
    _listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

QListWidget *PartyListWidget::listWidget() const
{
    return _listWidget;
}

void PartyListWidget::setListWidget(QListWidget *listWidget)
{
    _listWidget = listWidget;
}
