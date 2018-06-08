#include "SpellView.h"

#include <iostream>
#include <QMetaEnum>
#include <QPushButton>

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
    QFontMetrics a(_spellName->font());
    _spellName->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    _spellName->setMinimumWidth(50*a.averageCharWidth());
    QObject::connect(_spellName, SIGNAL(textChanged(QString)), this, SLOT(updateTitle()));

    _spellBookLabel = new QLabel("Domaine : ", this);
    _spellBook = new QLineEdit(this);
    QFontMetrics b(_spellBook->font());
    _spellBook->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    _spellBook->setMaximumWidth(15*b.averageCharWidth());

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
    QFontMetrics c(_spellCostInitial->font());
    _spellCostInitial->setMaximum(99999);
    _spellCostInitial->setFixedWidth(12*c.averageCharWidth());
    _spellCostIntermediaire = new QSpinBox(this);
    _spellCostIntermediaire->setMaximum(99999);
    _spellCostIntermediaire->setFixedWidth(12*c.averageCharWidth());
    _spellCostAvancee = new QSpinBox(this);
    _spellCostAvancee->setMaximum(99999);
    _spellCostAvancee->setFixedWidth(12*c.averageCharWidth());
    _spellCostArcane = new QSpinBox(this);
    _spellCostArcane->setMaximum(99999);
    _spellCostArcane->setFixedWidth(12*c.averageCharWidth());
    _spellRequirementInitial = new QSpinBox(this);
    _spellRequirementInitial->setFixedWidth(12*c.averageCharWidth());
    _spellRequirementIntermediaire = new QSpinBox(this);
    _spellRequirementIntermediaire->setFixedWidth(12*c.averageCharWidth());
    _spellRequirementAvancee = new QSpinBox(this);
    _spellRequirementAvancee->setFixedWidth(12*c.averageCharWidth());
    _spellRequirementArcane = new QSpinBox(this);
    _spellRequirementArcane->setFixedWidth(12*c.averageCharWidth());
    _spellMaintenanceInitial = new QSpinBox(this);
    _spellMaintenanceInitial->setFixedWidth(12*c.averageCharWidth());
    _spellMaintenanceIntermediaire = new QSpinBox(this);
    _spellMaintenanceIntermediaire->setFixedWidth(12*c.averageCharWidth());
    _spellMaintenanceAvancee = new QSpinBox(this);
    _spellMaintenanceAvancee->setFixedWidth(12*c.averageCharWidth());
    _spellMaintenanceArcane = new QSpinBox(this);
    _spellMaintenanceArcane->setFixedWidth(12*c.averageCharWidth());
    _spellEffectInitial = new QTextEdit(this);
    _spellEffectInitial->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    QFontMetrics m(_spellEffectInitial->font());
    _spellEffectInitial->setMaximumHeight(5*m.lineSpacing());
    _spellEffectInitial->setMinimumWidth(20*m.averageCharWidth());
    _spellEffectIntermediaire= new QTextEdit(this);
    _spellEffectIntermediaire->setMaximumHeight(5*m.lineSpacing());
    _spellEffectIntermediaire->setMinimumWidth(20*m.averageCharWidth());
    _spellEffectIntermediaire->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    _spellEffectAvancee = new QTextEdit(this);
    _spellEffectAvancee->setMaximumHeight(5*m.lineSpacing());
    _spellEffectAvancee->setMinimumWidth(20*m.averageCharWidth());
    _spellEffectAvancee->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    _spellEffectArcane = new QTextEdit(this);
    _spellEffectArcane->setMaximumHeight(5*m.lineSpacing());
    _spellEffectArcane->setMinimumWidth(20*m.averageCharWidth());
    _spellEffectArcane->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    _spellActionLabel = new QLabel("Action : ", this);
    _spellEffectTypeLabel = new QLabel("Effet : ", this);
    _spellMaintenanceTypeLabel = new QLabel("Maintien : ", this);
    _spellAction = new QComboBox(this);
    for(int i = 0; i < QMetaEnum::fromType<SpellEnum::ActionTypes>().keyCount(); ++i)
    {
        _spellAction->insertItem(i, QMetaEnum::fromType<SpellEnum::ActionTypes>().valueToKey(i));
    }
    QFontMetrics act(_spellAction->font());
    _spellAction->setMinimumWidth(15*act.averageCharWidth());
    _spellEffectType = new QComboBox(this);
    for(int i = 0; i < QMetaEnum::fromType<SpellEnum::EffectTypes>().keyCount(); ++i)
    {
        _spellEffectType->insertItem(i, QMetaEnum::fromType<SpellEnum::EffectTypes>().valueToKey(i));
    }
    _spellEffectType->setMinimumWidth(30*act.averageCharWidth());
    _spellMaintenanceType = new QComboBox(this);
    for(int i = 0; i < QMetaEnum::fromType<SpellEnum::MaintenanceTypes>().keyCount(); ++i)
    {
        _spellMaintenanceType->insertItem(i, QMetaEnum::fromType<SpellEnum::MaintenanceTypes>().valueToKey(i));
    }
    _spellMaintenanceType->setMinimumWidth(20*act.averageCharWidth());

    _spellSourceLabel = new QLabel("Source : ", this);
    _spellSource = new QLineEdit(this);
    _spellCommentaireLabel = new QLabel("Commetaires : ", this);
    _spellCommentaire = new QTextEdit(this);

    initForm();
    setReadOnly(true);
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
    QHBoxLayout* spellLayout2_4 = new QHBoxLayout;
    spellLayout2_4->addWidget(_spellMaintenanceTypeLabel, 0, Qt::AlignCenter);
    spellLayout2_4->addWidget(_spellMaintenanceType, 0, Qt::AlignCenter);
    spellLayout2_4->addStretch(1);
    spellLayout2->addLayout(spellLayout2_1,0);
    spellLayout2->addLayout(spellLayout2_2,0);
    spellLayout2->addLayout(spellLayout2_4,0);

    // Tableau des coûts
    QGridLayout* spellLayoutGrid = new QGridLayout;
    spellLayoutGrid->addWidget(_spellInitialLabel, 0, 1, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellIntermediaireLabel, 0, 2, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellAvanceeLabel, 0, 3, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellArcaneLabel, 0, 4, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellRequirementLabel, 1, 0, Qt::AlignLeft);
    spellLayoutGrid->addWidget(_spellRequirementInitial, 1, 1, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellRequirementIntermediaire, 1, 2, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellRequirementAvancee, 1, 3, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellRequirementArcane, 1, 4, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellCostLabel, 2, 0, Qt::AlignLeft);
    spellLayoutGrid->addWidget(_spellCostInitial, 2, 1, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellCostIntermediaire, 2, 2, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellCostAvancee, 2, 3, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellCostArcane, 2, 4, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellMaintenanceLabel, 3, 0, Qt::AlignLeft);
    spellLayoutGrid->addWidget(_spellMaintenanceInitial, 3, 1, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellMaintenanceIntermediaire, 3, 2, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellMaintenanceAvancee, 3, 3, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellMaintenanceArcane, 3, 4, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellEffectLabel, 4, 0, Qt::AlignLeft);
    spellLayoutGrid->addWidget(_spellEffectInitial, 4, 1, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellEffectIntermediaire, 4, 2, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellEffectAvancee, 4, 3, Qt::AlignCenter);
    spellLayoutGrid->addWidget(_spellEffectArcane, 4, 4, Qt::AlignCenter);

    // Source
    QHBoxLayout* spellLayoutSource = new QHBoxLayout;
    spellLayoutSource->addWidget(_spellSourceLabel, 0, Qt::AlignCenter);
    spellLayoutSource->addWidget(_spellSource, 0, Qt::AlignCenter);
    spellLayoutSource->addStretch(1);

    QHBoxLayout* spellLayoutCommentaire = new QHBoxLayout;
    QVBoxLayout* spellLayoutCommentaire_1 = new QVBoxLayout;
    spellLayoutCommentaire_1->addWidget(_spellCommentaireLabel, 0, Qt::AlignLeft);
    spellLayoutCommentaire_1->addWidget(_spellCommentaire);
    //QVBoxLayout* spellLayoutCommentaire_2 = new QVBoxLayout;
    //QPushButton* addSpellButton = new QPushButton("Ajouter");
    //addSpellButton->setToolTip("Ajoute le sort à la liste personnalisée");
    //QObject::connect(addSpellButton, SIGNAL(pressed()), this, SIGNAL(addSpellButtonClicked()));
    //spellLayoutCommentaire_2->addWidget(addSpellButton, 0, Qt::AlignCenter);
    spellLayoutCommentaire->addLayout(spellLayoutCommentaire_1, 0);
    //spellLayoutCommentaire->addLayout(spellLayoutCommentaire_2, 0);

    //Assemblage final
    spellLayout->addLayout(spellLayout1,0);
    spellLayout->addLayout(spellLayout2,0);
    spellLayout->addLayout(spellLayoutGrid,0);
    spellLayout->addWidget(_spellDescriptionLabel, 0, Qt::AlignLeft);
    spellLayout->addWidget(_spellDescription);
    spellLayout->addLayout(spellLayoutSource,0);
    spellLayout->addLayout(spellLayoutCommentaire, 0);


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

