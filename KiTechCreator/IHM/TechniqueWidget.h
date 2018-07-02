#ifndef TECHNIQUEWIDGET_H
#define TECHNIQUEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

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
    QLabel* _mkCostLabel;
    QLineEdit* _mkCost;

};

#endif // TECHNIQUEWIDGET_H
