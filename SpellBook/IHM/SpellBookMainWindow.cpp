#include "SpellBookMainWindow.h"

#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <QMessageBox>
#include <QToolButton>
#include <QInputDialog>

#include <Socle/Constantes.h>
#include <SpellBook/Modeles/SpellTreeModel.h>

SpellBookMainWindow::SpellBookMainWindow(QString styleSheet_) : QMainWindow(),
    _centralWidget(NULL),
    _spellPreview(NULL),
    _listCount(0)
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

    setMinimumSize(_centralWidget->minimumSizeHint()+(_spellList->first()->minimumSizeHint()*2));
    setWindowState(Qt::WindowMinimized);
}

SpellBookMainWindow::~SpellBookMainWindow()
{
    if(_centralWidget != NULL)
    {
        delete _centralWidget;
        _centralWidget = NULL;
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
    newSpellListAction->setToolTip("Crée une nouvelle liste personalisée");

    QAction* loadSpellListAction = new QAction("Ouvrir", this);
    loadSpellListAction->setToolTip("Ouvre une liste personalisée");

    QAction* saveSpellListAction = new QAction("Enregistrer", this);
    saveSpellListAction->setToolTip("Sauvegarde la liste personnalisée");

    QAction* saveAsSpellListAction = new QAction("Enregistrer sous", this);
    saveAsSpellListAction->setToolTip("Sauvegarde la liste personnalisée");

    QAction* newSpellViewAction = new QAction("Nouveau sort", this);
    newSpellViewAction->setToolTip("Ajoute un onglet de création de sort");

    QToolButton* changeThemeBouton = new QToolButton(this);
    changeThemeBouton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    changeThemeBouton->setIcon(QIcon(":/IMG/THEME"));
    changeThemeBouton->setMaximumWidth(TOOL_BUTTON_MAXIMUM_WIDTH);
    changeThemeBouton->setMinimumWidth(TOOL_BUTTON_MINIMUM_WIDTH);
    changeThemeBouton->setIconSize(QSize(TOOL_BUTTON_ICON_SIZE, TOOL_BUTTON_ICON_SIZE));
    changeThemeBouton->setToolTip("Active le mode Jour/Nuit");


    toolBar->addAction(newSpellListAction);
    toolBar->addAction(loadSpellListAction);
    toolBar->addAction(saveSpellListAction);
    toolBar->addAction(saveAsSpellListAction);
    toolBar->addSeparator();
    toolBar->addAction(newSpellViewAction);

    QWidget* spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacerWidget->setVisible(true);

    toolBar->addWidget(spacerWidget);
    toolBar->addWidget(changeThemeBouton);


    QObject::connect(newSpellListAction, SIGNAL(triggered(bool)), this, SLOT(createSpellList()));
    QObject::connect(loadSpellListAction, SIGNAL(triggered(bool)), this, SLOT(loadSpellList()));
    QObject::connect(saveSpellListAction, SIGNAL(triggered(bool)), this, SLOT(saveSpellList()));
    QObject::connect(saveAsSpellListAction, SIGNAL(triggered(bool)), this, SLOT(saveAsSpellList()));

    QObject::connect(newSpellViewAction, SIGNAL(triggered(bool)), this, SLOT(newSpellViewButton()));

    QObject::connect(changeThemeBouton, SIGNAL(pressed()), this, SIGNAL(changerThemeRequested()));

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
    spellListElt->setObjectName(SPELLLIST + QString::number(_listCount));
    ++_listCount;
    SpellTreeView* spellTreeList = new SpellTreeView(spellListElt);
    spellListElt->setWidget(spellTreeList);
    spellListElt->setWindowTitle(spellListElt->objectName());
    spellListElt->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeList->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    spellTreeList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    spellTreeList->setDragEnabled(true);
    spellTreeList->viewport()->setAcceptDrops(true);
    spellTreeList->setDropIndicatorShown(true);

    spellTreeList->loadTreeData("");
    spellTreeList->setHeaderHidden(true);
    spellTreeList->sort();

    QDockWidget* spellExplorer = new QDockWidget(this);
    SpellTreeView* spellTreeExplorer = new SpellTreeView(spellExplorer);
    spellExplorer->setWidget(spellTreeExplorer);
    spellExplorer->setObjectName(SPELLEXPLORER);
    spellExplorer->setWindowTitle(SPELLEXPLORER);
    spellExplorer->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeExplorer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    spellTreeExplorer->setSelectionMode(QAbstractItemView::ExtendedSelection);
    spellTreeExplorer->setDragEnabled(true);
    spellTreeExplorer->viewport()->setAcceptDrops(true);
    spellTreeExplorer->setDropIndicatorShown(true);

    spellTreeExplorer->loadTreeData(":/DATA/BOOK");
    spellTreeExplorer->setHeaderHidden(true);
    spellTreeExplorer->setReadOnly(true);
    spellTreeExplorer->sort();

    _spellList->append(spellExplorer);
    _spellList->append(spellListElt);
    addDockWidget(Qt::RightDockWidgetArea, _spellList->at(1));
    addDockWidget(Qt::LeftDockWidgetArea, _spellList->at(0));

    // Définition des positions des Tabs
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::TopDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::West);

}

