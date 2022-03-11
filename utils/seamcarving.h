#ifndef SEAMCARVING_H
#define SEAMCARVING_H

#include <QImage>

#define BORDER_ENERGY 10000

class SeamCarving
{
public:
    static int *findHorizontalSeam(QImage *);
    static int *findVerticalSeam(QImage *);

    static QImage removeHorizontalSeam(QImage *, int *);
    static QImage removeVerticalSeam(QImage *, int *);

    static double energy(QImage *, int, int);

private:
};

#endif // SEAMCARVING_H
