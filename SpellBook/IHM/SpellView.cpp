#include "SpellView.h"

#include <iostream>
#include <QMetaEnum>

#include <SpellBook/Modeles/SpellEnum.h>

SpellView::SpellView(QWidget *parent) : QWidget(parent),
    _spellNameLabel(NULL),
    _spellLevelLabel(NULL),
    _spellBookLabel(NULL),
    _spellDescriptionLabel(NULL),
    _spellInitialLabel(NULL),
    _spellIntermediaireLabel(NULL),
    _spellAvanceeLabel(NULL),
    _spellArcaneLabel(NULL),
    _spellCostLabel(NULL),
    _spellRequirementLabel(NULL),
    _spellMaintenanceLabel(NULL),
    _spellMaintenanceTypeLabel(NULL),
    _spellRMysLabel(NULL),
    _spellCommentaireLabel(NULL),
    _spellSourceLabel(NULL),
    _spellEffectTypeLabel(NULL),
    _spellEffectLabel(NULL),
    _spellActionLabel(NULL),
    _spellName(NULL),
    _spellLevel(NULL),
    _spellBook(NULL),
    _spellDescription(NULL),
    _spellCostInitial(NULL),
    _spellCostIntermediaire(NULL),
    _spellCostAvancee(NULL),
    _spellCostArcane(NULL),
    _spellRequirementInitial(NULL),
    _spellRequirementIntermediaire(NULL),
    _spellRequirementAvancee(NULL),
    _spellRequirementArcane(NULL),
    _spellMaintenanceInitial(NULL),
    _spellMaintenanceIntermediaire(NULL),
    _spellMaintenanceAvancee(NULL),
    _spellMaintenanceArcane(NULL),
    _spellMaintenanceType(NULL),
    _spellRMys(NULL),
    _spellRMysBool(NULL),
    _spellCommentaire(NULL),
    _spellSource(NULL),
    _spellEffectType(NULL),
    _spellEffectInitial(NULL),
    _spellEffectIntermediaire(NULL),
    _spellEffectAvancee(NULL),
    _spellEffectArcane(NULL),
    _spellAction(NULL)
{
    _spellNameLabel = new QLabel("Nom : ", this);
    _spellName = new QLineEdit(this);
    _spellName->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    _spellBookLabel = new QLabel("Domaine : ", this);
    _spellBook = new QComboBox(this);
    for(int i = 0; i < QMetaEnum::fromType<SpellEnum::Books>().keyCount(); ++i)
    {
        _spellBook->insertItem(i, QMetaEnum::fromType<SpellEnum::Books>().valueToKey(i));
    }

    _spellLevelLabel = new QLabel("/", this);
    _spellLevel = new QSpinBox(this);
    _spellLevel->setMaximum(100);
    _spellLevel->setMinimum(2);
    _spellLevel->setSingleStep(2);

    _spellDescriptionLabel = new QLabel("Description : ", this);
    _spellDescription = new QTextEdit(this);
    _spellDescription->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    _spellInitialLabel = new QLabel("Initial", this);
    _spellIntermediaireLabel = new QLabel("Intermédiaire", this);
    _spellAvanceeLabel = new QLabel("Avancée", this);
    _spellArcaneLabel = new QLabel("Arcane", this);
    _spellCostLabel = new QLabel("Coût", this);
    _spellRequirementLabel = new QLabel("Intel. Requis", this);
    _spellMaintenanceLabel = new QLabel("Maintien", this);
    _spellEffectLabel = new QLabel("Effets", this);
    _spellCostInitial = new QSpinBox(this);
    _spellCostIntermediaire = new QSpinBox(this);
    _spellCostAvancee = new QSpinBox(this);
    _spellCostArcane = new QSpinBox(this);
    _spellRequirementInitial = new QSpinBox(this);
    _spellRequirementIntermediaire = new QSpinBox(this);
    _spellRequirementAvancee = new QSpinBox(this);
    _spellRequirementArcane = new QSpinBox(this);
    _spellMaintenanceInitial = new QSpinBox(this);
    _spellMaintenanceIntermediaire = new QSpinBox(this);
    _spellMaintenanceAvancee = new QSpinBox(this);
    _spellMaintenanceArcane = new QSpinBox(this);
    _spellEffectInitial = new QLineEdit(this);
    _spellEffectInitial->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    _spellEffectIntermediaire= new QLineEdit(this);
    _spellEffectIntermediaire->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    _spellEffectAvancee = new QLineEdit(this);
    _spellEffectAvancee->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    _spellEffectArcane = new QLineEdit(this);
    _spellEffectArcane->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    _spellActionLabel = new QLabel("Action : ", this);
    _spellEffectTypeLabel = new QLabel("Effet : ", this);
    _spellRMysLabel = new QLabel("RMys : ", this);
    _spellMaintenanceTypeLabel = new QLabel("Maintien : ", this);
    _spellAction = new QComboBox(this);
    for(int i = 0; i < QMetaEnum::fromType<SpellEnum::ActionTypes>().keyCount(); ++i)
    {
        _spellAction->insertItem(i, QMetaEnum::fromType<SpellEnum::ActionTypes>().valueToKey(i));
    }
    _spellEffectType = new QComboBox(this);
    for(int i = 0; i < QMetaEnum::fromType<SpellEnum::EffectTypes>().keyCount(); ++i)
    {
        _spellEffectType->insertItem(i, QMetaEnum::fromType<SpellEnum::EffectTypes>().valueToKey(i));
    }
    _spellRMysBool = new QComboBox(this);
    _spellRMysBool->insertItem(0, "OUI");
    _spellRMysBool->insertItem(1, "NON");
    _spellRMys = new QSpinBox(this);
    _spellMaintenanceType = new QComboBox(this);
    for(int i = 0; i < QMetaEnum::fromType<SpellEnum::MaintenanceTypes>().keyCount(); ++i)
    {
        _spellMaintenanceType->insertItem(i, QMetaEnum::fromType<SpellEnum::MaintenanceTypes>().valueToKey(i));
    }

    _spellSourceLabel = new QLabel("Source : ", this);
    _spellSource = new QLineEdit(this);
    _spellCommentaireLabel = new QLabel("Commetaires : ", this);
    _spellCommentaire = new QTextEdit(this);

    initForm();
    setEnabled(false);
}

