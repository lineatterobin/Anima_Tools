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

#include <Librairies/Modeles/DomItem.h>
#include <SpellBook/Modeles/SpellEnum.h>

class SpellView : public QWidget
{
    Q_OBJECT
public:
    explicit SpellView(QWidget *parent = nullptr);

    ~SpellView();

    void setEnabled(const bool& value);
    void setReadOnly(const bool& value);

    void loadData(QModelIndex index_, const QAbstractItemModel *model_);

    QString getName();
    int getLevel();
    QString getBook();
    QString getDescription();
    int getCostInitial();
    int getCostIntermediaire();
    int getCostAvancee();
    int getCostArcane();
    int getRequirementInitial();
    int getRequirementIntermediaire();
    int getRequirementAvancee();
    int getRequirementArcane();
    int getMaintenanceInitial();
    int getMaintenanceIntermediaire();
    int getMaintenanceAvancee();
    int getMaintenanceArcane();
    int getMaintenanceType();
    QString getCommentaires();
    QString getSource();
    QString getEffectType();
    QString getEffectInitial();
    QString getEffectIntermediaire();
    QString getEffectAvancee();
    QString getEffectArcane();
    QString getAction();

signals:

    addSpellButtonClicked();
    nameChanged(SpellView*);

private slots:

    void updateTitle();

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
    QLabel* _spellCommentaireLabel;
    QLabel* _spellSourceLabel;
    QLabel* _spellEffectTypeLabel;
    QLabel* _spellEffectLabel;
    QLabel* _spellActionLabel;

    // Champs
    QLineEdit* _spellName;
    QSpinBox* _spellLevel;
    QLineEdit* _spellBook;
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
    QTextEdit* _spellCommentaire;
    QLineEdit* _spellSource;
    QComboBox* _spellEffectType;
    QTextEdit* _spellEffectInitial;
    QTextEdit* _spellEffectIntermediaire;
    QTextEdit* _spellEffectAvancee;
    QTextEdit* _spellEffectArcane;
    QComboBox* _spellAction;

};

#endif // SPELLVIEW_H
