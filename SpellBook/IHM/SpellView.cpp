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
    _spellBook->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _spellBook->insertItem(1, QIcon(), "Lumière");
    _spellBook->insertItem(2, QIcon(), "Obscurité");
    _spellBook->insertItem(3, QIcon(), "Création");
    _spellBook->insertItem(4, QIcon(), "Destruction");
    _spellBook->insertItem(5, QIcon(), "Necromancie");

    _spellLevelLabel = new QLabel("/", this);
    _spellLevelLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _spellLevel = new QSpinBox(this);
    _spellLevel->setMaximum(100);
    _spellLevel->setMinimum(2);
    _spellLevel->setSingleStep(2);
    _spellLevel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    _spellDescriptionLabel = new QLabel("Description:", this);
    _spellDescriptionLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _spellDescription = new QTextEdit(this);
    _spellDescription->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    initForm();
}

SpellView::~SpellView()
{
}

void SpellView::initForm()
{
    // Initialsation du formulaire
    QVBoxLayout* spellLayout = new QVBoxLayout(this);
    spellLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    QHBoxLayout* spellLayout1 = new QHBoxLayout(this);
    spellLayout1->setSizeConstraint(QLayout::SetMinAndMaxSize);

    QHBoxLayout* spellLayout1_1 = new QHBoxLayout(this);
    spellLayout1_1->setSizeConstraint(QLayout::SetFixedSize);
    spellLayout1_1->addWidget(_spellBookLabel, 0, Qt::AlignCenter);
    spellLayout1_1->addWidget(_spellBook, 0, Qt::AlignCenter);
    spellLayout1_1->addWidget(_spellLevelLabel, 0, Qt::AlignLeft);
    spellLayout1_1->addWidget(_spellLevel, 0, Qt::AlignLeft);
    spellLayout1_1->addStretch(1);
    QHBoxLayout* spellLayout1_2 = new QHBoxLayout(this);
    spellLayout1_2->setSizeConstraint(QLayout::SetFixedSize);
    spellLayout1_2->addWidget(_spellNameLabel, 0, Qt::AlignCenter);
    spellLayout1_2->addWidget(_spellName, 0, Qt::AlignCenter);
    spellLayout1_2->addStretch(1);

    spellLayout1->addLayout(spellLayout1_1,0);
    spellLayout1->addLayout(spellLayout1_2,0);

    spellLayout->addLayout(spellLayout1,0);
    spellLayout->addWidget(_spellDescriptionLabel, 0, Qt::AlignLeft);
    spellLayout->addWidget(_spellDescription, 0, Qt::AlignLeft);

    this->setMinimumSize(spellLayout->minimumSize());
    setLayout(spellLayout);
}
