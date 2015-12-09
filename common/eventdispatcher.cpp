#include "eventdispatcher.h"

#include "console.h"

EventDispatcher::EventDispatcher()
{
    recuirsion_count = 0;
}

void EventDispatcher::addEventListener(EventHandler* func)
{
    if (func == 0)
    {
        return;
    }
    if (recuirsion_count == 0)
    {
        listeners.insert(listeners.end(), std::make_pair(func, true));
    }
    else
    {
        nn.push_back(std::make_pair(func, true));
    }
}

void EventDispatcher::removeEventListener(EventHandler* func)
{
    if (func == 0)
    {
        return;
    }

    if (recuirsion_count == 0)
    {
        for (LIST::iterator i = listeners.begin(); i != listeners.end();)
        {
            if (i->first == func)
            {
                i = listeners.erase(i);
            }
            else
            {
                ++i;
            }
        }
    }
    else
    {
        for (LIST::iterator i = listeners.begin(); i != listeners.end();++i)
        {
            if (i->first == func)
            {
                i->second = false;
                break;
            }
        }
    }
}

void EventDispatcher::dispatchEvent(const Event& event)
{
    if (recuirsion_count == 0)
    {
        while (!nn.empty())
        {
            listeners.push_back(nn.back());
            nn.pop_back();
        }
    }

    ++recuirsion_count;
    for (LIST::iterator i = listeners.begin(); i != listeners.end(); ++i)
    {
        if (i->second)
        {
            i->first->Invoke(event);
        }
    }
    --recuirsion_count; 

    if (recuirsion_count == 0)
    {
        for (LIST::iterator i = listeners.begin(); i != listeners.end();)
        {
            if (i->second)
            {
                ++i;
            }
            else
            {
                i = listeners.erase(i);
            }
        }
    }
}
