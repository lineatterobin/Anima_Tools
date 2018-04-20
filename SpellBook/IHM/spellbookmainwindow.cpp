#include "spellbookmainwindow.h"

#include <Socle/constantes.h>

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

}

void SpellBookMainWindow::initAllWidgets()
{

}

void SpellBookMainWindow::initAllConnections()
{

}
