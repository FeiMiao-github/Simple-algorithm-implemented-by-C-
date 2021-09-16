/**
 * 使用C++中的有序表
 */

#include <iostream>
#include <map>
#include <set>

using namespace std;

ostream &operator<<(ostream &out, map<int, string> &m)
{
    out << "{";
    for (auto &&v: m)
    {
        out << v.first << ":" << v.second << ",";
    }
    out << "}";
    return out;
}

ostream &operator<<(ostream &out, set<int> &s)
{
    out << "{";
    for (auto &&v: s)
    {
        out << v << ',';
    }
    out << "}";
    return out;
}

void test_map()
{
    map<int, string> map {{1, "I'm 1"}, {2, "I'm 2"}};
    cout << map << "\n";

    map.insert({4, "I'm 4"});
    map.insert({3, "I'm 3"});
    map.insert({5, "I'm 5"});
    cout << map << "\n";

    map.erase(5);
    cout << map << "\n";
}

void test_set()
{
    set<int> set {7, 2, 5, 3, 2};
    cout << set << "\n";

    set.insert({3, 4});
    cout << set << "\n";
}

int main()
{
    test_map();
    test_set();
    return 0;
}