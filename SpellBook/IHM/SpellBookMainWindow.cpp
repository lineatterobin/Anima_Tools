#include "SpellBookMainWindow.h"

#include <QFile>

#include <Socle/Constantes.h>
#include <SpellBook/Modeles/SpellTreeModel.h>

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

    initConnections();

    setMinimumSize(_centralWidget->minimumSizeHint()+_spellExplorer->minimumSizeHint()+_spellList->minimumSizeHint());
    setWindowState(Qt::WindowMinimized);
}

SpellBookMainWindow::~SpellBookMainWindow()
{
    if(_centralWidget != NULL)
    {
        delete _centralWidget;
        _centralWidget = NULL;
    }
    if(_spellExplorer != NULL)
    {
        delete _spellExplorer;
        _spellExplorer = NULL;
    }
    if(_spellList != NULL)
    {
        delete _spellList;
        _spellList = NULL;
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
    SpellTreeView* spellTreeExplorer = new SpellTreeView(_spellExplorer);
    _spellExplorer->setWidget(spellTreeExplorer);
    _spellExplorer->setObjectName(SPELLEXPLORER);
    _spellExplorer->setWindowTitle(SPELLEXPLORER);
    _spellExplorer->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeExplorer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    addDockWidget(Qt::LeftDockWidgetArea, _spellExplorer);

    spellTreeExplorer->loadTreeData(":/DATA/BOOK");
    spellTreeExplorer->setHeaderHidden(true);

    hideRowSpellTreeView(spellTreeExplorer, true);

    _spellList = new QDockWidget(this);
    SpellTreeView* spellTreeList = new SpellTreeView(_spellList);
    _spellList->setWidget(spellTreeList);
    _spellList->setObjectName(SPELLLIST);
    _spellList->setWindowTitle(SPELLLIST);
    _spellList->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeList->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    addDockWidget(Qt::RightDockWidgetArea, _spellList);
}

void SpellBookMainWindow::initConnections()
{
    QObject::connect((QTreeView*)_spellExplorer->widget(), SIGNAL(clicked(QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
}

void SpellBookMainWindow::addSpellView(bool enabled_)
{
    SpellView spellView(_centralWidget);
    spellView.setEnabled(enabled_);
}

void SpellBookMainWindow::loadSpellPreview(const QModelIndex& index_)
{
    QTreeView* treeView = (QTreeView*)_spellExplorer->widget();
    QAbstractItemModel* model = treeView->model();

    //model->data(index_.child(0,0))
    if(model->hasChildren(index_) && model->index(0,0,index_).data().toString() == "name")
    {
        _spellPreview->loadData(index_, model);
    }
}

void SpellBookMainWindow::hideRowSpellTreeView(SpellTreeView* treeview_, const bool& hasXMLHeader_)
{
    QModelIndex startIndex = treeview_->model()->index(0, 0);

    //On cache le header du fixhier XML.
    if(hasXMLHeader_)
        treeview_->setRowHidden(0, startIndex.parent(), true);

    //On cache les informations des sorts.
    treeview_->hideTreeSpellData(startIndex.parent());
}
