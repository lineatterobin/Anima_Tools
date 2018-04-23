#include "SpellBookMainWindow.h"

#include <Socle/Constantes.h>
#include <SpellBook/IHM/SpellView.h>
#include <QToolBar>
#include <QVBoxLayout>

SpellBookMainWindow::SpellBookMainWindow(QString styleSheet_) : QMainWindow()
{
    setWindowTitle(SPELLBOOK_WINDOW_NAME);

    setTheme(styleSheet_);

    initToolBar();

    initAllWidgets();

    initAllConnections();

    setWindowState(Qt::WindowMaximized);
    QPixmap pixmap(":/IMG/ANIMA_LOGO");
    QIcon icon(pixmap);
    setWindowIcon(icon);
}

void SpellBookMainWindow::setTheme(QString styleSheet_)
{
    setStyleSheet(styleSheet_);
}

void SpellBookMainWindow::initToolBar()
{
    // Création de la barre d'outils.
    _toolBar= new QToolBar("ToolBar");
    _toolBar->setObjectName(SPELLBOOK_TOOLBAR_NAME);
    _toolBar->toggleViewAction()->setVisible(true);
    _toolBar->setIconSize(QSize(TOOL_BUTTON_ICON_SIZE, TOOL_BUTTON_ICON_SIZE));
}

void SpellBookMainWindow::initAllWidgets()
{
//    QVBoxLayout *layout = new QVBoxLayout;

//    QTabWidget *onglets = new QTabWidget(this);

//    SpellView *page1 = new SpellView;
//    SpellView *page2 = new SpellView;

//    onglets->addTab(page1, "Spell1");
//    onglets->addTab(page2, "Spell2");

//    layout->addWidget(onglets);
//    setCentralWidget(new QWidget);
//    centralWidget()->setLayout(layout);
//    this->layout()->setSizeConstraint(QLayout::SetMinimumSize);

//    onglets->setMaximumSize(this->size());
}

void SpellBookMainWindow::initAllConnections()
{

}
