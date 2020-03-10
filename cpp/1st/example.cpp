#include <iostream>
using namespace std;

// example 2
template <int M, int N> 
void foo2(int(*p)[(M<=N) * 10] = 0) {  
    cout << sizeof(*p) << endl;
    cout << "foo2 int\n";
}

template <int M, int N> 
void foo2(double(*p)[(M>N) * 10] = 0) {  
    cout << sizeof(*p) << endl;
    cout << "foo2 double\n";
}

int main()
{
    foo2<10, 12>();  // 函数参数类型替换
    foo2<12, 10>();  // 函数参数类型替换
}
