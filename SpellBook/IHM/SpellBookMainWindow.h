#ifndef SPELLBOOKMAINWINDOW_H
#define SPELLBOOKMAINWINDOW_H

#include <SpellBook/IHM/SpellView.h>
#include <SpellBook/IHM/SpellTreeView.h>

#include <QMainWindow>
#include <QToolBar>
#include <QVBoxLayout>
#include <QDockWidget>

class SpellBookMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // Constrcuteur et Destructeur
    explicit SpellBookMainWindow(QString styleSheet_);
    ~SpellBookMainWindow();

    /*!
     * \brief setTheme : affecte le stylesheet_ à la fenêtre.
     * \param styleSheet_
     */
    void setTheme(QString styleSheet_);

    /*!
     * \brief newSpellView : Crée une nouvelle SpellView dans le widget central.
     * \param readOnly_
     * \return SpellView*
     */
    SpellView *newSpellView(const bool &readOnly_);

    /*!
     * \brief addSpellView : Crée une nouvelle SpellView dans le widget central à partir des données d'un SpellTreeView.
     * \param treeView_
     * \param index_
     * \param readOnly_
     * \return SpellView*
     */
    SpellView *addSpellView(SpellTreeView* treeView_, const QModelIndex& index_, const bool &readOnly_);

signals:
    /*!
     * \brief changerThemeRequested : demande le changement du thème.
     */
    void changerThemeRequested();

public slots:

    /*!
     * \brief newSpellViewButton : slot relié au bouton d'ajout de SpellView.
     */
    void newSpellViewButton();

    /*!
     * \brief loadSpellPreview : Charge du sort selectionné dans la SpellView d'aperçu.
     * \param index_
     */
    void loadSpellPreview(const QModelIndex& index_);

    /*!
     * \brief addSpellViewExplorer : Ajoute une SpellView à partir des données du SpellTreeViewExplorer.
     * \param index_
     */
    void addSpellViewExplorer(const QModelIndex &index_);

    /*!
     * \brief addSpellViewList : Ajoute une SpellView à partir des données de la liste de sorts personnalisée.
     * \param index_
     */
    void addSpellViewList(const QModelIndex &index_);

    /*!
     * \brief closeSpellView : Fermeture d'une SpellView.
     * \param index_
     */
    void closeSpellView(const int& index_);

    /*!
     * \brief createSpellList : Crée une nouvelle liste personnalisée.
     */
    void createSpellList();

    /*!
     * \brief loadSpellList : Charge une liste personnalisée à partir d'un fichier XML.
     */
    void loadSpellList();

    /*!
     * \brief saveSpellList : Sauvegarde une liste personnalisée dans un fichier XML.
     */
    void saveSpellList();

    /*!
     * \brief saveAsSpellList : Comme saveSpellList mais provoque systématiquement le choix d'un fichier de sortie.
     */
    void saveAsSpellList();

    /*!
     * \brief addSpellButton : Ajoute le sort actuellement affiché à la liste personnalisée.
     */
    void addSpellButton();

    /*!
     * \brief updateTabName : Met à jour le nom de la SpellView en entrée.
     * \param spellView
     */
    void updateTabName(SpellView* spellView);

private:

    /*!
     * \brief initToolBar : Initialise la barre d'outils.
     */
    void initToolBar();

    /*!
     * \brief initCentralWidget : Initialise le widget central.
     */
    void initCentralWidget();

    /*!
     * \brief initDockWidgets : Initialise les DockWidgets (liste de sorts et liste personnalisée).
     */
    void initDockWidgets();

    /*!
     * \brief initConnections : Initialise les connections (SIGNAL and SLOT).
     */
    void initConnections();

    /*!
     * \brief sortTreeSpellView : Tri le SpellTreeView.
     * \param treeview_
     */
    void sortTreeSpellView(SpellTreeView* treeview_);

    QTabWidget* _centralWidget;
    QDockWidget* _spellExplorer;
    QList<QDockWidget*>* _spellList;
    SpellView* _spellPreview;

};

#endif // SPELLBOOKMAINWINDOW_H
