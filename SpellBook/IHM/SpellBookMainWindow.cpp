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

    setMinimumSize(_centralWidget->minimumSizeHint()+(_spellExplorer->minimumSizeHint()*2));
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
        qDeleteAll(*_spellList);
        _spellList->clear();
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
    newSpellListAction->setToolTip("Crée une nouvelle liste personalisée.");

    QAction* loadSpellListAction = new QAction("Ouvrir", this);
    loadSpellListAction->setToolTip("Ouvre une liste personalisée.");

    QAction* saveSpellListAction = new QAction("Enregistrer", this);
    saveSpellListAction->setToolTip("Sauvegarde la liste personnalisée");

    QAction* saveAsSpellListAction = new QAction("Enregistrer sous", this);
    saveAsSpellListAction->setToolTip("Sauvegarde la liste personnalisée");

    QAction* newSpellViewAction = new QAction("Nouveau sort", this);
    newSpellViewAction->setToolTip("Ajoute un onglet de création de sort.");

    toolBar->addAction(newSpellListAction);
    toolBar->addAction(loadSpellListAction);
    toolBar->addAction(saveSpellListAction);
    toolBar->addAction(saveAsSpellListAction);
    toolBar->addSeparator();
    toolBar->addAction(newSpellViewAction);

    QObject::connect(newSpellListAction, SIGNAL(triggered(bool)), this, SLOT(createSpellList()));
    QObject::connect(loadSpellListAction, SIGNAL(triggered(bool)), this, SLOT(loadSpellList()));
    QObject::connect(saveSpellListAction, SIGNAL(triggered(bool)), this, SLOT(saveSpellList()));
    QObject::connect(saveAsSpellListAction, SIGNAL(triggered(bool)), this, SLOT(saveAsSpellList()));

    QObject::connect(newSpellViewAction, SIGNAL(triggered(bool)), this, SLOT(newSpellViewButton()));

}

void SpellBookMainWindow::initCentralWidget()
{
    _centralWidget = new QTabWidget(this);
    _centralWidget->setObjectName(SPELLVIEWTAB);
    _centralWidget->setWindowTitle(SPELLVIEWTAB);
    _centralWidget->setTabsClosable(true);
    setCentralWidget(_centralWidget);
    _spellPreview = new SpellView(_centralWidget);
    _centralWidget->addTab(_spellPreview, "Aperçu");
    _centralWidget->setMinimumSize(_spellPreview->minimumSizeHint());
}

void SpellBookMainWindow::initDockWidgets()
{
    _spellList = new QList<QDockWidget*>();
    QDockWidget* spellListElt = new QDockWidget(this);
    spellListElt->setObjectName("spellList_0");
    SpellTreeView* spellTreeList = new SpellTreeView(spellListElt);
    spellListElt->setWidget(spellTreeList);
    spellListElt->setWindowTitle(spellListElt->objectName());
    spellListElt->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeList->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    spellTreeList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    spellTreeList->setDragEnabled(true);
    spellTreeList->viewport()->setAcceptDrops(true);
    spellTreeList->setDropIndicatorShown(true);

    _spellList->append(spellListElt);
    addDockWidget(Qt::RightDockWidgetArea, (_spellList->first()));

    spellTreeList->loadTreeData("");
    spellTreeList->setHeaderHidden(true);
    spellTreeList->sort();


    _spellExplorer = new QDockWidget(this);
    SpellTreeView* spellTreeExplorer = new SpellTreeView(_spellExplorer);
    _spellExplorer->setWidget(spellTreeExplorer);
    _spellExplorer->setObjectName(SPELLEXPLORER);
    _spellExplorer->setWindowTitle(SPELLEXPLORER);
    _spellExplorer->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeExplorer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    spellTreeExplorer->setSelectionMode(QAbstractItemView::ExtendedSelection);
    spellTreeExplorer->setDragEnabled(true);
    spellTreeExplorer->viewport()->setAcceptDrops(true);
    spellTreeExplorer->setDropIndicatorShown(true);

    addDockWidget(Qt::LeftDockWidgetArea, _spellExplorer);

    spellTreeExplorer->loadTreeData(":/DATA/BOOK");
    spellTreeExplorer->setHeaderHidden(true);
    spellTreeExplorer->setReadOnly(true);
    spellTreeExplorer->sort();

    spellTreeExplorer->setSiblingSpellTree(spellTreeList);

    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::TopDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::West);
}

void SpellBookMainWindow::initConnections()
{
    SpellTreeView* explorer = (SpellTreeView*)_spellExplorer->widget();
    SpellTreeView* list = (SpellTreeView*)_spellList->first()->widget();
    QObject::connect(explorer->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
    QObject::connect(list->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
    QObject::connect(explorer, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addSpellViewExplorer(QModelIndex)));
    QObject::connect(explorer, SIGNAL(openRequest(QModelIndex)), this, SLOT(addSpellViewExplorer(QModelIndex)));
    QObject::connect(list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addSpellViewList(QModelIndex)));
    QObject::connect(list, SIGNAL(openRequest(QModelIndex)), this, SLOT(addSpellViewExplorer(QModelIndex)));

    QObject::connect(_spellPreview, SIGNAL(addSpellButtonClicked()), this, SLOT(addSpellButton()));

    QObject::connect(_centralWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeSpellView(int)));

}

void SpellBookMainWindow::newSpellViewButton()
{
    newSpellView(false);
}

