#include "SpellBookMainWindow.h"

#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <QMessageBox>

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
        delete _spellExplorer->widget();
        delete _spellExplorer;
        _spellExplorer = NULL;
    }
    if(_spellList != NULL)
    {
        delete _spellList->widget();
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

    QAction* newSpellListAction = new QAction("Nouveau", this);
    newSpellListAction->setStatusTip("Crée une nouvelle liste personalisée.");

    QAction* loadSpellListAction = new QAction("Ouvrir", this);
    loadSpellListAction->setStatusTip("Ouvre une liste personalisée.");

    QAction* saveSpellListAction = new QAction("Enregistrer", this);
    saveSpellListAction->setStatusTip("Sauvegarde la liste personnalisée");

    QAction* saveAsSpellListAction = new QAction("Enregistrer sous", this);
    saveAsSpellListAction->setStatusTip("Sauvegarde la liste personnalisée");

    QAction* addSpellAction = new QAction("Ajouter", this);
    addSpellAction->setStatusTip("Ajoute le sort à la liste personnalisée");

    toolBar->addAction(newSpellListAction);
    toolBar->addAction(loadSpellListAction);
    toolBar->addAction(saveSpellListAction);
    toolBar->addAction(saveAsSpellListAction);
    toolBar->addAction(addSpellAction);

    QObject::connect(newSpellListAction, SIGNAL(triggered(bool)), this, SLOT(createSpellList()));
    QObject::connect(loadSpellListAction, SIGNAL(triggered(bool)), this, SLOT(loadSpellList()));
    QObject::connect(saveSpellListAction, SIGNAL(triggered(bool)), this, SLOT(saveSpellList()));
    QObject::connect(saveAsSpellListAction, SIGNAL(triggered(bool)), this, SLOT(saveAsSpellList()));
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
    spellTreeExplorer->setHeaderHidden(true);
    spellTreeExplorer->setReadOnly(true);
    spellTreeExplorer->sort();

    _spellList = new QDockWidget(this);
    SpellTreeView* spellTreeList = new SpellTreeView(_spellList);
    _spellList->setWidget(spellTreeList);
    _spellList->setObjectName(SPELLLIST);
    _spellList->setWindowTitle(SPELLLIST);
    _spellList->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeList->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    addDockWidget(Qt::RightDockWidgetArea, _spellList);

    spellTreeList->loadTreeData("");
    spellTreeList->setHeaderHidden(true);
    spellTreeList->sort();

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

void SpellBookMainWindow::createSpellList()
{
    QMessageBox msgBox;
    msgBox.setText("Les données de la liste actuelle vont être remplacées.");
    msgBox.setInformativeText("Voulez-vous enregistrer la liste actuelle ?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        saveSpellList();
        break;
    case QMessageBox::Discard:
        // Don't Save was clicked
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
        return;
        break;
    default:
        // should never be reached
        return;
        break;
    }

    SpellTreeView* treeList = (SpellTreeView*)_spellList->widget();
    treeList->model()->deleteLater();
    treeList->loadTreeData("");
    treeList->setHeaderHidden(true);
    treeList->sort();

}

void SpellBookMainWindow::loadSpellList()
{
    QMessageBox msgBox;
    msgBox.setText("Les données de la liste actuelle vont être remplacées.");
    msgBox.setInformativeText("Voulez-vous enregistrer la liste actuelle ?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        saveSpellList();
        break;
    case QMessageBox::Discard:
        // Don't Save was clicked
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
        return;
        break;
    default:
        // should never be reached
        return;
        break;
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir une liste personalisée", "", "XML Files (*.xml)");

    SpellTreeView* treeList = (SpellTreeView*)_spellList->widget();
    treeList->model()->deleteLater();
    treeList->loadTreeData(fileName);
    treeList->setHeaderHidden(true);
    treeList->sort();

}

void SpellBookMainWindow::saveSpellList()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->widget();
    QString fileName;
    if(treeList->xmlPath() == "")
        fileName = QFileDialog::getSaveFileName(this, "Enregistrer la liste personalisée", "NewList.xml", "XML Files (*.xml)");
    else
        fileName = treeList->xmlPath();


    treeList->model()->save(fileName);
}

void SpellBookMainWindow::saveAsSpellList()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->widget();
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, "Enregistrer la liste personalisée", "NewList.xml", "XML Files (*.xml)");

    treeList->model()->save(fileName);
}

void SpellBookMainWindow::addSpellButton()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->widget();
    treeList->addSpell((SpellView*)_centralWidget->currentWidget());
}
