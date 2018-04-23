#ifndef SPELLVIEW_H
#define SPELLVIEW_H

#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>

class SpellView : public QWidget
{
    Q_OBJECT
public:
    explicit SpellView(QWidget *parent = nullptr);

    ~SpellView();

signals:

public slots:

private:

    void initForm();

    // Libellés
    QLabel* _spellNameLabel;
    QLabel* _spellLevelLabel;
    QLabel* _spellBookLabel;
    QLabel* _spellDescriptionLabel;
    QLabel* _spellInitialLabel;
    QLabel* _spellIntermediaireLabel;
    QLabel* _spellAvanceeLabel;
    QLabel* _spellArcaneLabel;
    QLabel* _spellCostLabel;
    QLabel* _spellRequirementLabel;
    QLabel* _spellMaintenanceLabel;
    QLabel* _spellRMysLabel;
    QLabel* _spellRMysBoolLabel;
    QLabel* _spellCommentaireLabel;
    QLabel* _spellSourceLabel;
    QLabel* _spellEffectTypeLabel;

    // Champs
    QLineEdit* _spellName;
    QSpinBox* _spellLevel;
    QComboBox* _spellBook;
    QLineEdit* _spellDescription;
    QSpinBox* _spellCostInitial;
    QSpinBox* _spellCostIntermediaire;
    QSpinBox* _spellCostAvancee;
    QSpinBox* _spellCostArcane;
    QSpinBox* _spellRequirementInitial;
    QSpinBox* _spellRequirementIntermediaire;
    QSpinBox* _spellRequirementAvancee;
    QSpinBox* _spellRequirementArcane;
    QSpinBox* _spellMaintenanceInitial;
    QSpinBox* _spellMaintenanceIntermediaire;
    QSpinBox* _spellMaintenanceAvancee;
    QSpinBox* _spellMaintenanceArcane;
    QComboBox* _spellMaintenanceType;
    QSpinBox* _spellRMys;
    QComboBox* _spellRMysBool;
    QLineEdit* _spellCommentaire;
    QLineEdit* _spellSource;
    QLineEdit* _spellEffectType;

};

#endif // SPELLVIEW_H
