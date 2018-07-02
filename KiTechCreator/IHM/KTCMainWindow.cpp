#include "KTCMainWindow.h"

#include <Socle/Constantes.h>
#include <KiTechCreator/IHM/TechniqueWidget.h>

KTCMainWindow::KTCMainWindow(QString styleSheet_) : QMainWindow()
{
        setWindowTitle(KTC_WINDOW_NAME);
        setTheme(styleSheet_);

        QWidget* mainWidget = new TechniqueWidget(this);
        setCentralWidget(mainWidget);

        setMinimumSize(this->centralWidget()->minimumSizeHint());
        setWindowState(Qt::WindowMinimized);
}

KTCMainWindow::~KTCMainWindow()
{

}

void KTCMainWindow::setTheme(QString styleSheet_)
{
    setStyleSheet(styleSheet_);
}
