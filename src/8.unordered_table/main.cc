/**
 * 使用C++中的哈希表
 * 
 */

#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

ostream& operator<<(ostream& out, unordered_set<int> &set)
{
    for (auto &&v : set)
    {
        out << v << ",";
    }
    return out;
}

ostream& operator<<(ostream& out, unordered_map<int, string> &map)
{
    for (auto &&v : map)
    {
        out << v.first << ":" << v.second << ",";
    }
    return out;
}

void test_hash_set()
{
    unordered_set<int> set { 1, 2, 3, 4, 5, 6};
    cout << set << "\n";

    set.insert(2);
    cout << set << "\n";

    set.insert(8);
    cout << set << "\n";

    set.erase(2);
    cout << set << "\n";
}

void test_hash_map()
{
    std::pair<int, string> xm = make_pair(1, "xiaoMing");
    unordered_map<int, string> map{xm};
    cout << map << "\n";

    map.insert({{2,"Hello"}, {3,"World"}});
    cout << map << "\n";

    map.emplace(4, "WWW");
    cout << map << "\n";

}

int main()
{
    test_hash_set();
    test_hash_map();
    return 0;
}