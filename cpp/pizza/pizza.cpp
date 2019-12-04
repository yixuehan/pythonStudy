#include <iostream>
#include <memory>
#include <map>
using namespace std;

class Pizza
{
public:
    virtual void prepare() {
        cout << "标准化准备" << endl;
    }
    virtual void bake() {
        cout << "标准化烘焙\n";
    }
    virtual void cut() {
        cout << "标准化切分\n";
    }
    virtual void box() {
        cout << "标准化打包\n";
    }
private:
    string _name;
};

class PizzaA : public Pizza
{
public:
    virtual void prepare()  override {
        cout << "pizzaA prepare\n";
    }
};

class PizzaB : public Pizza
{
public:
    virtual void cut() override {
        cout << "pizzaB cut\n";
    }
};

enum class PizzaType {PizzaA, PizzaB};
class PizzaFactory
{
public:
    PizzaFactory()
    {
    }
    static shared_ptr<Pizza> createPizza(PizzaType type)
    {
        shared_ptr<Pizza> ptr;
        switch (type) {
        case PizzaType::PizzaA:
            ptr.reset(new PizzaA);
            break;
        case PizzaType::PizzaB:
            ptr.reset(new PizzaB);
            break;
        }
        return ptr;
    }
private:
};

class PizzaStore
{
public:
    static shared_ptr<Pizza> orderPizza(PizzaType type)
    {
        auto pizza = PizzaFactory::createPizza(type);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }
};

int main()
{
    PizzaStore::orderPizza(PizzaType::PizzaA);
}