SpellView* SpellBookMainWindow::newSpellView(const bool& readOnly_)
{
    SpellView* spellView = new SpellView(_centralWidget);
    spellView->setReadOnly(readOnly_);
    _centralWidget->addTab(spellView, "Nouveau");
    QObject::connect(spellView, SIGNAL(addSpellButtonClicked()), this, SLOT(addSpellButton()));
    QObject::connect(spellView, SIGNAL(nameChanged(SpellView*)), this, SLOT(updateTabName(SpellView*)));
    _centralWidget->setCurrentWidget(spellView);
    return spellView;
}

void SpellBookMainWindow::addSpellViewExplorer(const QModelIndex &index_)
{
    addSpellView((SpellTreeView*)_spellExplorer->widget(), index_, true);
}

void SpellBookMainWindow::addSpellViewList(const QModelIndex &index_)
{
    addSpellView((SpellTreeView*)_spellList->first()->widget(), index_, false);
}

SpellView* SpellBookMainWindow::addSpellView(SpellTreeView* treeView_, const QModelIndex &index_, const bool& readOnly_)
{
    QAbstractItemModel* model = treeView_->model();
    if(model->hasChildren(index_) && model->index(0,0,index_).data().toString() == "name")
    {
        SpellView* spellView = new SpellView(_centralWidget);
        spellView->setReadOnly(readOnly_);
        spellView->loadData(index_, model);
        _centralWidget->addTab(spellView, spellView->getName());
        QObject::connect(spellView, SIGNAL(addSpellButtonClicked()), this, SLOT(addSpellButton()));
        QObject::connect(spellView, SIGNAL(nameChanged(SpellView*)), this, SLOT(updateTabName(SpellView*)));
        _centralWidget->setCurrentWidget(spellView);
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
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setMinimumSize(250,150);
    msgBox.setText("Les données de la liste actuelle vont être remplacées.");
    msgBox.setInformativeText("Voulez-vous enregistrer la liste actuelle ?");
    QPushButton *save = msgBox.addButton("Enregistrer", QMessageBox::AcceptRole);
    QPushButton *discard = msgBox.addButton("Ignorer", QMessageBox::DestructiveRole);
    QPushButton *cancel = msgBox.addButton("Annuler", QMessageBox::RejectRole);
    msgBox.setDefaultButton(save);
    msgBox.exec();

    if(msgBox.clickedButton() == (QAbstractButton*)save)
    {
        // Save was clicked
        saveSpellList();
    }
    else if(msgBox.clickedButton() == (QAbstractButton*)discard)
    {
        // Don't Save was clicked
        ;;
    }
    else if(msgBox.clickedButton() == (QAbstractButton*)cancel)
    {
        // Cancel was clicked
        return;
    }
    else
    {
        // should never be reached
        return;
    }

    SpellTreeView* treeList = (SpellTreeView*)_spellList->first()->widget();
    treeList->model()->deleteLater();
    treeList->loadTreeData("");
    treeList->setHeaderHidden(true);
    treeList->sort();

}

void SpellBookMainWindow::loadSpellList()
{
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setMinimumSize(250,150);
    msgBox.setText("Les données de la liste actuelle vont être remplacées.");
    msgBox.setInformativeText("Voulez-vous enregistrer la liste actuelle ?");
    QPushButton *save = msgBox.addButton("Enregistrer", QMessageBox::AcceptRole);
    QPushButton *discard = msgBox.addButton("Ignorer", QMessageBox::DestructiveRole);
    QPushButton *cancel = msgBox.addButton("Annuler", QMessageBox::RejectRole);
    msgBox.setDefaultButton(save);
    msgBox.exec();

    if(msgBox.clickedButton() == (QAbstractButton*)save)
    {
        // Save was clicked
        saveSpellList();
    }
    else if(msgBox.clickedButton() == (QAbstractButton*)discard)
    {
        // Don't Save was clicked
        ;;
    }
    else if(msgBox.clickedButton() == (QAbstractButton*)cancel)
    {
        // Cancel was clicked
        return;
    }
    else
    {
        // should never be reached
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir une liste personalisée", STD_DOCUMENT_PATH, "XML Files (*.xml)");

    SpellTreeView* treeList = (SpellTreeView*)_spellList->first()->widget();
    treeList->model()->deleteLater();
    treeList->loadTreeData(fileName);
    treeList->setHeaderHidden(true);
    treeList->sort();

}

void SpellBookMainWindow::saveSpellList()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->first()->widget();
    QString fileName;
    if(treeList->xmlPath() == "")
        fileName = QFileDialog::getSaveFileName(this, "Enregistrer la liste personalisée", STD_DOCUMENT_PATH, "XML Files (*.xml)");
    else
        fileName = treeList->xmlPath();

    treeList->model()->save(fileName);
    treeList->setXmlPath(fileName);
}

void SpellBookMainWindow::saveAsSpellList()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->first()->widget();
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, "Enregistrer la liste personalisée", STD_DOCUMENT_PATH, "XML Files (*.xml)");

    treeList->model()->save(fileName);
    treeList->setXmlPath(fileName);
}

void SpellBookMainWindow::addSpellButton()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->first()->widget();
    treeList->addSpell((SpellView*)_centralWidget->currentWidget());
}

void SpellBookMainWindow::updateTabName(SpellView* spellView)
{
    int index = _centralWidget->indexOf(spellView);
    QString name = spellView->getName();
    if(name == "")
    {
        _centralWidget->setTabText(index, "Nouveau");
    }
    else
    {
        _centralWidget->setTabText(index, name);
    }
}