SpellView::~SpellView()
{

}

void SpellView::initForm()
{
    // Initialsation du formulaire
    QVBoxLayout* spellLayout = new QVBoxLayout(this);

    // Eléments principaux
    QHBoxLayout* spellLayout1 = new QHBoxLayout;
    QHBoxLayout* spellLayout1_1 = new QHBoxLayout;
    spellLayout1_1->addWidget(_spellBookLabel, 0, Qt::AlignCenter);
    spellLayout1_1->addWidget(_spellBook, 0, Qt::AlignCenter);
    spellLayout1_1->addWidget(_spellLevelLabel, 0, Qt::AlignLeft);
    spellLayout1_1->addWidget(_spellLevel, 0, Qt::AlignLeft);
    spellLayout1_1->addStretch(1);
    QHBoxLayout* spellLayout1_2 = new QHBoxLayout;
    spellLayout1_2->addWidget(_spellNameLabel, 0, Qt::AlignCenter);
    spellLayout1_2->addWidget(_spellName, 0, Qt::AlignCenter);
    spellLayout1_2->addStretch(1);
    spellLayout1->addLayout(spellLayout1_1,0);
    spellLayout1->addLayout(spellLayout1_2,0);

    // Eléments Secondaires
    QHBoxLayout* spellLayout2 = new QHBoxLayout;
    QHBoxLayout* spellLayout2_1 = new QHBoxLayout;
    spellLayout2_1->addWidget(_spellActionLabel, 0, Qt::AlignCenter);
    spellLayout2_1->addWidget(_spellAction, 0, Qt::AlignCenter);
    spellLayout2_1->addStretch(1);
    QHBoxLayout* spellLayout2_2 = new QHBoxLayout;
    spellLayout2_2->addWidget(_spellEffectTypeLabel, 0, Qt::AlignCenter);
    spellLayout2_2->addWidget(_spellEffectType, 0, Qt::AlignCenter);
    spellLayout2_2->addStretch(1);
    QHBoxLayout* spellLayout2_3 = new QHBoxLayout;
    spellLayout2_3->addWidget(_spellRMysLabel, 0, Qt::AlignCenter);
    spellLayout2_3->addWidget(_spellRMysBool, 0, Qt::AlignCenter);
    spellLayout2_3->addWidget(_spellRMys, 0, Qt::AlignCenter);
    spellLayout2_3->addStretch(1);
    QHBoxLayout* spellLayout2_4 = new QHBoxLayout;
    spellLayout2_4->addWidget(_spellMaintenanceTypeLabel, 0, Qt::AlignCenter);
    spellLayout2_4->addWidget(_spellMaintenanceType, 0, Qt::AlignCenter);
    spellLayout2_4->addStretch(1);
    spellLayout2->addLayout(spellLayout2_1,0);
    spellLayout2->addLayout(spellLayout2_2,0);
    spellLayout2->addLayout(spellLayout2_3,0);
    spellLayout2->addLayout(spellLayout2_4,0);

    // Tableau des coûts
    QGridLayout* spellLayoutGrid = new QGridLayout;
    spellLayoutGrid->addWidget(_spellInitialLabel, 0, 1, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellIntermediaireLabel, 0, 2, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellAvanceeLabel, 0, 3, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellArcaneLabel, 0, 4, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellRequirementLabel, 1, 0, Qt::AlignLeft);
    spellLayoutGrid->addWidget(_spellRequirementInitial, 1, 1);
    spellLayoutGrid->addWidget(_spellRequirementIntermediaire, 1, 2);
    spellLayoutGrid->addWidget(_spellRequirementAvancee, 1, 3);
    spellLayoutGrid->addWidget(_spellRequirementArcane, 1, 4);
    spellLayoutGrid->addWidget(_spellCostLabel, 2, 0, Qt::AlignLeft);
    spellLayoutGrid->addWidget(_spellCostInitial, 2, 1);
    spellLayoutGrid->addWidget(_spellCostIntermediaire, 2, 2);
    spellLayoutGrid->addWidget(_spellCostAvancee, 2, 3);
    spellLayoutGrid->addWidget(_spellCostArcane, 2, 4);
    spellLayoutGrid->addWidget(_spellMaintenanceLabel, 3, 0, Qt::AlignLeft);
    spellLayoutGrid->addWidget(_spellMaintenanceInitial, 3, 1);
    spellLayoutGrid->addWidget(_spellMaintenanceIntermediaire, 3, 2);
    spellLayoutGrid->addWidget(_spellMaintenanceAvancee, 3, 3);
    spellLayoutGrid->addWidget(_spellMaintenanceArcane, 3, 4);
    spellLayoutGrid->addWidget(_spellEffectLabel, 4, 0, Qt::AlignLeft);
    spellLayoutGrid->addWidget(_spellEffectInitial, 4, 1);
    spellLayoutGrid->addWidget(_spellEffectIntermediaire, 4, 2);
    spellLayoutGrid->addWidget(_spellEffectAvancee, 4, 3);
    spellLayoutGrid->addWidget(_spellEffectArcane, 4, 4);

    // Source
    QHBoxLayout* spellLayoutSource = new QHBoxLayout;
    spellLayoutSource->addWidget(_spellSourceLabel, 0, Qt::AlignCenter);
    spellLayoutSource->addWidget(_spellSource, 0, Qt::AlignCenter);
    spellLayoutSource->addStretch(1);

    //Assemblage final
    spellLayout->addLayout(spellLayout1,0);
    spellLayout->addLayout(spellLayout2,0);
    spellLayout->addLayout(spellLayoutGrid,0);
    spellLayout->addWidget(_spellDescriptionLabel, 0, Qt::AlignLeft);
    spellLayout->addWidget(_spellDescription);
    spellLayout->addLayout(spellLayoutSource,0);
    spellLayout->addWidget(_spellCommentaireLabel, 0, Qt::AlignLeft);
    spellLayout->addWidget(_spellCommentaire);

    this->setMinimumSize(spellLayout->minimumSize());
    setLayout(spellLayout);
}

