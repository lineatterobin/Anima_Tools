#include "TechniqueWidget.h"

#include <QHBoxLayout>
#include <QIntValidator>

TechniqueWidget::TechniqueWidget(QWidget *parent) : QWidget(parent),
    _nameLabel(new QLabel("Nom : ", this)),
    _name(new QLineEdit(this)),
    _levelLabel(new QLabel("Niveau : ", this)),
    _level(new QLineEdit(this)),
    _mkCostLabel(new QLabel("MK : ", this)),
    _mkCost(new QLineEdit(this))
{
    _name->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    QFontMetrics fm(_name->font());
    _name->setMinimumWidth(50*fm.averageCharWidth());

    QIntValidator* levelValidator = new QIntValidator(1,3,this);
    _level->setValidator(levelValidator);
    _level->setFixedWidth(6*fm.averageCharWidth());
    _level->setReadOnly(true);

    QIntValidator* mkValidator = new QIntValidator(0,1000,this);
    _mkCost->setValidator(mkValidator);
    _mkCost->setFixedWidth(8*fm.averageCharWidth());
    _mkCost->setReadOnly(true);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(_nameLabel, 0, Qt::AlignCenter);
    layout->addWidget(_name, 0, Qt::AlignCenter);
    layout->addStretch(1);
    layout->addWidget(_levelLabel, 0, Qt::AlignRight);
    layout->addWidget(_level, 0, Qt::AlignLeft);
    layout->addStretch(1);
    layout->addWidget(_mkCostLabel, 0, Qt::AlignRight);
    layout->addWidget(_mkCost, 0, Qt::AlignLeft);
    layout->addStretch(1);

    setLayout(layout);
    setMinimumSize(layout->minimumSize());
}

TechniqueWidget::~TechniqueWidget()
{
    if(_nameLabel != NULL)
    {
        _nameLabel->deleteLater();
        _nameLabel = NULL;
    }
    if(_name != NULL)
    {
        _name->deleteLater();
        _name = NULL;
    }
    if(_levelLabel != NULL)
    {
        _levelLabel->deleteLater();
        _levelLabel = NULL;
    }
    if(_level != NULL)
    {
        _level->deleteLater();
        _level = NULL;
    }
    if(_mkCostLabel != NULL)
    {
        _mkCostLabel->deleteLater();
        _mkCostLabel = NULL;
    }
    if(_mkCost != NULL)
    {
        _mkCost->deleteLater();
        _mkCost = NULL;
    }
}
