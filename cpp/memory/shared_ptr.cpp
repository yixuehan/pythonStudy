#include <memory>
#include <iostream>
using namespace std;

struct Good : std::enable_shared_from_this<Good> // 注意：继承
{
public:
	// std::shared_ptr<Good> getptr() {
	// 	return shared_from_this();
	// }
	~Good() { std::cout << "Good::~Good() called" << std::endl; }
};

int main()
{
	// 大括号用于限制作用域，这样智能指针就能在system("pause")之前析构
    std::shared_ptr<Good> ptr;
	{
		std::shared_ptr<Good> gp1(new Good());
		//auto gp1(new Good());
		std::shared_ptr<Good> gp2 = gp1->shared_from_this();
		// 打印gp1和gp2的引用计数
		//std::cout << "gp1.use_count() = " << gp1.use_count() << std::endl;
		std::cout << "gp2.use_count() = " << gp2.use_count() << std::endl;
        auto g3(new Good);
        ptr = g3->shared_from_this();
		std::cout << "gp2.use_count() = " << gp2.use_count() << std::endl;
	}
    cout << "out scope\n";
}
