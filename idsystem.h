#ifndef IDSYSTEM_H
#define IDSYSTEM_H

class IDSystem
{
public:
    IDSystem();
    int next();
    void release(int id);
private:
    int next_id;
};

#endif // IDSYSTEM_H
