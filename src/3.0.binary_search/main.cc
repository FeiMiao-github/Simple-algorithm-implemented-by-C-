/**
 * 二分查找
 *     1. 有序数组(升序)中查找 a
 *     2. 有序数组(升序)中查找大于等于a的最左侧的数字
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cout;

class b_search
{
public:
    virtual ~b_search() = default;
    virtual int search(vector<int> &arr, int tgt) const = 0;
};

class b_search_r
    : public b_search
{
private:
    /**
     * @brief find designated value
     * @return the index of the designated value. if not exists, return -1
     */
    int search(vector<int> &arr, int tgt, int s, int e) const
    {
        if (s > e)
        {
            return -1;
        }

        int mid = (s + e) / 2;
        if (arr[mid] == tgt)
        {
            return mid;
        }
        
        if (arr[mid] > tgt)
        {
            return search(arr, tgt, s, mid - 1);
        }
        else
        {
            return search(arr, tgt, mid + 1, e);
        }
    }

public:
    int search(vector<int> &arr, int tgt) const override
    {
        int e = arr.size() - 1;
        if (e < 0)
        {
            return -1;
        }
        return search(arr, tgt, 0, e);
    }
};

class b_search_f
    : public b_search
{
public:
    int search(vector<int> &arr, int tgt) const override
    {
        int s = 0;
        int e = arr.size() - 1;

        if (e < 0)
        {
            return -1;
        }

        int mid = (s + e) / 2;
        while (s <= e)
        {
            if (arr[mid] == tgt)
            {
                break;
            }
            if (arr[mid] > tgt)
            {
                e = mid - 1;
            }
            else
            {
                s = mid + 1;
            }
            mid = (s + e) / 2;
        }

        return s > e ? -1 : mid;
    }
};

class test
{
private:
    void test_case(b_search *s, vector<int> *arr, int tgt, int res)
    {
        cout << "Test" << ++no << " ====> ";
        int r = s->search(*arr, tgt);
        cout << "result: " << ((r == res) ? "true" : "false");
        cout << "\n";
    }
public:
    void operator()(b_search *s)
    {
        // test1
        vector<int> * parr = new vector<int> {};
        test_case (s, parr, 0, -1);
        delete parr;

        parr = new vector<int> {1, 2, 3, 4};
        test_case (s, parr, 1, 0); // test2
        test_case (s, parr, 0, -1); // test3
        test_case (s, parr, 4, 3); // test4
        test_case (s, parr, 5, -1); // test5
        delete parr;

        parr = new vector<int> {1, 2, 3, 4, 5};
        test_case (s, parr, 1, 0); // test6
        test_case (s, parr, 0, -1); // test7
        test_case (s, parr, 5, 4); // test8
        test_case (s, parr, 6, -1); // test9
        delete parr;

        parr = new vector<int> {0, 2, 3, 4, 6};
        test_case (s, parr, 1, -1); // test10
        test_case (s, parr, 5, -1); // test11
        delete parr;
    }
private:
    int no = 0;
};

int main()
{
    test t1;
    b_search* s = new b_search_r;
    t1(s);
    delete s;

    test t2;
    s = new b_search_f;
    t2(s);
    delete s;

    return 0;
}


