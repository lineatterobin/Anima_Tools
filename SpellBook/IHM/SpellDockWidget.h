#ifndef SPELLDOCKWIDGET_H
#define SPELLDOCKWIDGET_H

#include <QDockWidget>
#include <QString>
#include <QCloseEvent>

#include <SpellBook/Modeles/SpellEnum.h>
#include <SpellBook/IHM/SpellTreeView.h>

class SpellDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    SpellDockWidget(QWidget *parent = nullptr, SpellEnum::TreeTypes type_ = SpellEnum::CUSTOM, QString data_ = "");
    SpellDockWidget(QString name_, QWidget *parent = nullptr);

    SpellTreeView* getTree();

    QLabel *getFileNameLabel() const;

signals:
    addSpellButtonClicked(SpellTreeView*);
    closeRequest(SpellDockWidget*);

private slots:
    void addSpellButtonClickedAction();
    void refreshFileNameLabel();
    void fileNameLabelModified();
    void fileNameLabelSaved();

protected:
    void closeEvent(QCloseEvent *event_);

private:
    QLabel* _fileNameLabel;
    SpellTreeView* _treeView;
    SpellEnum::TreeTypes _type;
};

#endif // SPELLDOCKWIDGET_H
