#include "SpellBookMainWindow.h"

#include <QFile>
#include <iostream>

#include <Socle/Constantes.h>
#include <SpellBook//Modeles/SpellTreeModel.h>

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
    QTreeView* spellTreeExplorer = new QTreeView(_spellExplorer);
    _spellExplorer->setWidget(spellTreeExplorer);
    _spellExplorer->setObjectName(SPELLEXPLORER);
    _spellExplorer->setWindowTitle(SPELLEXPLORER);
    _spellExplorer->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    spellTreeExplorer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    addDockWidget(Qt::LeftDockWidgetArea, _spellExplorer);

    loadTreeData(spellTreeExplorer, ":/DATA/BOOK");
    spellTreeExplorer->setHeaderHidden(true);

    QModelIndex startIndex = spellTreeExplorer->model()->index(0, 0);
    //On cache le header du fixhier XML.
    spellTreeExplorer->setRowHidden(0, startIndex.parent(), true);
    //On cache les informations des sorts.
    hideTreeSpellData(spellTreeExplorer, startIndex.parent());

    _spellList = new QDockWidget(this);
    QTreeView* spellTreeList = new QTreeView(_spellList);
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

void SpellBookMainWindow::loadTreeData(QTreeView* treeView_, QString xmlPath_)
{
    if (!xmlPath_.isEmpty()) {
        QFile file(xmlPath_);
        if (file.open(QIODevice::ReadOnly)) {
            QDomDocument document;
            if (document.setContent(&file)) {
                SpellTreeModel *newModel = new SpellTreeModel(document, this);
                treeView_->setModel(newModel);
            }
            file.close();
        }
    }
}

void SpellBookMainWindow::hideTreeSpellData(QTreeView* treeView_, const QModelIndex& startIndex_, int currentDepth_)
{
    QAbstractItemModel* model = treeView_->model();
    int childCount = model->rowCount(startIndex_);

    for(int i = 0; i< childCount; ++i)
    {
        if(currentDepth_ < 3)
        {
            // On descent d'un niveau.
            hideTreeSpellData(treeView_, model->index(i,0,startIndex_), currentDepth_ + 1);
        }
        else
        {
            //Niveau du sort : On cache les informations des niveaux inférieurs.
            treeView_->setRowHidden(i, startIndex_, true);
        }
    }

}

void SpellBookMainWindow::loadSpellPreview(const QModelIndex& index_)
{
    QTreeView* treeView = (QTreeView*)_spellExplorer->widget();
    QAbstractItemModel* model = treeView->model();

    std::cout << model->data(index_).toString().toStdString() << std::endl;
    QVariant data = model->data(index_);

    //model->data(index_.child(0,0))
    if(model->hasChildren(index_) && model->index(0,0,index_).data().toString() == "name")
    {
        std::cout << "Chargement de " << model->data(index_).toString().toStdString() << std::endl;
        _spellPreview->loadData(index_, model);
    }
}
