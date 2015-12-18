#include "bitmap.h"

#include <QFile>
#include <QApplication>

std::map<QString, QImage*> Bitmap::cache;

Bitmap::Bitmap()
{
    source = 0;
}

void Bitmap::Invoke(const Event &event)
{
    if (event.type == Event::COMPLETE)
    {
        TextureLoader* loader = (TextureLoader*)(event.target);
        cache[source_path] = source = loader->getTexture();
        inner_size.x = source->width();
        inner_size.y = source->height();
        loader->removeEventListener(this);
        loader->deleteLater();
    }
}

Bitmap::~Bitmap()
{
    //delete source;
}

QImage* Bitmap::getSource() const
{
    return source;
}

void Bitmap::load(QString path)
{
    path = QApplication::applicationDirPath().append("/").append(path);
    source_path = path;
    if (QFile::exists(path))
    {
        if (!cache[path])
        {
            loader = new TextureLoader(path);
            loader->addEventListener(this);
            loader->start();
        }
        else
        {
            source = cache[source_path];
            inner_size.x = source->width();
            inner_size.y = source->height();
        }
    }
    else
    {
        Console::print(QString("Cant find the file: ") + path);
    }
}

void Bitmap::render(QPainter* render2d, const Matrix& base, bool t, double new_int)
{
    if (source != 0)
    {
        DisplayObject::render(render2d, base, t, new_int);

        Matrix current = Matrix::mul(getTransform(), base);

        *bounds = getBounds(current);

        render2d->save();
        render2d->setMatrix(QMatrix());
        render2d->setBrush(QBrush(QColor(0,255,0, 255)));

        //Console::print("BASE");
        //Console::print(base);
        /*Console::print(base);
        Console::print(Camera::gi()->getTransform());
        Console::print(getTransform());
        Console::print(current);*/
        //render2d->drawRect(*bounds);
        //Console::print("render bounds");
        //Console::print(render_bounds.top());
        //Console::print(render_bounds.bottom());
        render2d->setMatrix(current.toQMatrix());

        render2d->drawImage(0, 0, *source);
        //render2d->drawLine(0,0,0,100);
        //render2d->drawLine(0, 0, 0, 100);
        render2d->restore();
    }
}
