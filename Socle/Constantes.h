#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <QString>
#include <QStandardPaths>

const QString VERSION = "0.6";
const QString VERSION_LIBELLE = "AnimaTools v" + VERSION;

const int DEFAULT_WIDTH = 500;
const int DEFAULT_HEIGHT = 200;

const QString SPELLBOOK_WINDOW_NAME = "Editeur de Grimoires";
const QString SPELLBOOK_TOOLBAR_NAME = "Barre d'outils";
const QString SPELLVIEWTAB = "Détails";
const QString SPELLEXPLORER = "Source";
const QString SPELLLIST= "Grimoire";

const QString KTC_WINDOW_NAME = "Editeur de Techniques de Ki";

const int TOOL_BUTTON_ICON_SIZE = 15;
const int TOOL_BUTTON_MINIMUM_WIDTH = 70;
const int TOOL_BUTTON_MAXIMUM_WIDTH = 70;


const QString STD_DOCUMENT_PATH = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first();

#endif // CONSTANTES_H
