#include "SpellBookMainWindow.h"

#include <QFile>
#include <iostream>

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

    initToolBar();

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

void SpellBookMainWindow::initToolBar()
{
    QToolBar* toolBar = addToolBar(SPELLBOOK_TOOLBAR_NAME);
    toolBar->setObjectName(SPELLBOOK_TOOLBAR_NAME);
    QAction* addSpellAction = new QAction("Ajouter", this);
    addSpellAction->setStatusTip("Ajoute le sort à la liste personnalisée");
    toolBar->addAction(addSpellAction);

    QObject::connect(addSpellAction, SIGNAL(triggered(bool)), this, SLOT(addSpellButton()));

}

void SpellBookMainWindow::initCentralWidget()
{
    _centralWidget = new QTabWidget(this);
    _centralWidget->setObjectName(SPELLVIEWTAB);
    _centralWidget->setWindowTitle(SPELLVIEWTAB);
    _centralWidget->setTabsClosable(true);
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
    spellTreeExplorer->sort();
    spellTreeExplorer->setHeaderHidden(true);
    spellTreeExplorer->setReadOnly(true);

    hideRowSpellTreeView(spellTreeExplorer, true);

    _spellList = new QDockWidget(this);
    SpellTreeView* spellTreeList = new SpellTreeView(_spellList);
    _spellList->setWidget(spellTreeList);
    _spellList->setObjectName(SPELLLIST);
    _spellList->setWindowTitle(SPELLLIST);
    _spellList->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeList->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    addDockWidget(Qt::RightDockWidgetArea, _spellList);

    spellTreeList->loadTreeData("");
    spellTreeList->setMaxDepth(2);
    spellTreeList->sort();
    spellTreeList->setHeaderHidden(true);

    hideRowSpellTreeView(spellTreeList, true);

    spellTreeExplorer->setSiblingSpellTree(spellTreeList);
}

void SpellBookMainWindow::initConnections()
{
    QObject::connect(_spellExplorer->widget(), SIGNAL(clicked(QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
    QObject::connect(_spellList->widget(), SIGNAL(clicked(QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
    QObject::connect(_spellExplorer->widget(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addSpellViewExplorer(QModelIndex)));
    QObject::connect(_spellList->widget(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addSpellViewList(QModelIndex)));
    //QObject::connect(_spellExplorer->widget(), SIGNAL(customContextMenuRequested(QPoint)), _spellExplorer->widget(), SLOT(openTreeContextMenu(QPoint)));

    QObject::connect(_centralWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeSpellView(int)));
}

void SpellBookMainWindow::addSpellViewExplorer(const QModelIndex &index_)
{
    addSpellView((SpellTreeView*)_spellExplorer->widget(), index_, false);
    //test d'ajout
}

void SpellBookMainWindow::addSpellViewList(const QModelIndex &index_)
{
    addSpellView((SpellTreeView*)_spellList->widget(), index_, true);
}

SpellView* SpellBookMainWindow::addSpellView(SpellTreeView* treeView_, const QModelIndex &index_, bool enabled_)
{
    QAbstractItemModel* model = treeView_->model();
    if(model->hasChildren(index_) && model->index(0,0,index_).data().toString() == "name")
    {
        SpellView* spellView = new SpellView(_centralWidget);
        spellView->setEnabled(enabled_);
        spellView->loadData(index_, model);
        _centralWidget->addTab(spellView, spellView->getName());
        return spellView;
    }
    return NULL;
}

void SpellBookMainWindow::loadSpellPreview(const QModelIndex& index_)
{
    SpellTreeView* treeView = (SpellTreeView*)_spellExplorer->widget();
    QAbstractItemModel* model = treeView->model();

    if(model->hasChildren(index_) && model->index(0,0,index_).data().toString() == "name")
    {
        _spellPreview->loadData(index_, model);
    }

    _centralWidget->setCurrentIndex(0);
}

void SpellBookMainWindow::closeSpellView(const int &index_)
{
    if(index_ == 0)
    {
        return;
    }
    else
    {
        QWidget* p = _centralWidget->widget(index_);
        _centralWidget->removeTab(index_);
        p->deleteLater();
    }
}

void SpellBookMainWindow::addSpellButton()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->widget();
    treeList->addSpell((SpellView*)_centralWidget->currentWidget());
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
