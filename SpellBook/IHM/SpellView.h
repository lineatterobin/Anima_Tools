#ifndef SPELLVIEW_H
#define SPELLVIEW_H

#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
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

    void setEnabled(const bool& value);

    void loadData(const QModelIndex& index_, QAbstractItemModel* model);

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
    QLabel* _spellMaintenanceTypeLabel;
    QLabel* _spellRMysLabel;
    QLabel* _spellCommentaireLabel;
    QLabel* _spellSourceLabel;
    QLabel* _spellEffectTypeLabel;
    QLabel* _spellEffectLabel;
    QLabel* _spellActionLabel;

    // Champs
    QLineEdit* _spellName;
    QSpinBox* _spellLevel;
    QComboBox* _spellBook;
    QTextEdit* _spellDescription;
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
    QTextEdit* _spellCommentaire;
    QLineEdit* _spellSource;
    QComboBox* _spellEffectType;
    QLineEdit* _spellEffectInitial;
    QLineEdit* _spellEffectIntermediaire;
    QLineEdit* _spellEffectAvancee;
    QLineEdit* _spellEffectArcane;
    QComboBox* _spellAction;

};

#endif // SPELLVIEW_H