void SpellView::setReadOnly(const bool& value)
{
    if(_spellName != NULL)
        _spellName->setReadOnly(value);
    if(_spellLevel != NULL)
        _spellLevel->setReadOnly(value);
    if(_spellBook != NULL)
        _spellBook->setReadOnly(value);
    if(_spellDescription != NULL)
        _spellDescription->setReadOnly(value);
    if(_spellCostInitial != NULL)
        _spellCostInitial->setReadOnly(value);
    if(_spellCostIntermediaire != NULL)
        _spellCostIntermediaire->setReadOnly(value);
    if(_spellCostAvancee != NULL)
        _spellCostAvancee->setReadOnly(value);
    if(_spellCostArcane != NULL)
        _spellCostArcane->setReadOnly(value);
    if(_spellRequirementInitial != NULL)
        _spellRequirementInitial->setReadOnly(value);
    if(_spellRequirementIntermediaire != NULL)
        _spellRequirementIntermediaire->setReadOnly(value);
    if(_spellRequirementAvancee != NULL)
        _spellRequirementAvancee->setReadOnly(value);
    if(_spellRequirementArcane != NULL)
        _spellRequirementArcane->setReadOnly(value);
    if(_spellMaintenanceInitial != NULL)
        _spellMaintenanceInitial->setReadOnly(value);
    if(_spellMaintenanceIntermediaire != NULL)
        _spellMaintenanceIntermediaire->setReadOnly(value);
    if(_spellMaintenanceAvancee != NULL)
        _spellMaintenanceAvancee->setReadOnly(value);
    if(_spellMaintenanceArcane != NULL)
        _spellMaintenanceArcane->setReadOnly(value);
    if(_spellMaintenanceType != NULL)
        _spellMaintenanceType->setEnabled(!value);
    if(_spellCommentaire != NULL)
        _spellCommentaire->setReadOnly(value);
    if(_spellSource != NULL)
        _spellSource->setReadOnly(value);
    if(_spellEffectType != NULL)
        _spellEffectType->setEnabled(!value);
    if(_spellEffectInitial != NULL)
        _spellEffectInitial->setReadOnly(value);
    if(_spellEffectIntermediaire != NULL)
        _spellEffectIntermediaire->setReadOnly(value);
    if(_spellEffectAvancee != NULL)
        _spellEffectAvancee->setReadOnly(value);
    if(_spellEffectArcane != NULL)
        _spellEffectArcane->setReadOnly(value);
    if(_spellAction != NULL)
        _spellAction->setEnabled(!value);
}

