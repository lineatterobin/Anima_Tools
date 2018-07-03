#include "TechniqueWidget.h"

#include <QHBoxLayout>
#include <QIntValidator>

TechniqueWidget::TechniqueWidget(QWidget *parent) : QWidget(parent),
    _nameLabel(new QLabel("Nom : ", this)),
    _name(new QLineEdit(this)),
    _levelLabel(new QLabel("Niveau : ", this)),
    _level(new QLineEdit(this)),
    _diCostLabel(new QLabel("DI : ", this)),
    _diCost(new QLineEdit(this)),
    _typeLabel(new QLabel("Type : ", this)),
    _type(new QLineEdit(this)),
    _combinable(new QCheckBox("Cominable : ",this)),
    _maintenanceType(new QComboBox(this))
{
    _name->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    QFontMetrics fm(_name->font());
    _name->setMinimumWidth(50*fm.averageCharWidth());

    QIntValidator* levelValidator = new QIntValidator(1,3,this);
    _level->setValidator(levelValidator);
    _level->setFixedWidth(6*fm.averageCharWidth());
    _level->setReadOnly(true);

    QIntValidator* mkValidator = new QIntValidator(0,1000,this);
    _diCost->setValidator(mkValidator);
    _diCost->setFixedWidth(8*fm.averageCharWidth());
    _diCost->setReadOnly(true);

    _type->setFixedWidth(25*fm.averageCharWidth());
    _type->setReadOnly(true);

    QHBoxLayout* nameLayout = new QHBoxLayout;
    nameLayout->addWidget(_nameLabel, 0, Qt::AlignCenter);
    nameLayout->addWidget(_name, 0, Qt::AlignCenter);
    nameLayout->addStretch(1);
    nameLayout->addWidget(_levelLabel, 0, Qt::AlignRight);
    nameLayout->addWidget(_level, 0, Qt::AlignLeft);
    nameLayout->addStretch(1);
    nameLayout->addWidget(_diCostLabel, 0, Qt::AlignRight);
    nameLayout->addWidget(_diCost, 0, Qt::AlignLeft);
    nameLayout->addStretch(1);
    nameLayout->addWidget(_typeLabel, 0, Qt::AlignRight);
    nameLayout->addWidget(_type, 0, Qt::AlignLeft);

    _combinable->setTristate(false);
    _combinable->setCheckState(Qt::Unchecked);

    _maintenanceType->insertItem(0, "AUCUN");
    _maintenanceType->insertItem(1, "MAINTIEN");
    _maintenanceType->insertItem(2, "SOUTIEN");
    _maintenanceType->setMinimumWidth(15*fm.averageCharWidth());

    QHBoxLayout* optionsLayout = new QHBoxLayout;
    optionsLayout->addStretch(1);
    optionsLayout->addWidget(_combinable, 0, Qt::AlignCenter);
    optionsLayout->addStretch(1);
    optionsLayout->addWidget(_maintenanceType, 0, Qt::AlignCenter);
    optionsLayout->addStretch(1);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(nameLayout, 0);
    layout->addLayout(optionsLayout, 0);
    layout->addStretch(1); //temporaire

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
    if(_diCostLabel != NULL)
    {
        _diCostLabel->deleteLater();
        _diCostLabel = NULL;
    }
    if(_diCost != NULL)
    {
        _diCost->deleteLater();
        _diCost = NULL;
    }
    if(_typeLabel != NULL)
    {
        _typeLabel->deleteLater();
        _typeLabel = NULL;
    }
    if(_type != NULL)
    {
        _type->deleteLater();
        _type = NULL;
    }

}
