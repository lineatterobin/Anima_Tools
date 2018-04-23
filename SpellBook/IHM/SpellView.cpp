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
    _spellEffectType(NULL)
{
    _spellNameLabel = new QLabel("Nom : ", this);
    _spellName = new QLineEdit(this);

    initForm();
}

SpellView::~SpellView()
{
}

void SpellView::initForm()
{
    // Initialsation du formulaire

    QFormLayout* spellLayout = new QFormLayout(this);
    spellLayout->addRow(_spellNameLabel, _spellName);

    setLayout(spellLayout);
}
