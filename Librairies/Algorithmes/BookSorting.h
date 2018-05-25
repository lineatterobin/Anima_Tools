#ifndef BOOKSORTING_H
#define BOOKSORTING_H

#include <QString>
#include <QStringList>

const QStringList BOOK_ORDER = { "Lumière",
                                 "Obscurité",
                                 "Création",
                                 "Destruction",
                                 "Feu",
                                 "Eau",
                                 "Terre",
                                 "Air",
                                 "Essence",
                                 "Nécromancie",
                                 "Chaos",
                                 "Guerre",
                                 "Literae",
                                 "Mort",
                                 "Musique",
                                 "Noblesse",
                                 "Paix",
                                 "Péché",
                                 "Connaissance",
                                 "Sang",
                                 "Songes",
                                 "Temps",
                                 "Seuil",
                                 "Vide",
                                 "Accès Libre"
                               };

class BookSorting
{
public:
    static int compareBooks(const QString &book1_, const QString &book2_);
};

#endif // BOOKSORTING_H
