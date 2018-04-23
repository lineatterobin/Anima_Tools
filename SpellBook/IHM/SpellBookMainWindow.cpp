#include "SpellBookMainWindow.h"

#include <Socle/Constantes.h>

SpellBookMainWindow::SpellBookMainWindow(QString styleSheet_) : QMainWindow(),
    _centralWidget(NULL),
    _mainLayout(NULL),
    _toolBar(NULL),
    _spellViewWidget(NULL),
    _spellPreview(NULL)
{
    setWindowTitle(SPELLBOOK_WINDOW_NAME);

    setTheme(styleSheet_);

    //Initialisation du layout principal
    _mainLayout = new QVBoxLayout;

    initToolBar();

    initAllWidgets();

    initAllConnections();

    setWindowState(Qt::WindowMaximized);
    QPixmap pixmap(":/IMG/ANIMA_LOGO");
    QIcon icon(pixmap);
    setWindowIcon(icon);

    _centralWidget = new QWidget;
    _centralWidget->setLayout(_mainLayout);
    setCentralWidget(_centralWidget);
}

SpellBookMainWindow::~SpellBookMainWindow()
{

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

    _mainLayout->addWidget(_toolBar);
}

void SpellBookMainWindow::initAllWidgets()
{
    // SpellView
    addSpellViewWidget();

    // SpellList

    // SpellCustomList
}

void SpellBookMainWindow::initAllConnections()
{

}

void SpellBookMainWindow::addSpellViewWidget()
{
    _spellViewWidget = new QTabWidget(this);

    _spellViewWidget->setObjectName(SPELLVIEWTAB);
    _spellViewWidget->setWindowTitle(SPELLVIEWTAB);

    _spellPreview = new SpellView(this);
    _spellViewWidget->addTab(_spellPreview, "Preview");

    _mainLayout->addWidget(_spellViewWidget);
    _mainLayout->setAlignment(Qt::AlignCenter);

}