void SpellView::loadData(QModelIndex index_, const QAbstractItemModel* model_)
{
    // Domaine
    QModelIndex parent = model_->parent(index_);
    _spellBook->setText(parent.data().toString());

    // Niveau
    QStringList niveau = index_.data().toString().split(" ", QString::SkipEmptyParts);
    QString niv = niveau.at(0);
    _spellLevel->setValue(niv.toInt());

    // Name
    QModelIndex child = model_->index(0,0,index_);
    _spellName->setText(model_->index(0,0,child).data().toString());

    // Initial values
    child = model_->index(0,0, model_->index(1,0,index_));
    _spellRequirementInitial->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(1,0, model_->index(1,0,index_));
    _spellCostInitial->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(2,0, model_->index(1,0,index_));
    _spellMaintenanceInitial->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(3,0, model_->index(1,0,index_));
    _spellEffectInitial->setText(model_->index(0,0,child).data().toString());

    // Intermediaire values
    child = model_->index(0,0, model_->index(2,0,index_));
    _spellRequirementIntermediaire->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(1,0, model_->index(2,0,index_));
    _spellCostIntermediaire->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(2,0, model_->index(2,0,index_));
    _spellMaintenanceIntermediaire->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(3,0, model_->index(2,0,index_));
    _spellEffectIntermediaire->setText(model_->index(0,0,child).data().toString());

    // Avancee values
    child = model_->index(0,0, model_->index(3,0,index_));
    _spellRequirementAvancee->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(1,0, model_->index(3,0,index_));
    _spellCostAvancee->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(2,0, model_->index(3,0,index_));
    _spellMaintenanceAvancee->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(3,0, model_->index(3,0,index_));
    _spellEffectAvancee->setText(model_->index(0,0,child).data().toString());

    // Arcane values
    child = model_->index(0,0, model_->index(4,0,index_));
    _spellRequirementArcane->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(1,0, model_->index(4,0,index_));
    _spellCostArcane->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(2,0, model_->index(4,0,index_));
    _spellMaintenanceArcane->setValue(model_->index(0,0,child).data().toInt());
    child = model_->index(3,0, model_->index(4,0,index_));
    _spellEffectArcane->setText(model_->index(0,0,child).data().toString());

    // Type de Maintien
    child = model_->index(5,0,index_);
    _spellMaintenanceType->setCurrentIndex(model_->index(0,0,child).data().toInt());

    // Type action
    child = model_->index(6,0,index_);
    if(QString::compare(model_->index(0,0,child).data().toString(), "ACTIVE", Qt::CaseInsensitive) == 0)
    {
        _spellAction->setCurrentIndex(SpellEnum::ACTIVE);
    }
    else
    {
        _spellAction->setCurrentIndex(SpellEnum::PASSIVE);
    }

    // Type effet
    child = model_->index(7,0,index_);
    if(QString::compare(model_->index(0,0,child).data().toString(), "AUTOMATIQUE", Qt::CaseInsensitive) == 0)
        _spellEffectType->setCurrentIndex(SpellEnum::AUTOMATIQUE);
    else if (QString::compare(model_->index(0,0,child).data().toString(), "EFFET", Qt::CaseInsensitive) == 0)
        _spellEffectType->setCurrentIndex(SpellEnum::EFFET);
    else if (QString::compare(model_->index(0,0,child).data().toString(), "ANIMIQUE", Qt::CaseInsensitive) == 0)
        _spellEffectType->setCurrentIndex(SpellEnum::ANIMIQUE);
    else if (QString::compare(model_->index(0,0,child).data().toString(), "ATTAQUE", Qt::CaseInsensitive) == 0)
        _spellEffectType->setCurrentIndex(SpellEnum::ATTAQUE);
    else if (QString::compare(model_->index(0,0,child).data().toString(), "DEFENSE", Qt::CaseInsensitive) == 0)
        _spellEffectType->setCurrentIndex(SpellEnum::DEFENSE);
    else if (QString::compare(model_->index(0,0,child).data().toString(), "DETECTION", Qt::CaseInsensitive) == 0)
        _spellEffectType->setCurrentIndex(SpellEnum::DETECTION);
    else if (QString::compare(model_->index(0,0,child).data().toString(), "EFFET_ANIMIQUE", Qt::CaseInsensitive) == 0)
        _spellEffectType->setCurrentIndex(SpellEnum::EFFET_ANIMIQUE);
    else if (QString::compare(model_->index(0,0,child).data().toString(), "ATTAQUE_ANIMIQUE", Qt::CaseInsensitive) == 0)
        _spellEffectType->setCurrentIndex(SpellEnum::ATTAQUE_ANIMIQUE);
    else
        _spellEffectType->setCurrentIndex(SpellEnum::EFFET);

    // Description
    child = model_->index(8,0,index_);
    _spellDescription->setText(model_->index(0,0,child).data().toString());

    // Commentaires
    child = model_->index(9,0,index_);
    _spellCommentaire->setText(model_->index(0,0,child).data().toString());

    // Source
    child = model_->index(10,0,index_);
    _spellSource->setText(model_->index(0,0,child).data().toString());

}

