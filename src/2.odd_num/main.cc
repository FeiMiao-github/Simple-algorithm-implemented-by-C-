/**
 * 获取数组中个数为奇数的数字
 *     1: 只有一个数字的个数为奇数
 *     2: 只有两个数字个数为奇数
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::swap;

// 1: 只有一个数字的个数为奇数
class oddnum1
{
public:
    /**
     * @return 目标数字
     */
    int func(vector<int> &arr)
    {
        if (arr.size() < 2)
        {
            throw "arr.size should be greater than 1";
        }

        int eor = arr[0];
        for (auto p = arr.begin() + 1; p != arr.end(); p++)
        {
            eor ^= *p;
        }

        return eor;
    }
};

// 2: 只有两个数字个数为奇数
class oddnum2
{
public:
    /**
     * @brief 获取数组中出现奇数次的2个数字
     * @param odda 目标数字
     * @param oddb 目标数字
     */
    void func(vector<int> &arr, int &odda, int &oddb)
    {
        if (arr.size() < 2)
        {
            throw "arr.size should be greater than 1";
        }

        int eor = 0;
        for (auto p = arr.begin(); p != arr.end(); p++)
        {
            eor ^= *p;
        }

        // 获取最右侧的1
        int right = eor & (~eor + 1);
        int eor1 = 0;
        for (auto p = arr.begin() + 1; p != arr.end(); p++)
        {
            if (right & *p)
            {
                eor1 ^= *p;
            }
        }

        odda = eor1;
        oddb = eor ^ odda;
    }
};

/**
 * @brief 测试oddnum1
 */
class test_oddnum1
{
private:
    void test_case(vector<int> &arr, int res)
    {
        oddnum1 o;
        cout << "test_oddNum1 " << i++ << ":";
        int r = o.func(arr);
        cout << ((r == res) ? "true" : "false");
        cout << "\n";
    }

public:
    void execute()
    {
        vector<int> *parr = new vector<int> { 1, 2, 4, 2, 4};
        test_case(*parr, 1);
    }
private:
    int i = 1;
};

/**
 * @brief 测试oddnum2
 */
class test_oddnum2
{
private:
    void test_case(vector<int> &arr, int resa, int resb)
    {
        oddnum2 o;
        int ra = 0, rb = 0;
        cout << "test_oddNum2 " << i++ << ":";
        o.func(arr, ra, rb);
        if (ra > rb) swap(ra, rb);
        cout << ((ra == resa && rb == resb) ? "true" : "false");
        cout << "\n";
    }

public:
    void execute()
    {
        vector<int> *parr = new vector<int> { 1, 2, 4, 2, 4, 3};
        test_case(*parr, 1, 3);
    }
private:
    int i = 1;
};

int main()
{
    test_oddnum1 t1;
    t1.execute();

    test_oddnum2 t2;
    t2.execute();
    return 0;
}