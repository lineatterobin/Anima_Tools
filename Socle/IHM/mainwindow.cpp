#include "mainwindow.h"

#include <Socle/Constantes.h>

#include <QPainter>
#include <QLabel>
#include <QFile>

MainWindow::MainWindow() : QMainWindow()
{
    // Chargement du style graphique.
    QFile file(":/CSS/THEME_ACCUEIL");
    if(file.open(QFile::ReadOnly))
    {
        QString styleSheet = QString::fromLatin1(file.readAll());
        setStyleSheet(styleSheet);

        //On ferme le fichier
        file.close();

        // Boutons
        _btnTest = new QPushButton();
        _btnTest->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _btnTest->setText("Spell Book Editor");
        _btnTest->setToolTip("Test");
        _btnTest->setObjectName("BTNTest");

        connect(_btnTest, SIGNAL(pressed()), this, SLOT(lower()));

        // Grille de boutons
        QWidget* mainWidget = new QWidget;
        _buttonsLayout = new QGridLayout(mainWidget);
        _buttonsLayout->addWidget(_btnTest, 0,7, Qt::AlignCenter);

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
