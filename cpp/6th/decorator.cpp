#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;


class Person
{
public:
    Person()
    {}
    Person(const string &name)
        :_name(name)
    {}
    virtual void show()
    {
        cout << "装扮的" << _name << endl;
    }
private:
    string _name;
};

class Decorator : public Person
{
public:
    virtual void decorator(Person *p)
    {
        _component = p;
    }
    virtual void show() override
    {
        if (_component) {
            _component->show();
        }
        Person::show();
    }
protected:
    Person *_component{nullptr};
};

class TShirt : public Decorator
{
public:
    virtual void show() override
    {
        cout << "T 恤 ";
        _component->show();
    }
};

class BigTrouser: public Decorator
{
public:
    virtual void show() override
    {
        cout << "垮裤 ";
        _component->show();
    }
};

class Sneakers: public Decorator
{
public:
    virtual void show() override
    {
        cout << "破球鞋 ";
        _component->show();
    }
};

class LeatherShoes: public Decorator
{
public:
    virtual void show() override
    {
        cout << "皮鞋 ";
        _component->show();
    }
};

int main()
{
    Person person("小灰");
    Sneakers sneaker;
    sneaker.decorator(&person);
    LeatherShoes lshoes;
    lshoes.decorator(&sneaker);
    lshoes.show();
    //////////////////////////////////////////
    BigTrouser bt;
    bt.decorator(&person);
    TShirt ts;
    ts.decorator(&bt);
    ts.show();

}
