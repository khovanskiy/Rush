#include "event.h"

const QString Event::INIT = "init";
const QString Event::COMPLETE = "complete";
const QString Event::ENTER_FRAME = "enterFrame";
const QString Event::CHANGE = "change";
const QString Event::ADDED_TO_STAGE = "addedToStage";
const QString Event::REMOVED_FROM_STAGE = "removedFromStage";
const QString Event::INVALIDATE = "invalidate";

Event::Event(EventDispatcher* target, QString type)
{
    this->target = target;
    this->type = type;
}
