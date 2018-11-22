#include "PartyManagerMainWindow.h"

#include <QToolBar>
#include <QToolButton>

#include <Socle/Constantes.h>

PartyManagerMainWindow::PartyManagerMainWindow(QString styleSheet_) : QMainWindow(),
  _centralWidget(nullptr)
{
  setWindowTitle(PARTY_MANAGER_WINDOW_NAME);
  setTheme(styleSheet_);
  setContextMenuPolicy(Qt::NoContextMenu);

  QPixmap pixmap(":/IMG/ANIMA_LOGO");
  QIcon icon(pixmap);
  setWindowIcon(icon);

  initCentralWidget();

  initDockWidgets();

  initToolBar();

  initConnections();

  setMinimumSize(_centralWidget->minimumSizeHint());
  setWindowState(Qt::WindowMinimized);
}

PartyManagerMainWindow::~PartyManagerMainWindow()
{
    if(_centralWidget != nullptr)
    {
        delete _centralWidget;
        _centralWidget = nullptr;
    }
}

void PartyManagerMainWindow::setTheme(QString styleSheet_)
{
    setStyleSheet(styleSheet_);
}

void PartyManagerMainWindow::initToolBar()
{
    QToolBar* toolBar = addToolBar(PARTY_MANAGER_TOOLBAR_NAME);
    toolBar->setObjectName(PARTY_MANAGER_TOOLBAR_NAME);

    QToolButton* changeThemeBouton = new QToolButton(this);
    changeThemeBouton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    changeThemeBouton->setIcon(QIcon(":/IMG/THEME"));
    changeThemeBouton->setMaximumWidth(TOOL_BUTTON_MAXIMUM_WIDTH);
    changeThemeBouton->setMinimumWidth(TOOL_BUTTON_MINIMUM_WIDTH);
    changeThemeBouton->setIconSize(QSize(TOOL_BUTTON_ICON_SIZE, TOOL_BUTTON_ICON_SIZE));
    changeThemeBouton->setToolTip("Active le mode Jour/Nuit");

    QWidget* spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacerWidget->setVisible(true);

    toolBar->addWidget(spacerWidget);
    toolBar->addWidget(changeThemeBouton);

    QObject::connect(changeThemeBouton, SIGNAL(pressed()), this, SIGNAL(changerThemeRequested()));
}

void PartyManagerMainWindow::initCentralWidget()
{
    _centralWidget = new QTabWidget(this);
    _centralWidget->setTabsClosable(true);
    setCentralWidget(_centralWidget);
}

void PartyManagerMainWindow::initDockWidgets()
{

}

void PartyManagerMainWindow::initConnections()
{

}
