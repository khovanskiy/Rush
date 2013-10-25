#ifndef MATRIX_H
#define MATRIX_H

#include <QMatrix>

class Matrix
{
public:
    Matrix();
    QMatrix toQMatrix();
    double M11;
    double M12;
    double M21;
    double M22;
};

#endif // MATRIX_H