void SpellBookMainWindow::initConnections()
{
    SpellTreeView* explorer = (SpellTreeView*)_spellList->at(0)->widget();
    SpellTreeView* list = (SpellTreeView*)_spellList->at(1)->widget();
    QObject::connect(explorer->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
    QObject::connect(list->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
    QObject::connect(explorer, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addSpellView(QModelIndex)));
    QObject::connect(explorer, SIGNAL(openRequest(QModelIndex)), this, SLOT(addSpellView(QModelIndex)));
    QObject::connect(list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addSpellView(QModelIndex)));
    QObject::connect(list, SIGNAL(openRequest(QModelIndex)), this, SLOT(addSpellView(QModelIndex)));

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

SpellView* SpellBookMainWindow::addSpellView(QModelIndex index_)
{
    const QAbstractItemModel* model = index_.model();
    if(model->hasChildren(index_) && model->index(0,0,index_).data().toString() == "name")
    {
        SpellView* spellView = new SpellView(_centralWidget);
        spellView->setReadOnly(false);
        spellView->loadData(index_, model);
        _centralWidget->addTab(spellView, spellView->getName());
        QObject::connect(spellView, SIGNAL(addSpellButtonClicked()), this, SLOT(addSpellButton()));
        QObject::connect(spellView, SIGNAL(nameChanged(SpellView*)), this, SLOT(updateTabName(SpellView*)));
        _centralWidget->setCurrentWidget(spellView);
        return spellView;
    }
    return NULL;
}

void SpellBookMainWindow::loadSpellPreview(QModelIndex index_)
{
    const QAbstractItemModel* model = index_.model();

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
    bool ok;
    // Ask for birth date as a string.
    QString text = QInputDialog::getText(0, "Nouvelle liste", "Nom de la liste :", QLineEdit::Normal, "", &ok);
    if (ok)
    {
        QDockWidget* spellListElt = new QDockWidget(this);
        if(!text.isEmpty())
            spellListElt->setObjectName(text);
        else
        {
            spellListElt->setObjectName(SPELLLIST + QString::number(_listCount));
            ++_listCount;
        }
        SpellTreeView* spellTreeList = new SpellTreeView(spellListElt);
        spellListElt->setWidget(spellTreeList);
        spellListElt->setWindowTitle(spellListElt->objectName());
        spellListElt->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        spellTreeList->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        spellTreeList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        spellTreeList->setDragEnabled(true);
        spellTreeList->viewport()->setAcceptDrops(true);
        spellTreeList->setDropIndicatorShown(true);

        spellTreeList->loadTreeData("");
        spellTreeList->setHeaderHidden(true);
        spellTreeList->sort();

        _spellList->append(spellListElt);
        addDockWidget(Qt::RightDockWidgetArea, spellListElt);
        tabifyDockWidget(_spellList->at(1), spellListElt);
    }
    else
    {
        return;
    }

}

void SpellBookMainWindow::loadSpellList()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir une liste personalisée", STD_DOCUMENT_PATH, "XML Files (*.xml)");

    QDockWidget* spellListElt = new QDockWidget(this);
    SpellTreeView* spellTreeList = new SpellTreeView(spellListElt);
    spellListElt->setWidget(spellTreeList);
    spellListElt->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeList->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    spellTreeList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    spellTreeList->setDragEnabled(true);
    spellTreeList->viewport()->setAcceptDrops(true);
    spellTreeList->setDropIndicatorShown(true);

    spellTreeList->loadTreeData(fileName);
    spellTreeList->setHeaderHidden(true);
    spellTreeList->sort();
    spellListElt->setWindowTitle(spellListElt->objectName());

    _spellList->append(spellListElt);
    addDockWidget(Qt::RightDockWidgetArea, spellListElt);
    tabifyDockWidget(_spellList->at(1), spellListElt);
}

void SpellBookMainWindow::saveSpellList()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->at(1)->widget();
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
    SpellTreeView* treeList = (SpellTreeView*)_spellList->at(1)->widget();
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, "Enregistrer la liste personalisée", STD_DOCUMENT_PATH, "XML Files (*.xml)");

    treeList->model()->save(fileName);
    treeList->setXmlPath(fileName);
}

void SpellBookMainWindow::addSpellButton()
{
    SpellTreeView* treeList = (SpellTreeView*)_spellList->at(1)->widget();
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

QList<QDockWidget*> SpellBookMainWindow::getList()
{
    return *_spellList;
}
