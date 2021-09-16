/**
 * 寻找两个正序数组的中位数 
 */
#include <iostream>
#include <vector>

using namespace std;

class i_solution {
public:
    virtual double find_median_sorted_arrays(vector<int>& nums1, vector<int>& nums2) const = 0;
    virtual ~i_solution() = default;
};

// merge -> search
// 时间复杂度: O(m+n), 空间复杂度 O(m+n)
class solution_merge
    : public i_solution
{
public:
    double find_median_sorted_arrays(vector<int> &num1, vector<int> &num2) const override
    {
        int total = num1.size() + num2.size();
        vector<int> num(total);
        auto p1 = num1.begin();
        auto p2 = num2.begin();
        auto p = num.begin();
        while (p1 != num1.end() && p2 != num2.end())
        {
            if (*p1 > *p2)
            {
                *p = *p2;
                p2++;
            }
            else
            {
                *p = *p1;
                p1++;
            }
            p++;
        }

        while (p1 != num1.end())
        {
            *p = *p1;
            p++;
            p1++;
        }

        while (p2 != num2.end())
        {
            *p = *p2;
            p++;
            p2++;
        }

        int mid = total / 2;
        int rem = total % 2;
        double ret = num[mid]; 
        if (rem == 0)
        {
            ret += num[mid - 1];
            ret /= 2;
        }
        return ret;
    }
};

// search directly
// 时间复杂度 O(m + n), 空间复杂度O(1)
class solution_search
    : public i_solution
{
public:
    double find_median_sorted_arrays(vector<int> &num1, vector<int> &num2) const override
    {
        int total = num1.size() + num2.size();
        size_t mid = total / 2;
        size_t rem = total % 2;

        int lv = 0, rv = 0;
        size_t n1i = 0, n2i = 0, i = 0;
        while (i <= mid)
        {
            if (n1i >= num1.size() || n2i >= num2.size()) break;
            lv = rv;
            if (num1[n1i] > num2[n2i])
            {
                rv = num2[n2i];
                n2i++;
            }
            else
            {
                rv = num1[n1i];
                n1i++;
            }
            i++;
        }

        while (i <= mid)
        {
            if (n1i >= num1.size()) break;
            lv = rv;
            rv = num1[n1i];
            n1i++;
            i++;
        }

        while (i <= mid)
        {
            if (n2i >= num2.size()) break;
            lv = rv;
            rv = num2[n2i];
            n2i++;
            i++;
        }

        double ret = rv;
        if (rem == 0)
        {
            ret += lv;
            ret /= 2;
        }
        return ret;
    }
};

// search directly
// 时间复杂度 O(log(min(m+n))) 空间复杂度O(1)
class solution_fseach
    : public i_solution
{
public:
    /**
     * 题目分析：
     *     数组A(短),B(长)
     *     A A | A A
     *     B B B |B B
     *     对A数组进行二分法分割,为保持左右元素数量相同,获取B数组的分割位置
     *          Note: 如果A数组和B数组元素和为偶数,
     *                  分割线以左A元素的数量+分割线以左B元素的数量 = 分割线以右A元素的数量+分割线以右B元素的数量
     *                如果A数组和B数组元素和为奇数
     *                  分割线以左A元素的数量+分割线以左B元素的数量 = 分割线以右A元素的数量+分割线以右B元素的数量+1
     * 
     *          若从分割线起向右A数组的第一个元素 < 从分割线起向左B数组的第一个元素
     *                说明中数在A数组分割线以右，采用二分法向右移动分割线
     *          否则
     *                说明中数在A数组分割线以左，采用二分法向左移动分割线
     *          1 2 4 4 9   left = 0 right = 5
     *          2 5 6 8 10
     *          (1) 1 2 4 /4 9 left = 3 right = 5
     *              2 5 /6 8 10
     *          (2) 1 2 4 4 | 9 left = 4 right = 5
     *              2 | 5 6 8 10
     *          (3) 1 2 4 4 9 left = 4 right = 4
     *              2 5 6 8 10
     *          最终结果任意一个左侧元素的值 <= 任意一个右侧元素的值,分割完成
     */
    double find_median_sorted_arrays(vector<int> &num1, vector<int> &num2) const override
    {
        vector<int> *s_arr = &num1;
        vector<int> *l_arr = &num2;

        if (num1.size() > num2.size())
        {
            s_arr = &num2;
            l_arr = &num1;
        }
        int m = s_arr->size();
        int n = l_arr->size();
        int total_left = (n - m + 1) / 2 + m; // 等于 (n + m + 1) / 2

        int left = 0;
        int right = m;

        while (left < right)
        {
            int i = left + (right - left + 1) / 2;
            int j = total_left - i;
            if ((*s_arr)[i - 1] < (*l_arr)[j])
            {
                left = i;
            }
            else
            {
                right = i - 1;
            }
        }

        int i = left;
        int j = total_left - i;
        int s_arr_l = i == 0 ? INT32_MIN : (*s_arr)[i - 1];
        int s_arr_r = i == m ? INT32_MAX : (*s_arr)[i];
        int l_arr_l = j == 0 ? INT32_MIN : (*l_arr)[j - 1];
        int l_arr_r = j == n ? INT32_MAX : (*l_arr)[j];

        double ret = 0;
        if ((m + n) % 2 == 0)
        {
            ret = max(s_arr_l, l_arr_l) + min(s_arr_r, l_arr_r);
            ret /= 2.0;
        }
        else
        {
            ret = max(s_arr_l, l_arr_l);
        }

        return ret;
    }
};

