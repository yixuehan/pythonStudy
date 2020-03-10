#include <iostream>
#include <algorithm>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class Solution {
public:
    string addBinary(string a, string b) {
        if (a.size() < b.size()) return addBinary(std::move(b), std::move(a));
        string res = "0";
        res.resize(a.size()+1);
        int posB = b.size()-1;
        int posA = a.size()-1;
        int flag = 0;
        int temp;
        while(posB >=0) {
            temp = a[posA] -'0' + b[posB] - '0' + flag;
            res[posA+1] = (temp % 2) + '0';
            flag = temp / 2;
            --posB;
            --posA;
        }
        while (posA >= 0) {
            temp = a[posA] -'0' + flag;
            res[posA+1] = (temp % 2) + '0';
            flag = temp / 2;
            --posA;
        }
        if (flag == 1) {
            res[0] = '1';
            return res;
        }
        return res.substr(1);
    }
    string addBinary2(string a, string b) {
        if (a.size() < b.size()) return addBinary2(std::move(b), std::move(a));
        string res;
        int posA = a.size()-1;
        int posB = b.size()-1;
        int flag = 0;
        int valueA, valueB, temp;
        while(posB >= 0) {
            valueA = a[posA--] - '0';
            valueB = b[posB--] - '0';
            temp = valueA + valueB + flag;
            res.push_back(temp % 2 + '0');
            flag = temp / 2;
        }
        while(posA >= 0) {
            valueA = a[posA--] - '0';
            temp = valueA + flag;
            res.push_back(temp % 2 + '0');
            flag = temp / 2;
        }
        if (flag == 1) {
            res.push_back('1');
        }
        int l = 0, r = res.size()-1;
        while (l < r) {
            // res[l] = res[l] ^ res[r];
            // res[r] = res[l] ^ res[r];
            // res[l] = res[l] ^ res[r];
            // temp = res[l];
            // res[r] = temp;
            // res[l] = res[r];
            std::swap(res[l], res[r]);
            ++l;
            --r;
        }
        return res;
    }
};

int main()
{
    Solution s;
    {
        timer::auto_cpu_timer t;
        for (int i = 0;i < 1000000; ++i) {
            s.addBinary("1010101010101010", "10101010101010101001101011010101010101010");
        }
    }
    cout << s.addBinary("1010101010101010", "10101010101010101001101011010101010101010") << endl;
    {
        timer::auto_cpu_timer t;
        for (int i = 0;i < 1000000; ++i) {
            s.addBinary2("1010101010101010", "10101010101010101001101011010101010101010");
        }
    }
    cout << s.addBinary2("1010101010101010", "10101010101010101001101011010101010101010") << endl;
}
