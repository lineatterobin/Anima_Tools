#include "mainwindow.h"

#include <QPainter>

MainWindow::MainWindow() : QMainWindow()
{
    _btnTest = new QPushButton();
    _btnTest->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _btnTest->setText("TEST Bouton");
    _btnTest->setToolTip("Test");
    _btnTest->setObjectName("BTNTest");

    connect(_btnTest, SIGNAL(pressed()), this, SLOT(lower()));

    QWidget* mainWidget = new QWidget;
    _buttonslayout = new QGridLayout(mainWidget);
    _buttonslayout->addWidget(_btnTest, 8,8, Qt::AlignCenter);

    for(int i = 0; i < 16; i++)
        _buttonslayout->setColumnStretch(i, 1);
    for(int i = 0; i < 10; i++)
        _buttonslayout->setRowStretch(i, 1);

    setCentralWidget(mainWidget);

    resize(600, 400);
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
    QImage labelScaled = titre.scaledToWidth(width(), Qt::SmoothTransformation);
    painter.drawImage(width()/2 - labelScaled.width()/2 , height()/3 - labelScaled.height()/3, labelScaled);

}
