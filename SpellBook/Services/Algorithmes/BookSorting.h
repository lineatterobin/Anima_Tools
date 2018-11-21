#ifndef BOOKSORTING_H
#define BOOKSORTING_H

#include <QString>
#include <QStringList>

const QStringList BOOK_ORDER = { "Lumière",
                                 "Obscurité",
                                 "Création",
                                 "Destruction",
                                 "Air",
                                 "Eau",
                                 "Feu",
                                 "Terre",
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

/*!
 * \brief La classe BookSorting permet de trier les livres d'après un ordre spécifique.
 */
class BookSorting
{
public:
    /*!
     * \brief compareBooks compare deux livres
     * \param book1_
     * \param book2_
     * \return entier positif, négatif ou nul suivant la comparaison.
     */
    static int compareBooks(const QString &book1_, const QString &book2_);
};

#endif // BOOKSORTING_H
