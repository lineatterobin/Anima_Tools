#include "BookSorting.h"

int BookSorting::compareBooks(const QString &book1_,const QString &book2_)
{
    int i1 = BOOK_ORDER.indexOf(book1_);
    int i2 = BOOK_ORDER.indexOf(book2_);

    if (i1 == -1 && i2 == -1)
    {
        return QString::compare(book1_, book2_);
    }
    else if (i1 == -1)
    {
        return 1;
    }
    else if (i2 == -1)
    {
        return -1;
    }
    else
    {
        return i1 - i2;
    }
}


