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
        Console::print("Cant find the file");
    }
}

void Bitmap::render(QPainter* render2d)
{
    if (source != 0)
    {
        render2d->save();
        render2d->setMatrix(*getRenderMatrix());
        render2d->drawImage(0, 0, *source);
        render2d->restore();
    }
}
