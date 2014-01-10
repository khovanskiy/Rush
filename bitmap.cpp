#include "bitmap.h"

#include <QFile>

#include "console.h"

Bitmap::Bitmap()
{
    source = 0;
}

Bitmap::~Bitmap()
{
    delete source;
}

QImage* Bitmap::getSource() const
{
    return source;
}

void Bitmap::load(QString path)
{
    if (QFile::exists(path))
    {
        source = new QImage(path);
        _width = source->width();
        _height = source->height();
        dispatchEvent(Event(this, Event::COMPLETE));
    }
    else
    {
        source = new QImage(path);
        _width = source->width();
        _height = source->height();
        dispatchEvent(Event(this, Event::COMPLETE));
        Console::print(QString("Cant find the file: ") + path);
    }
}

void Bitmap::render(QPainter* render2d, const Matrix& base)
{
    if (source != 0)
    {
        Matrix current = Matrix::mul(*getLocalMatrix(), base);
        render2d->save();
        render2d->setMatrix(QMatrix());
        //render2d->setBrush(QBrush(QColor(0,255,0)));
        //render2d->drawRect(getRenderBounds());
        render2d->setMatrix(current.toQMatrix());
        render2d->drawImage(0, 0, *source);
        render2d->restore();
    }
}
