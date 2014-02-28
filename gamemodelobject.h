#ifndef GAMEMODELOBJECT_H
#define GAMEMODELOBJECT_H

#include <map>
#include <vector>

class GameModelObject
{
public:
    GameModelObject(__int64 id);
    GameModelObject();
    virtual ~GameModelObject();
    static GameModelObject* findById(__int64 id);
    __int64 getId();
    void setId(__int64);

    bool isValid();
    void invalidate();

private:
    bool valid;
    void insert(__int64, const GameModelObject*);
    void erase(__int64);
    __int64 my_id;
    static std::map<__int64, GameModelObject*> table;
};

#endif // GAMEMODELOBJECT_H
