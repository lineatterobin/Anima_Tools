#ifndef TECHNIQUEWIDGET_H
#define TECHNIQUEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>

#include <KiTechCreator/Modeles/KiTechEnum.h>

class TechniqueWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TechniqueWidget(QWidget *parent = nullptr);
    ~TechniqueWidget();

signals:

public slots:

private:
    QLabel* _nameLabel;
    QLineEdit* _name;
    QLabel* _levelLabel;
    QLineEdit* _level;
    QLabel* _diCostLabel;
    QLineEdit* _diCost;
    QLabel* _typeLabel;
    QLineEdit* _type;

    QCheckBox* _combinable;
    QComboBox* _maintenanceType;

};

#endif // TECHNIQUEWIDGET_H
