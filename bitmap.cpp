#include "bitmap.h"

#include <QFile>
#include <QApplication>

#include "console.h"

Bitmap::Bitmap()
{
    source = 0;
}

void Bitmap::Invoke(const Event &event)
{
    if (event.type == Event::COMPLETE)
    {
        TextureLoader* loader = (TextureLoader*)(event.target);
        source = loader->getTexture();
        inner_width = source->width();
        inner_height = source->height();
        loader->removeEventListener(this);
        loader->deleteLater();
    }
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
    path = QApplication::applicationDirPath().append("/").append(path);
    if (QFile::exists(path))
    {
        loader = new TextureLoader(path);
        loader->addEventListener(this);
        loader->start();
    }
    else
    {
        Console::print(QString("Cant find the file: ") + path);
    }
}

void Bitmap::render(QPainter* render2d, const Matrix& base, bool t, float new_int)
{
    if (source != 0)
    {
        DisplayObject::render(render2d, base, t, new_int);

        Matrix current = Matrix::mul(*getLocalMatrix(), base);

        render_bounds = getBounds(&current);

        render2d->save();
        render2d->setMatrix(QMatrix());
        render2d->setBrush(QBrush(QColor(0,255,0, 50)));
        render2d->drawRect(render_bounds);
        render2d->setMatrix(current.toQMatrix());
        render2d->drawImage(0, 0, *source);
        render2d->restore();
    }
}
