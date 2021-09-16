/**
 * 给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，
 * 分别表示 nums1 和 nums2 中的元素数目。
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class i_solution
{
public:
    virtual void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) const = 0;
    virtual ~i_solution() = default;
};

class solution_normal
    : public i_solution
{
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) const override
    {
        queue<int> q;
        int s1 = 0, s2 = 0;
        while (s1 < m && s2 < n)
        {
            if (q.empty())
            {
                if (nums1[s1] > nums2[s2])
                {
                    q.push(nums1[s1]);
                    nums1[s1] = nums2[s2];
                    s1++;
                    s2++;
                }
                else
                {
                    s1++;
                }
            }
            else
            {
                if (q.front() > nums2[s2])
                {
                    q.push(nums1[s1]);
                    nums1[s1] = nums2[s2];
                    s1++;
                    s2++;
                }
                else
                {
                    q.push(nums1[s1]);
                    nums1[s1] = q.front();
                    q.pop();
                    s1++;
                }
            }
        }
        
        if (s1 < m)
        {
            int j = m + n - 1;
            for (int i = m - 1; i >= s1; i--, j--)
            {
                nums1[j] = nums1[i];
            }
            
            while (!q.empty())
            {
                nums1[s1] = q.front();
                q.pop();
                s1++;
            }
            return;
        }
        
        while(!q.empty() && s2 < n)
        {
            if (q.front() > nums2[s2])
            {
                nums1[s1] = nums2[s2];
                s2++;
                s1++;
            }
            else
            {
                nums1[s1] = q.front();
                s1++;
                q.pop();
            }
        }
        
        while (!q.empty())
        {
            nums1[s1++] = q.front();
            q.pop();
        }
        
        while (s2 < n)
        {
            nums1[s1++] = nums2[s2++];
        }
    }
};

class solution_reverse_sort
    : public i_solution
{
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) const override
    {
        int i = m + n - 1;
        m -= 1;
        n -= 1;
        while (m >= 0 && n >= 0)
        {
            if (nums1[m] > nums2[n])
            {
                nums1[i--] = nums1[m--];
            }
            else
            {
                nums1[i--] = nums2[n--];
            }
        }

        while (m >= 0)
        {
            nums1[i--] = nums1[m--];
        }

        while (n >= 0)
        {
            nums1[i--] = nums2[n--];
        }
    }
};

class test
{
private:
    bool check_equal(vector<int> *arr1, vector<int> *arr2)
    {
        if (arr1->size() != arr2->size()) return false;
        for (auto p1 = arr1->begin(), p2 = arr2->begin();
            p1 != arr1->end(); p1++, p2++)
        {
            if (*p1 != *p2)
            {
                return false;
            }
        }
        return true;
    }

    void test_case(i_solution *s, vector<int> *arr1, int m, vector<int> *arr2, int n, vector<int> *res)
    {
        bool r = false;
        cout << "Test" << ++no << " ====> ";
        s->merge(*arr1, m, *arr2, n);
        r = check_equal(arr1, res);
        cout << "result: " << (r ? "true" : "false");
        cout << "\n";
        if (!r)
        {
            cout << "{";
            for (auto p = arr1->begin(); p != arr1->end(); p++)
            {
                cout << *p << ", ";
            }
            cout << "}\n";
        }
    }
public:
    void operator()(i_solution *s)
    {
        vector<int> * parr1 = new vector<int> {1,3,0};
        vector<int> * parr2 = new vector<int> {2};
        vector<int> * res = new vector<int> {1,2,3};
        test_case (s, parr1,  2, parr2, 1, res);
        delete res;
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {1, 2, 0, 0};
        parr2 = new vector<int> {3, 4};
        res  = new vector<int> {1, 2, 3, 4};
        test_case (s, parr1, 2, parr2, 2, res);
        delete res;
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {0};
        parr2 = new vector<int> {3};
        res  = new vector<int> {3};
        test_case (s, parr1, 0, parr2, 1, res);
        delete res;
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {3};
        parr2 = new vector<int> {0};
        res  = new vector<int> {3};
        test_case (s, parr1, 1, parr2, 0, res);
        delete res;
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {
            -48,-46,-46,-46,-45,-45,-44,-42,-38,-36,-35,-34,-33,-32,-32,
            -32,-30,-29,-28,-28,-26,-25,-23,-19,-15,-13,-12,-10,-8,-7,
            -6,-4,-2,0,0,0,1,1,2,4,4,5,6,8,11,11,16,16,22,23,23,24,25,
            25,26,28,29,30,32,33,34,34,35,35,36,36,38,40,41,42,42,42,42,
            45,48,0,0,0,0,0,0,0
        }; // 75
        parr2 = new vector<int> {-36,-27,-24,-14,-13,2,9}; // 7
        res = new vector<int> {
            -48,-46,-46,-46,-45,-45,-44,-42,-38,-36,-36,-35,-34,-33,-32,
            -32,-32,-30,-29,-28,-28,-27,-26,-25,-24,-23,-19,-15,-14,-13,
            -13,-12,-10,-8,-7,-6,-4,-2,0,0,0,1,1,2,2,4,4,5,6,8,9,11,11,
            16,16,22,23,23,24,25,25,26,28,29,30,32,33,34,34,35,35,36,36,
            38,40,41,42,42,42,42,45,48
        };
        test_case (s, parr1, 75, parr2, 7, res);
        delete res;
        delete parr2;
        delete parr1;

        parr1 = new vector<int> {
            -48,-36,-26, -23, -1, 0,0,0
        };
        parr2 = new vector<int> {-36,-27,-24};
        res = new vector<int> {
            -48, -36, -36, -27, -26, -24, -23, -1
        };
        test_case (s, parr1, 5, parr2, 3, res);
        delete res;
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
    i_solution *s = new solution_normal;
    t1(s);
    delete s;

    test t2;
    s = new solution_reverse_sort;
    t2(s);
    delete s;

    return 0;
}