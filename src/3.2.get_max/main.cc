/**
 * 使用二分法查找数组的最大值
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cout;

class solution
{
    /**
     * n + n / 2 + n / 4 + .... = n * (1 - (1/2)^(log2(n))) / (1 - 1/2)
     *                          = 2n - 2
     */
    int process(vector<int> &arr, int l, int r)
    {
        if (l + 1 == r)
        {
            return arr[l];
        }

        int mid = l + ((r - l) >> 1);
        int lmax = process(arr, l, mid);
        int rmax = process(arr, mid, r);
        return lmax > rmax ? lmax : rmax;
    }

public:
    int max(vector<int> &arr)
    {
        int l = 0;
        int r = arr.size();
        if (r == 0)
        {
            return 0;
        }

        if (r == 1)
        {
            return arr[0];
        }

        return process(arr, l, r);
    }
};

class test
{
private:
    void test_case(solution *s, vector<int> *arr1, int res)
    {
        cout << "Test" << ++no << " ====> ";
        int r = s->max(*arr1);
        cout << "result: " << ((r == res) ? "true" : "false");
        cout << "\n";
    }
public:
    void operator()(solution *s)
    {
        vector<int> * parr = new vector<int> {1,3};
        int res = 3;
        test_case (s, parr, res);
        delete parr;

        parr = new vector<int> {5, 4, 2, 3, 9, 8, 1};
        res = 9;
        test_case (s, parr, res);
        delete parr;

        cout << "\n";
    }
private:
    int no = 0;
};

int main()
{
    solution s;

    test t1;
    t1(&s);

    return 0;
}