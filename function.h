#ifndef FUNCTION_H
#define FUNCTION_H

class Event;
class FunctionProxy;

class Function
{
public:
    virtual void Invoke(const Event& event) = 0;
};

class FunctionProxy : public Function
{
public:
    FunctionProxy(Function* f)
    {
        this->f = f;
    }
    void Invoke(const Event &event)
    {
        f->Invoke(event);
    }
private:
    Function* f;
};

#endif // FUNCTION_H