void SpellView::updateTitle()
{
    emit nameChanged(this);
}

QString SpellView::getName()
{
    return _spellName->text();
}

int SpellView::getLevel()
{
    return _spellLevel->value();
}

QString SpellView::getBook()
{
    return _spellBook->text();
}

QString SpellView::getDescription()
{
    return _spellDescription->toPlainText();
}

int SpellView::getCostInitial()
{
    return _spellCostInitial->value();
}

int SpellView::getCostIntermediaire()
{
    return _spellCostIntermediaire->value();
}

int SpellView::getCostAvancee()
{
    return _spellCostAvancee->value();
}

int SpellView::getCostArcane()
{
    return _spellCostArcane->value();
}
int SpellView::getRequirementInitial()
{
    return _spellRequirementInitial->value();
}

int SpellView::getRequirementIntermediaire()
{
    return _spellRequirementIntermediaire->value();
}

int SpellView::getRequirementAvancee()
{
    return _spellRequirementAvancee->value();
}

int SpellView::getRequirementArcane()
{
    return _spellRequirementArcane->value();
}
int SpellView::getMaintenanceInitial()
{
    return _spellMaintenanceInitial->value();
}

int SpellView::getMaintenanceIntermediaire()
{
    return _spellMaintenanceIntermediaire->value();
}

int SpellView::getMaintenanceAvancee()
{
    return _spellMaintenanceAvancee->value();
}

int SpellView::getMaintenanceArcane()
{
    return _spellMaintenanceArcane->value();
}

int SpellView::getMaintenanceType()
{
    return _spellMaintenanceType->currentIndex();
}

QString SpellView::getCommentaires()
{
    return _spellCommentaire->toPlainText();
}

QString SpellView::getSource()
{
    return _spellSource->text();
}

QString SpellView::getEffectType()
{
    return _spellEffectType->currentText();
}

QString SpellView::getEffectInitial()
{
    return _spellEffectInitial->toPlainText();
}

QString SpellView::getEffectIntermediaire()
{
    return _spellEffectIntermediaire->toPlainText();
}

QString SpellView::getEffectAvancee()
{
    return _spellEffectAvancee->toPlainText();
}

QString SpellView::getEffectArcane()
{
    return _spellEffectArcane->toPlainText();
}

QString SpellView::getAction()
{
    return _spellAction->currentText();
}
