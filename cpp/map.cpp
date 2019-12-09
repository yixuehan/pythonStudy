#include <iostream>
#include <map>
using namespace std;
 
int main() {
  std::map<int, float> num_map;
  num_map[4] = 4.13;
  num_map[9] = 9.24;
  num_map[1] = 1.09;
  // 调用 a_map.begin() 及 a_map.end()
  for (auto it = num_map.begin(); it != num_map.end(); ++it) {
    std::cout << it->first << ", " << it->second << '\n';
  }
  auto it = num_map.find(4);
  cout << it->second << endl;
  it->second = 100;
  cout << it->second << endl;
  --it;
  cout << it->second << endl;
  int a = 10, b = 20;
    pair<int&, int&> p(a, b);
    p.first = 100;
    p.second = 200;
    cout << a << ' ' << b << endl;
}