void SpellView::setEnabled(const bool& value)
{
    if(_spellName != NULL)
        _spellName->setEnabled(value);
    if(_spellLevel != NULL)
        _spellLevel->setEnabled(value);
    if(_spellBook != NULL)
        _spellBook->setEnabled(value);
    if(_spellDescription != NULL)
        _spellDescription->setEnabled(value);
    if(_spellCostInitial != NULL)
        _spellCostInitial->setEnabled(value);
    if(_spellCostIntermediaire != NULL)
        _spellCostIntermediaire->setEnabled(value);
    if(_spellCostAvancee != NULL)
        _spellCostAvancee->setEnabled(value);
    if(_spellCostArcane != NULL)
        _spellCostArcane->setEnabled(value);
    if(_spellRequirementInitial != NULL)
        _spellRequirementInitial->setEnabled(value);
    if(_spellRequirementIntermediaire != NULL)
        _spellRequirementIntermediaire->setEnabled(value);
    if(_spellRequirementAvancee != NULL)
        _spellRequirementAvancee->setEnabled(value);
    if(_spellRequirementArcane != NULL)
        _spellRequirementArcane->setEnabled(value);
    if(_spellMaintenanceInitial != NULL)
        _spellMaintenanceInitial->setEnabled(value);
    if(_spellMaintenanceIntermediaire != NULL)
        _spellMaintenanceIntermediaire->setEnabled(value);
    if(_spellMaintenanceAvancee != NULL)
        _spellMaintenanceAvancee->setEnabled(value);
    if(_spellMaintenanceArcane != NULL)
        _spellMaintenanceArcane->setEnabled(value);
    if(_spellMaintenanceType != NULL)
        _spellMaintenanceType->setEnabled(value);
    if(_spellRMys != NULL)
        _spellRMys->setEnabled(value);
    if(_spellRMysBool != NULL)
        _spellRMysBool->setEnabled(value);
    if(_spellCommentaire != NULL)
        _spellCommentaire->setEnabled(value);
    if(_spellSource != NULL)
        _spellSource->setEnabled(value);
    if(_spellEffectType != NULL)
        _spellEffectType->setEnabled(value);
    if(_spellEffectInitial != NULL)
        _spellEffectInitial->setEnabled(value);
    if(_spellEffectIntermediaire != NULL)
        _spellEffectIntermediaire->setEnabled(value);
    if(_spellEffectAvancee != NULL)
        _spellEffectAvancee->setEnabled(value);
    if(_spellEffectArcane != NULL)
        _spellEffectArcane->setEnabled(value);
    if(_spellAction != NULL)
        _spellAction->setEnabled(value);
}

