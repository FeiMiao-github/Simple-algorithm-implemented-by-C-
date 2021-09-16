/**
 * 逆序对问题
 * 给定一个数组，如果一个数左边的数大于它，则它们构成一对逆数对
 * 要求：打印出所有的逆数对
 * 
 */

#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::string;

/**
 * @brief 利用Merge_sort解决和问题
 * 时间复杂度 n log (n)
 */
class solution
{
    void process(vector<int> &arr, int l, int r)
    {
        if (l + 1 >= r)
        {
            return;
        }

        int mid = l + ((r - l) >> 1);
        process(arr, l, mid);
        process(arr, mid, r);

        int i = l;
        int j = mid;
        int k = 0;
        vector<int> tmp(r - l);
        while (i < mid && j < r)
        {
            if (arr[i] <= arr[j])
            {
                tmp[k++] = arr[i++];
            }
            else
            {
                print(arr, i, mid, arr[j]);
                tmp[k++] = arr[j++];
            }
        }

        while (i < mid)
        {
            tmp[k++] = arr[i++];
        }

        while (j < r)
        {
            tmp[k++] = arr[j++];
        }

        i = l;
        k = 0;
        while (i < r)
        {
            arr[i++] = tmp[k++];
        }
    }

    void print(vector<int> &arr, int l, int r, int val)
    {
        for (int i = l; i < r; i++)
        {
            cout << "[" << arr[i] << ", " << val << "],";
        }
    }
public:
    void reverse_order(vector<int> &arr)
    {
        int l = 0;
        int r = arr.size();
        process(arr, l, r);
    }
};

class test
{
public:
    test(solution *s)
        : m_solution_(s)
    {
    }
private:
    void test_case(const string &name, vector<int> &arr)
    {
        cout << "Test " << name << ":";
        m_solution_->reverse_order(arr);
    }
public:
    void execute(const string &name = "unknown")
    {

        vector<int> *parr = new vector<int> {5, 4, 3, 2, 1};
        test_case("case1 (" + name + ")", *parr);
        delete parr;
        cout << "\n";

        parr = new vector<int> {8, 2, 4, 9, 7};
        test_case("case2 (" + name + ")", *parr);
        delete parr;
        cout << "\n";

        parr = new vector<int> {8, 2, 4, 9, 7, 3};
        test_case("case2 (" + name + ")", *parr);
        delete parr;

        cout << "\n";
    }
private:
    solution *m_solution_;
};

int main()
{
    solution s;
    test t(&s);
    t.execute("min sum");

    return 0;
}