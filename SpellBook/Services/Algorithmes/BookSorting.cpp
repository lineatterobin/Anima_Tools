#include "BookSorting.h"

int BookSorting::compareBooks(const QString &book1_,const QString &book2_)
{
    int i1 = BOOK_ORDER.indexOf(book1_);
    int i2 = BOOK_ORDER.indexOf(book2_);

    if (i1 == -1 && i2 == -1)
    {
        // Les deux livres sont inconnus. On utilise l'ordre alphabétique.
        return QString::compare(book1_, book2_);
    }
    else if (i1 == -1)
    {
        // book1 est inconnu. On le cosidère plus grand que book2 (ie. placé après book2).
        return 1;
    }
    else if (i2 == -1)
    {
        // book2 est inconnu. On le cosidère plus grand que book1 (ie. placé après book1).
        return -1;
    }
    else
    {
        /*
         * Tri défini par BOOK_ORDER.
         * >0 si book1 est après book2 dans le classement.
         * ==0 si book1 == book2.
         * <0 si book1 est avant book2 dans le classement.
         */
        return i1 - i2;
    }
}


