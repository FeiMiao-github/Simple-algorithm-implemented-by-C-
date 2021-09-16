/**
 * 小和问题 
 *      1 3 5 2 4
 *      3 > 1 --> 1
 *      5 > 3, 5 > 2 --> 3,2
 *      2 > 1 --> 1
 *      4 > 2, 4 > 3, 4 > 1 --> 2,3,1
 * 此时小和 = 1 + 3 + 2 + 1 + 2 + 3 + 1
 * 
 */

#include <iostream>
#include <vector>
#include <chrono>

using std::cout;
using std::vector;
using std::string;

/**
 * @brief 利用Merge_sort解决和问题
 * 时间复杂度 n log (n)
 */
class solution
{
    int process(vector<int> &arr, int l, int r)
    {
        if (l + 1 >= r)
        {
            return 0;
        }

        int ret = 0;
        int mid = l + ((r - l) >> 1);
        ret += process(arr, l, mid);
        ret += process(arr, mid, r);

        int i = l;
        int j = mid;
        int k = 0;
        vector<int> tmp(r - l);
        while (i < mid && j < r)
        {
            if (arr[i] < arr[j])
            {
                ret += (r - j) * arr[i];
                tmp[k++] = arr[i++];
            }
            else
            {
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

        return ret;
    }
public:
    int minsum(vector<int> &arr)
    {
        int l = 0;
        int r = arr.size();
        return process(arr, l, r);
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
    void test_case(const string &name, vector<int> &arr, int res)
    {
        cout << "Test " << name << ":";
        auto start = std::chrono::steady_clock::now();
        int ret = m_solution_->minsum(arr);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = (end - start);

        if (ret == res)
        {
            cout << "true[" << diff.count() << " s]";
        }
        else
        {
            cout << "false";
        }
        cout << "\n";
    }
public:
    void execute(const string &name = "unknown")
    {

        vector<int> *parr = new vector<int> {5, 4, 3, 2, 1};
        int res = 0;
        test_case("case1 (" + name + ")", *parr, res);
        delete parr;

        parr = new vector<int> {8, 2, 4, 9, 7};
        res = 22;
        test_case("case2 (" + name + ")", *parr, res);
        delete parr;

        parr = new vector<int> {8, 2, 4, 9, 7, 3};
        res = 24;
        test_case("case2 (" + name + ")", *parr, res);
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