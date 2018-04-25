#include "SpellBookMainWindow.h"

#include <Socle/Constantes.h>
#include <iostream>

SpellBookMainWindow::SpellBookMainWindow(QString styleSheet_) : QMainWindow(),
    _centralWidget(NULL),
    _spellPreview(NULL)
{
    setWindowTitle(SPELLBOOK_WINDOW_NAME);

    setTheme(styleSheet_);

    QPixmap pixmap(":/IMG/ANIMA_LOGO");
    QIcon icon(pixmap);
    setWindowIcon(icon);

    _centralWidget = new QTabWidget;
    _centralWidget->setObjectName(SPELLVIEWTAB);
    _centralWidget->setWindowTitle(SPELLVIEWTAB);
    setCentralWidget(_centralWidget);

    _spellPreview = new SpellView;
    _centralWidget->addTab(_spellPreview, "Preview");
    _centralWidget->setMinimumSize(_spellPreview->minimumSizeHint());

    setMinimumSize(_centralWidget->minimumSizeHint());
    setWindowState(Qt::WindowMinimized);
}

SpellBookMainWindow::~SpellBookMainWindow()
{
    if(_spellPreview != NULL)
    {
        _spellPreview->close();
        delete _spellPreview;
        _spellPreview = NULL;
    }
    if(_centralWidget != NULL)
    {
        delete _centralWidget;
        _centralWidget = NULL;
    }
}

void SpellBookMainWindow::setTheme(QString styleSheet_)
{
    setStyleSheet(styleSheet_);
}

void SpellBookMainWindow::initToolBar()
{

}

void SpellBookMainWindow::initAllWidgets()
{

}

void SpellBookMainWindow::initAllConnections()
{

}

void SpellBookMainWindow::addSpellView()
{

}
