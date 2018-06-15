#include "MainWindow.h"

#include <Socle/Constantes.h>

#include <QPainter>
#include <QLabel>
#include <QFile>
#include <QIcon>

MainWindow::MainWindow() : QMainWindow(),
    _spellBookWindow(NULL),
    _ktcMainWindow(NULL)
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
    QPushButton* btnSpellBook= new QPushButton();
    btnSpellBook->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnSpellBook->setText(SPELLBOOK_WINDOW_NAME);

    QPushButton* btnKTC = new QPushButton(this);
    btnKTC->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnKTC->setText(KTC_WINDOW_NAME);

    connect(btnSpellBook, SIGNAL(pressed()), this, SLOT(lancerSpellBook()));
    connect(btnKTC, SIGNAL(pressed()), this, SLOT(lancerKTC()));

    // Grille de boutons
    QWidget* mainWidget = new QWidget();
    mainWidget->setObjectName("MainWidget");
    QGridLayout* buttonsLayout = new QGridLayout(mainWidget);
    buttonsLayout->addWidget(btnSpellBook, 0,7, Qt::AlignLeft);
    buttonsLayout->addWidget(btnKTC, 2,7, Qt::AlignLeft);

    // Version
    QLabel* versionLabel = new QLabel(VERSION_LIBELLE, this);
    versionLabel->setObjectName("Version");
    buttonsLayout->addWidget(versionLabel, 8, 0, Qt::AlignBottom);

    // Création des lignes et colonnes de la grille de boutons
    for(int i = 0; i < 9; i++)
        buttonsLayout->setColumnStretch(i, 1);
    for(int i = 0; i < 9; i++)
        buttonsLayout->setRowStretch(i, 1);

    // Ajout du Widget à la fenêtre principale.
    setCentralWidget(mainWidget);

    // Réglage de la taille de la fenêtre.
    resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

MainWindow::~MainWindow()
{
    if(_spellBookWindow != NULL)
    {
        delete _spellBookWindow;
    }
    if(_ktcMainWindow != NULL)
    {
        delete _ktcMainWindow;
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if(_spellBookWindow != NULL)
        _spellBookWindow->close();
    if(_ktcMainWindow != NULL)
        _ktcMainWindow->close();
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
    if(_spellBookWindow == NULL || _spellBookWindow->isHidden())
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

void MainWindow::lancerKTC()
{
    if(_ktcMainWindow == NULL || _ktcMainWindow->isHidden())
    {
        delete _ktcMainWindow;
        _ktcMainWindow = new KTCMainWindow(_styleSheet);
        _ktcMainWindow->show();
    }

    _ktcMainWindow->raise();
    _ktcMainWindow->activateWindow();
    _ktcMainWindow->setWindowState(_ktcMainWindow->windowState() & ~Qt::WindowMinimized);

    connect(_ktcMainWindow, SIGNAL(changerThemeRequested()), this, SLOT(changerTheme()));
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
    if(_spellBookWindow != NULL)
        _spellBookWindow->setTheme(_styleSheet);
    if(_ktcMainWindow != NULL)
        _ktcMainWindow->setTheme(_styleSheet);
}
