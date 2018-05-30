#include "MainWindow.h"

#include <Socle/Constantes.h>

#include <QPainter>
#include <QLabel>
#include <QFile>
#include <QIcon>

MainWindow::MainWindow() : QMainWindow(),
    _spellBookWindow(NULL)
{
    // Chargement du style graphique.
    QFile file(":/CSS/THEME_ACCUEIL");
    if(file.open(QFile::ReadOnly))
    {
        _styleSheet = QString::fromLatin1(file.readAll());
        setStyleSheet(_styleSheet);

        setWindowIcon(QIcon(":/IMG/ANIMA_ICON"));

        //On ferme le fichier
        file.close();

        // Boutons
        _btnSpellBook= new QPushButton();
        _btnSpellBook->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _btnSpellBook->setText("Spell Book Editor");
        _btnSpellBook->setToolTip("Test");
        _btnSpellBook->setObjectName("BTNTest");

        connect(_btnSpellBook, SIGNAL(pressed()), this, SLOT(lancerSpellBook()));

        // Grille de boutons
        QWidget* mainWidget = new QWidget;
        _buttonsLayout = new QGridLayout(mainWidget);
        _buttonsLayout->addWidget(_btnSpellBook, 0,7, Qt::AlignCenter);

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
}

MainWindow::~MainWindow()
{
    if(_spellBookWindow != NULL)
    {
        delete _spellBookWindow;
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if(_spellBookWindow != NULL)
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
    if(_spellBookWindow == NULL || _spellBookWindow->isHidden())
    {
        delete _spellBookWindow;
        _spellBookWindow = new SpellBookMainWindow(_styleSheet);
        _spellBookWindow->show();
    }

    _spellBookWindow->raise();
    _spellBookWindow->activateWindow();
    _spellBookWindow->setWindowState(_spellBookWindow->windowState() & ~Qt::WindowMinimized);
}
