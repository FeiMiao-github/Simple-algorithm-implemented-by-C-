/**
 * 荷兰国旗问题
 *   1.给定一个数组arr和一个数num，请把小于等于num的数放在数组的左边，
 * 大于num的数放在数组右边。要求额外的空间复杂度O(1),时间复杂度O(N)
 * 
 *   2.给定一个数组arr和一个数num，请把小于num的数放在数组的左边，等于
 * num的数放在数组中间，大于num的数放在数组的右边。
 * 要求时间复杂度O(N)，空间复杂度O(1)
 */

#include <iostream>
#include <vector>
#include <functional>
#include <chrono>

using namespace std;
using namespace chrono_literals;
using namespace placeholders;

typedef function<void(vector<int>&,int)> func_t;

class solution
{
public:
    void solve1_m1(vector<int> &arr, int num)
    {
        int r = arr.size() - 1;
        int l = 0;

        while (l < r)
        {
            while (arr[l] <= num)
            {
                l++;
            }

            while (arr[r] > num)
            {
                r--;
            }

            if (r < l)
            {
                break;
            }
            else
            {
                swap(arr[l], arr[r]);
                r--;
                l++;
            }
        }
    }

    void solve1_m2(vector<int> &arr, int num)
    {
        int r = arr.size();

        int i = 0;
        while (i < r)
        {
            if (arr[i] <= num)
            {
                i++;
            }
            else
            {
                swap(arr[i], arr[r - 1]);
                r -= 1;
            }
        }
    }

    void solve2(vector<int> &arr, int num)
    {
        int r = arr.size();
        int l = 0;

        int i = 0;
        while (i < r)
        {
            if (arr[i] > num)
            {
                swap(arr[i], arr[r - 1]);
                r--;
            }
            else if (arr[i] == num)
            {
                i++;
            }
            else if (i == l)
            {
                i++;
                l++;
            }
            else 
            {
                swap(arr[l], arr[i]);
                i++;
                l++;
            }
        }
    }
};

ostream& operator<<(ostream& o, vector<int> &arr)
{
    o << "[";
    auto p = arr.begin();
    while (p != arr.end())
    {
        o << *p;
        if (++p != arr.end())
        {
            o << ",";
        }
    }
    o << "]";
    return o;
}

void test(func_t f, const string &name, vector<int> &arr, int n)
{
    auto start = chrono::steady_clock::now();
    f(arr, n);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "test " << name << ": time: " << diff.count() << "(s) ";
}

int main(void)
{
    solution s;

    vector<int> *parr = new vector<int> {7, 3, 9, 2, 4, 5, 1, 5, 6};
    func_t func = std::bind(
        &solution::solve1_m1,
        &s,
        _1,
        _2
    );
    test(func, "solve1_m1", *parr, 5);
    cout << *parr << "\n";
    delete parr;

    parr = new vector<int> {7, 3, 9, 2, 4, 5, 1, 5, 6};
    func = std::bind(
        &solution::solve1_m2,
        &s,
        _1,
        _2
    );
    test(func, "solve1_m2", *parr, 5);
    cout << *parr << "\n";
    delete parr;

    parr = new vector<int> {9, 8, 7, 6, 5, 4, 3, 2, 1};
    func = std::bind(
        &solution::solve1_m2,
        &s,
        _1,
        _2
    );
    test(func, "solve1_m2", *parr, 5);
    cout << *parr << "\n";
    delete parr;

    parr = new vector<int> {9, 8, 7, 6, 5, 4, 3, 2, 1};
    func = std::bind(
        &solution::solve2,
        &s,
        _1,
        _2
    );
    test(func, "solve2", *parr, 5);
    cout << *parr << "\n";
    delete parr;

    
    parr = new vector<int> {7, 3, 9, 2, 4, 5, 1, 5, 6};
    func = std::bind(
        &solution::solve2,
        &s,
        _1,
        _2
    );
    test(func, "solve2", *parr, 5);
    cout << *parr << "\n";
    delete parr;

    return 0;
}