// 时间复杂度 O(log(m+n)) 空间复杂度O(1)
class solution_bsearch
    : public i_solution
{
    int get_kth(vector<int> &num1, vector<int> &num2, int k) const
    {
        int i1 = 0, i2 = 0;
        int l1 = num1.size();
        int l2 = num2.size();

        while (true)
        {
            if (i1 == l1)
            {
                return num2[i2 + k - 1];
            }

            if (i2 == l2)
            {
                return num1[i1 + k - 1];
            }

            if (k == 1)
            {
                return min(num1[i1], num2[i2]);
            }

            int ni1 = min(i1 + k / 2, l1) - 1;
            int ni2 = min(i2 + k / 2, l2) - 1; 
            if (num1[ni1] > num2[ni2])
            {
                k -= ni2 - i2 + 1;
                i2 = ni2 + 1;
            }
            else
            {
                k -= ni1 - i1 + 1;
                i1 = ni1 + 1;
            }
        }
    }
public:
    double find_median_sorted_arrays(vector<int>& nums1, vector<int>& nums2) const override
    {
        int m = nums1.size();
        int n = nums2.size();

        if (m > n)
        {
            return find_median_sorted_arrays(nums2, nums1);
        }

        double ret = 0;
        int index = m + (n - m + 1) / 2;
        if ((m + n) % 2 == 0)
        {
            ret = get_kth(nums1, nums2, index) + get_kth(nums1, nums2, index + 1);
            ret /= 2;
        }
        else
        {
            ret = get_kth(nums1, nums2, index);
        }
        return ret;
    } 
};

class test
{
private:
    void test_case(i_solution *s, vector<int> *arr1, vector<int> *arr2, double res)
    {
        cout << "Test" << ++no << " ====> ";
        double r = s->find_median_sorted_arrays(*arr1, *arr2);
        cout << "result: " << ((r == res) ? "true" : "false");
        cout << "\n";
    }
public:
    void operator()(i_solution *s)
    {
        vector<int> * parr1 = new vector<int> {1,3};
        vector<int> * parr2 = new vector<int> {2};
        test_case (s, parr1,  parr2, 2);
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {1, 2};
        parr2 = new vector<int> {3, 4};
        test_case (s, parr1,  parr2, 2.5);
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {1};
        parr2 = new vector<int> {};
        test_case (s, parr1,  parr2, 1);
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {};
        parr2 = new vector<int> {0};
        test_case (s, parr1,  parr2, 0);
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {1, 3, 5};
        parr2 = new vector<int> {2, 4, 6};
        test_case (s, parr1,  parr2, 3.5);
        delete parr2;
        delete parr1;

        cout << "\n";
    }
private:
    int no = 0;
};

int main()
{
    test t1;
    i_solution *s = new solution_merge;
    t1(s);
    delete s;

    test t2;
    s = new solution_search;
    t2(s);
    delete s;

    test t3;
    s = new solution_fseach;
    t3(s);
    delete s;

    test t4;
    s = new solution_bsearch;
    t4(s);
    delete s;

    return 0;
}