#include "SpellView.h"

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
    _spellRMysLabel(NULL),
    _spellRMysBoolLabel(NULL),
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
    _spellBook->insertItem(1, QIcon(), "Lumière");
    _spellBook->insertItem(2, QIcon(), "Obscurité");
    _spellBook->insertItem(3, QIcon(), "Création");
    _spellBook->insertItem(4, QIcon(), "Destruction");
    _spellBook->insertItem(5, QIcon(), "Necromancie");

    _spellLevelLabel = new QLabel("/", this);
    _spellLevel = new QSpinBox(this);
    _spellLevel->setMaximum(100);
    _spellLevel->setMinimum(2);
    _spellLevel->setSingleStep(2);

    _spellDescriptionLabel = new QLabel("Description : ", this);
    _spellDescription = new QTextEdit(this);
    _spellDescription->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

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

    spellLayout->addLayout(spellLayout1,0);
    spellLayout->addWidget(_spellDescriptionLabel, 0, Qt::AlignLeft);
    spellLayout->addWidget(_spellDescription);

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

