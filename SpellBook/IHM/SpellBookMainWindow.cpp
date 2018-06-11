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
    _spellList = new QList<SpellDockWidget*>();

    SpellDockWidget* spellExplorer = new SpellDockWidget(this, _listCount, SpellEnum::SOURCE, ":/DATA/BOOK");
    ++_listCount;

    SpellDockWidget* spellListElt = new SpellDockWidget(this, _listCount, SpellEnum::CUSTOM, "");
    QObject::connect(spellListElt, SIGNAL(addSpellButtonClicked(SpellTreeView*)), this, SLOT(addSpellButton(SpellTreeView*)));
    ++_listCount;

    _spellList->append(spellExplorer);
    _spellList->append(spellListElt);
    addDockWidget(Qt::LeftDockWidgetArea, _spellList->at(0));
    addDockWidget(Qt::RightDockWidgetArea, _spellList->at(1));

    // Définition des positions des Tabs
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::TopDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::West);

}

void SpellBookMainWindow::initConnections()
{
    SpellTreeView* explorer = _spellList->at(0)->getTree();
    SpellTreeView* list = _spellList->at(1)->getTree();
    QObject::connect(explorer->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
    QObject::connect(list->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(loadSpellPreview(QModelIndex)));
    QObject::connect(explorer, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addSpellView(QModelIndex)));
    QObject::connect(explorer, SIGNAL(openRequest(QModelIndex)), this, SLOT(addSpellView(QModelIndex)));
    QObject::connect(list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addSpellView(QModelIndex)));
    QObject::connect(list, SIGNAL(openRequest(QModelIndex)), this, SLOT(addSpellView(QModelIndex)));

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
    QString text = QInputDialog::getText(0, "Nouvelle liste", "Nom de la liste :", QLineEdit::Normal, "", &ok);
    if (ok)
    {
        SpellDockWidget* spellListElt = new SpellDockWidget(this, _listCount);
        ++_listCount;
        if(!text.isEmpty())
        {
            spellListElt->setObjectName(text);
        }
        spellListElt->setWindowTitle(spellListElt->objectName());

        _spellList->append(spellListElt);
        addDockWidget(Qt::RightDockWidgetArea, spellListElt);
        tabifyDockWidget(_spellList->at(1), spellListElt);
        QObject::connect(spellListElt, SIGNAL(addSpellButtonClicked(SpellTreeView*)), this, SLOT(addSpellButton(SpellTreeView*)));
    }
    else
    {
        return;
    }

}

void SpellBookMainWindow::loadSpellList()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir une liste personalisée", STD_DOCUMENT_PATH, "XML Files (*.xml)");

    SpellDockWidget* spellListElt = new SpellDockWidget(this, _listCount, SpellEnum::CUSTOM, fileName);
    ++_listCount;

    spellListElt->setWindowTitle(spellListElt->objectName());

    _spellList->append(spellListElt);
    addDockWidget(Qt::RightDockWidgetArea, spellListElt);
    tabifyDockWidget(_spellList->at(1), spellListElt);
    QObject::connect(spellListElt, SIGNAL(addSpellButtonClicked(SpellTreeView*)), this, SLOT(addSpellButton(SpellTreeView*)));
}

void SpellBookMainWindow::saveSpellList()
{
    SpellTreeView* treeList = _spellList->at(1)->getTree();
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
    SpellTreeView* treeList = _spellList->at(1)->getTree();
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, "Enregistrer la liste personalisée", STD_DOCUMENT_PATH, "XML Files (*.xml)");

    treeList->model()->save(fileName);
    treeList->setXmlPath(fileName);
}

void SpellBookMainWindow::addSpellButton(SpellTreeView* treeView_)
{
    treeView_->addSpell((SpellView*)_centralWidget->currentWidget());
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

QList<SpellDockWidget*> SpellBookMainWindow::getList()
{
    return *_spellList;
}
