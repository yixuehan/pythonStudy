#include <iostream>
#include <memory>
struct Base
{
    Base() {
        std::cout << "Base::构造" << std::endl;
    }
    ~Base() { //非virtual
        std::cout << "Base::~析构" << std::endl;
    }
    virtual void execute() = 0;
};

class Inherit : public Base
{
public:
    Inherit() {
        std::cout << "Inherit::构造" << std::endl;
    }
    ~Inherit() { //非virtual
        std::cout << "Inherit::~析构" << std::endl;
    }
    void execute() override {
        std::cout << "Inherit::execute()" << std::endl;
    }
};

int main() {   
    std::cout << "-----原始指针-----" << std::endl;
    {
        Base* p = new Inherit();
        p->execute();
        delete p;
    }

    std::cout << "-----unique_ptr-----" << std::endl;
    {
        // std::unique_ptr<Base> p = std::make_unique<Inherit>();
        std::unique_ptr<Base> p(new Inherit);
        p->execute();        
    }


    std::cout << "-----shared_ptr-----" << std::endl;
    {
        // std::shared_ptr<Base> p = std::make_shared<Inherit>();
        std::shared_ptr<Base> p(new Inherit);
        // std::shared_ptr<Base> p((Base*)new Inherit);
        p->execute();
    }

    std::cout << "-----结束-----" << std::endl;

    return 0;
}