void SpellView::loadData(const QModelIndex& index_, QAbstractItemModel* model)
{
    // Name
    QModelIndex child = model->index(0,0,index_);
    _spellName->setText(model->index(0,0,child).data().toString());

    // Initial values
    child = model->index(0,0, model->index(1,0,index_));
    _spellRequirementInitial->setValue(model->index(0,0,child).data().toInt());
    child = model->index(1,0, model->index(1,0,index_));
    _spellCostInitial->setValue(model->index(0,0,child).data().toInt());
    child = model->index(2,0, model->index(1,0,index_));
    _spellMaintenanceInitial->setValue(model->index(0,0,child).data().toInt());
    child = model->index(3,0, model->index(1,0,index_));
    _spellEffectInitial->setText(model->index(0,0,child).data().toString());

    // Intermediaire values
    child = model->index(0,0, model->index(2,0,index_));
    _spellRequirementIntermediaire->setValue(model->index(0,0,child).data().toInt());
    child = model->index(1,0, model->index(2,0,index_));
    _spellCostIntermediaire->setValue(model->index(0,0,child).data().toInt());
    child = model->index(2,0, model->index(2,0,index_));
    _spellMaintenanceIntermediaire->setValue(model->index(0,0,child).data().toInt());
    child = model->index(3,0, model->index(2,0,index_));
    _spellEffectIntermediaire->setText(model->index(0,0,child).data().toString());

    // Avancee values
    child = model->index(0,0, model->index(3,0,index_));
    _spellRequirementAvancee->setValue(model->index(0,0,child).data().toInt());
    child = model->index(1,0, model->index(3,0,index_));
    _spellCostAvancee->setValue(model->index(0,0,child).data().toInt());
    child = model->index(2,0, model->index(3,0,index_));
    _spellMaintenanceAvancee->setValue(model->index(0,0,child).data().toInt());
    child = model->index(3,0, model->index(3,0,index_));
    _spellEffectAvancee->setText(model->index(0,0,child).data().toString());

    //Arcane values
    child = model->index(0,0, model->index(4,0,index_));
    _spellRequirementArcane->setValue(model->index(0,0,child).data().toInt());
    child = model->index(1,0, model->index(4,0,index_));
    _spellCostArcane->setValue(model->index(0,0,child).data().toInt());
    child = model->index(2,0, model->index(4,0,index_));
    _spellMaintenanceArcane->setValue(model->index(0,0,child).data().toInt());
    child = model->index(3,0, model->index(4,0,index_));
    _spellEffectArcane->setText(model->index(0,0,child).data().toString());

    //Type de Maintien
    child = model->index(5,0,index_);
    _spellMaintenanceType->setCurrentIndex(model->index(0,0,child).data().toInt());
}
