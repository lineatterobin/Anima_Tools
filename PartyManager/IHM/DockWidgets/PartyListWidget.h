#ifndef PARTYLISTWIDGET_H
#define PARTYLISTWIDGET_H

#include <QDockWidget>
#include <QListWidget>

class PartyListWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit PartyListWidget(QWidget *parent_ = nullptr);

    QListWidget *listWidget() const;
    void setListWidget(QListWidget *listWidget);

private:

    QListWidget* _listWidget;
};

#endif // PARTYLISTWIDGET_H
