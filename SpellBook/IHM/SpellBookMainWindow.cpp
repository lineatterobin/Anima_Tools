#include "SpellBookMainWindow.h"

#include <Socle/Constantes.h>

SpellBookMainWindow::SpellBookMainWindow(QString styleSheet_) : QMainWindow(),
    _centralWidget(NULL),
    _spellPreview(NULL)
{
    setWindowTitle(SPELLBOOK_WINDOW_NAME);
    setTheme(styleSheet_);

    QPixmap pixmap(":/IMG/ANIMA_LOGO");
    QIcon icon(pixmap);
    setWindowIcon(icon);

    initCentralWidget();

    initDockWidgets();

    setMinimumSize(_centralWidget->minimumSizeHint());
    setWindowState(Qt::WindowMinimized);
}

SpellBookMainWindow::~SpellBookMainWindow()
{
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

void SpellBookMainWindow::initCentralWidget()
{
    _centralWidget = new QTabWidget(this);
    _centralWidget->setObjectName(SPELLVIEWTAB);
    _centralWidget->setWindowTitle(SPELLVIEWTAB);
    setCentralWidget(_centralWidget);
    _spellPreview = new SpellView(_centralWidget);
    _centralWidget->addTab(_spellPreview, "Preview");
    _centralWidget->setMinimumSize(_spellPreview->minimumSizeHint());
}

void SpellBookMainWindow::initDockWidgets()
{
    _spellExplorer = new QDockWidget(this);
    QTreeView* spellTreeExplorer = new QTreeView(this);
    _spellExplorer->setWidget(spellTreeExplorer);
    _spellExplorer->setObjectName(SPELLEXPLORER);
    _spellExplorer->setWindowTitle(SPELLEXPLORER);
    _spellExplorer->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeExplorer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    addDockWidget(Qt::LeftDockWidgetArea, _spellExplorer);

    _spellList = new QDockWidget(this);
    QTreeView* spellTreeList = new QTreeView(this);
    _spellList->setWidget(spellTreeList);
    _spellList->setObjectName(SPELLLIST);
    _spellList->setWindowTitle(SPELLLIST);
    _spellList->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeList->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    addDockWidget(Qt::RightDockWidgetArea, _spellList);
}

void SpellBookMainWindow::addSpellView(bool enabled_)
{
    SpellView spellView(_centralWidget);
    spellView.setEnabled(enabled_);
}
