#ifndef SPELLDOCKWIDGET_H
#define SPELLDOCKWIDGET_H

#include <QDockWidget>

#include <SpellBook/Modeles/SpellEnum.h>
#include <SpellBook/IHM/SpellTreeView.h>

class SpellDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit SpellDockWidget(QWidget *parent = nullptr, int listCount_ = 0, SpellEnum::TreeTypes type_ = SpellEnum::CUSTOM, QString data_ = "");

    SpellTreeView* getTree();

signals:
    addSpellButtonClicked(SpellTreeView*);

private slots:
    void addSpellButtonClickedAction();

private:
    SpellTreeView* _treeView;
    SpellEnum::TreeTypes _type;
};

#endif // SPELLDOCKWIDGET_H
