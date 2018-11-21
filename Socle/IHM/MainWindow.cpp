#include "MainWindow.h"

#include <Socle/Constantes.h>

#include <QPainter>
#include <QLabel>
#include <QFile>
#include <QIcon>

MainWindow::MainWindow() : QMainWindow(),
    _spellBookWindow(nullptr)
{
    // Chargement du style graphique.
    QFile file(":/CSS/THEME_JOUR");
    if(file.open(QFile::ReadOnly))
    {
        _styleSheet = QString::fromLatin1(file.readAll());
        setStyleSheet(_styleSheet);

        _theme = Theme::JOUR;
    }
    //On ferme le fichier
    file.close();

    // Boutons
    _btnSpellBook= new QPushButton();
    _btnSpellBook->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _btnSpellBook->setText("Editeur de Grimoire");

    connect(_btnSpellBook, SIGNAL(pressed()), this, SLOT(lancerSpellBook()));

    _btnPartyManager= new QPushButton();
    _btnPartyManager->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _btnPartyManager->setText("Gestionnaire de groupe");

    connect(_btnPartyManager, SIGNAL(pressed()), this, SLOT(lancerPartyManager()));

    // Grille de boutons
    QWidget* mainWidget = new QWidget();
    mainWidget->setObjectName("MainWidget");
    _buttonsLayout = new QGridLayout(mainWidget);
    _buttonsLayout->addWidget(_btnSpellBook, 0,7, Qt::AlignCenter);
    _buttonsLayout->addWidget(_btnPartyManager, 1,7, Qt::AlignCenter);

    // Version
    QLabel* versionLabel = new QLabel(VERSION_LIBELLE, this);
    versionLabel->setObjectName("Version");
    _buttonsLayout->addWidget(versionLabel, 8, 0, Qt::AlignBottom);

    // Création des lignes et colonnes de la grille de boutons
    for(int i = 0; i < 9; i++)
        _buttonsLayout->setColumnStretch(i, 1);
    for(int i = 0; i < 9; i++)
        _buttonsLayout->setRowStretch(i, 1);

    // Ajout du Widget à la fenêtre principale.
    setCentralWidget(mainWidget);

    // Réglage de la taille de la fenêtre.
    resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

MainWindow::~MainWindow()
{
    if(_spellBookWindow != nullptr)
    {
        delete _spellBookWindow;
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if(_spellBookWindow != nullptr)
        _spellBookWindow->close();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    // Création et initialisation des images.
    QImage titre;
    titre.load(":/IMG/ANIMA_LOGO");

    // Initialisation des obets permettant de dessiner.
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(175,160,97), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    // Titre
    QImage labelScaled = titre.scaledToWidth(2*width()/3, Qt::SmoothTransformation);
    painter.drawImage(0*width()/2 - 0*labelScaled.width()/2 , 0*height()/2 - 0*labelScaled.height()/2, labelScaled);

}

void MainWindow::lancerSpellBook()
{
    if(_spellBookWindow == nullptr || _spellBookWindow->isHidden())
    {
        delete _spellBookWindow;
        _spellBookWindow = new SpellBookMainWindow(_styleSheet);
        _spellBookWindow->show();
    }

    _spellBookWindow->raise();
    _spellBookWindow->activateWindow();
    _spellBookWindow->setWindowState(_spellBookWindow->windowState() & ~Qt::WindowMinimized);

    connect(_spellBookWindow, SIGNAL(changerThemeRequested()), this, SLOT(changerTheme()));
}

void MainWindow::lancerPartyManager()
{
    if(_partyManagerWindow == nullptr || _partyManagerWindow->isHidden())
    {
        delete _partyManagerWindow;
        _partyManagerWindow = new PartyManagerMainWindow(_styleSheet);
        _partyManagerWindow->show();
    }

    _partyManagerWindow->raise();
    _partyManagerWindow->activateWindow();
    _partyManagerWindow->setWindowState(_partyManagerWindow->windowState() & ~Qt::WindowMinimized);

    connect(_partyManagerWindow, SIGNAL(changerThemeRequested()), this, SLOT(changerTheme()));
}

void MainWindow::changerTheme()
{
    if (_theme == Theme::JOUR)
    {
        QFile file(":/CSS/THEME_NUIT");
        if(file.open(QFile::ReadOnly))
        {
            _styleSheet = QString::fromLatin1(file.readAll());
            setStyleSheet(_styleSheet);

            _theme = Theme::NUIT;
        }
        file.close();
    }
    else
    {
        QFile file(":/CSS/THEME_JOUR");
        if(file.open(QFile::ReadOnly))
        {
            _styleSheet = QString::fromLatin1(file.readAll());
            setStyleSheet(_styleSheet);

            _theme = Theme::JOUR;
        }
        file.close();
    }

    // On met à jour les modules s'ils existent.
    if(_spellBookWindow != nullptr)
        _spellBookWindow->setTheme(_styleSheet);
}
