#ifndef BITMAP_H
#define BITMAP_H

#include <QImage>
#include <QPainter>
#include <QString>
#include <map>
#include "../common/event.h"
#include "interactiveobject.h"
#include "QThread"
#include "../common/console.h"

class TextureLoader : public QObject, public EventDispatcher
{
    Q_OBJECT
public:
    TextureLoader(QString path)
    {
        this->path = path;
        thread = new QThread();
        QObject::connect(thread, SIGNAL(started()), this, SLOT(run()));
        texture = 0;
    }

    ~TextureLoader()
    {
        thread->deleteLater();
    }

    void start()
    {
        this->moveToThread(thread);
        thread->start();
    }

    QImage* getTexture()
    {
        return texture;
    }

public slots:
    void run()
    {
        QImage* temp = new QImage();
        temp->load(this->path);
        thread->quit();
        texture =  temp;
        dispatchEvent(Event(this, Event::COMPLETE));
    }
private:
    QImage* texture;
    QString path;
    QThread* thread;
};

class Bitmap : public InteractiveObject, public EventHandler
{
public:
    Bitmap();
    ~Bitmap();
    QImage* getSource() const;
    void load(QString);
    void render(QPainter*, const Matrix&, bool, float);
    void Invoke(const Event &event);
private:
    static std::map<QString, QImage*> cache;
    QImage* source;
    QString source_path;
    TextureLoader* loader;
};

#endif // BITMAP_H
