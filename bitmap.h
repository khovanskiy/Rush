#ifndef BITMAP_H
#define BITMAP_H

#include <QImage>
#include <QPainter>
#include "event.h"
#include "interactiveobject.h"

class Bitmap : public InteractiveObject
{
public:
    Bitmap();
    ~Bitmap();
    QImage* getSource() const;
    void load(QString);
    void render(QPainter*, const Matrix&);
private:
    QImage* source;
};

#endif // BITMAP_H
