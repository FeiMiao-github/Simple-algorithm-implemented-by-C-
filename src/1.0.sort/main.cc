/**
 * 一些简单的排序算法的实现
 *      bubble_sort 冒泡排序
 *      select_sort 选择排序
 *      insert_sort 插入排序
 *      merge_sort  归并排序
 *      quick_sort  快速排序
 *      heap_sort   堆排序
 *      bucket_sort 桶排序(不基于比较排序)
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std::chrono_literals;

using std::vector;
using std::string;
using std::cout;

// 工具函数，比较两个数组内的元素是否相等
bool operator==(vector<int>& a, vector<int> &b)
{
    if (a.size() != b.size()) return false;

    for (size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }

    return true;
}

// 工具函数，打印一个数组
std::ostream &operator<<(std::ostream  &out, vector<int> &arr)
{
    out << "{";
    for (auto&& v : arr)
    {
        out << v << ",";
    }
    out << "}";
    return out;
}

class i_sort
{
protected:
    /**
     * 此处a和b应当指向不同的内存空间
     * 不推荐使用
     */
    void swap(int &a, int&b) const
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }

public:
    virtual ~i_sort() = default;
    virtual void execute(vector<int> &arr) const = 0;
};

// 冒泡排序
// 时间复杂度 n^2
// 空间复杂度 1
class bubble_sort
    : public i_sort
{
public:
    void execute(vector<int> &arr) const override
    {
        for (int i = arr.size() - 1; i > 0; i--)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// 选择排序
// 时间复杂度 n^2
// 空间复杂度 1
class select_sort
    : public i_sort
{
public:
    void execute(vector<int> &arr) const override
    {
        int l = arr.size();
        for (int i = 0; i < l - 1; i++)
        {
            // 最小值的数组下标
            int mini = i;
            for (int j = i + 1; j < l; j++)
            {
                if (arr[mini] > arr[j])
                {
                    swap(arr[mini], arr[j]);
                }
            }
        }
    }
};

// 插入排序
// 时间复杂度 n^2 (最好时间复杂度n)
// 空间复杂度 1
class insert_sort
    : public i_sort
{
public:
    void execute(vector<int> &arr) const override
    {
        int l = arr.size();
        for (int i = 1; i < l; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (arr[j] > arr[j-1])
                {
                    break;
                }
                else
                {
                    swap(arr[j], arr[j - 1]);
                }
            } 
        }
    }
};

// 归并排序
// 时间复杂度 n * log n
// 空间复杂度 n
class merge_sort
    : public i_sort
{
    void process(vector<int> &arr, int l, int r) const
    {
        if (l + 1 == r)
        {
            return;
        }

        int mid = l + ((r - l) >> 1);
        process(arr, l, mid);
        process(arr, mid, r);

        int i = l;
        int j = mid;
        vector<int> tmp(r - l);
        int k = 0;
        while (i < mid && j < r)
        {
            if (arr[i] < arr[j])
            {
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

        k = 0;
        for (i = l; i < r; i++)
        {
            arr[i] = tmp[k++];
        }
    }
public:
    void execute(vector<int> &arr) const override
    {
        if (arr.size() < 2u)
        {
            return;
        }

        int l = 0;
        int r = arr.size();
        process(arr, l, r);
    }
};

// 快速排序
// 最差时间复杂度 O(N^2)
// 平均时间复杂度 O(NlogN)
// 空间复杂度 O(logn)
// 相同元素较多的情况下会节省更多的时间，因为它每次处理一批数据
class quick_sort
    : public i_sort
{
    void sort(vector<int> &arr, int l, int r) const
    {
        if (l + 1 < r)
        {
            int pos = random() % (r - l) + l;
            int l_end = 0, r_start = 0;
            if (pos != r - 1)
            {
                swap(arr[pos], arr[r - 1]);
            }
            partion(arr, l, r, l_end, r_start);
            sort(arr, l, l_end);
            sort(arr, r_start, r);
        }
    }

    void partion(vector<int> &arr, int l, int r, int &l_end, int &r_start) const
    {
        int tmpl = l;
        int tmpr = r - 1;
        int num = arr[tmpr];

        int i = tmpl;
        
        while (i < tmpr)
        {
            if (arr[i] > num)
            {
                if (i != tmpr - 1)
                {
                    swap(arr[i], arr[tmpr - 1]);
                }
                tmpr--;
            }
            else if (arr[i] == num)
            {
                i++;
            }
            else if (tmpl != i)
            {
                swap(arr[tmpl], arr[i]);
                tmpl++;
                i++;
            }
            else
            {
                tmpl++;
                i++;
            }
        }

        if (tmpr != r - 1)
        {
            swap(arr[r - 1], arr[tmpr]);
        }

        r_start = tmpr + 1;
        l_end = tmpl;
    }
public:
    void execute(vector<int> &arr) const override
    {
        sort(arr, 0, arr.size());
    }
};

// 堆排序
// 时间复杂度 n log n
// 空间复杂度 1
// 对于几乎有序的数组会节省较多的时间
class heap_sort
    : public i_sort
{
    void heap_insert(vector<int> &arr, int index) const
    {
        // (n - 1) * log n
        int pindex = (index - 1) / 2;
        while (arr[index] > arr[pindex])
        {
            swap(arr[index], arr[pindex]);
            index = pindex;
            pindex = (index - 1) / 2;                
        }
    }

    void heapify(vector<int> &arr, int index, int heapsize) const
    {
        // 从0开始执行堆化过程
        int left = 2 * index + 1;
        // 判断有左子节点
        while (left < heapsize)
        {
            // 获取子节点较大的值
            int largest = (
                    (left + 1) < heapsize && (arr[left + 1] > arr[left])
                ) ? left + 1 : left;
            // 与父节点比较
            //      情况1:小等于父节点.保持不变
            //      情况2:大于父节点,与父结点交换
            largest = arr[largest] > arr[index] ? largest : index;
            if (largest == index)
            {
                // 较大的是父节点,退出循环
                break;
            }
            swap(arr[largest], arr[index]);
            index = largest;
            left = largest * 2 + 1;
        }
    }
public:
    void execute(vector<int> &arr) const override
    {
        // heap_insert(arr);
        // 从数组下标0开始执行堆插入过程
        const int l = arr.size();
#define USE_HEAP_SORT_1 1
#if USE_HEAP_SORT_1
        // 准备过程1
        for (int i = 1; i < l; i++)
        {
            heap_insert(arr, i);
        }
#else
        // 准备过程2
        for(int i = l - 1; i >= 0; i--)
        {
            heapify(arr, i, l);
        }
#endif
#undef USE_HEAP_SORT_1

        // 从数组下标arr.size() - 1开始执行抛出最大值之后堆化过程
        // (n - 1) log n
        for(int i = l - 1; i > 0; i--)
        {
            // 最大值放在最后，heapsize - 1
            swap(arr[0], arr[i]);
            // 从0开始执行堆化过程
            heapify(arr, 0, i);
        }
    }
};

class bucket_sort
    : public i_sort
{
    void sort(vector<int> &arr, int l, int r, int bits) const
    {
        const int radix = 10;

        for (int i = 0; i < bits; i++)
        {
            vector<int> help(r - l);
            vector<int> count(radix);
            for (int j = l; j < r; j++)
            {
                int bit = get_bit(arr[j], i);
                count[bit]++;
            }

            for (int j = 1; j < radix; j++)
            {
                count[j] += count[j - 1];
            }
            for (int j = r - 1; j >= l; j--)
            {
                int bit = get_bit(arr[j], i);
                help[count[bit] - 1] = arr[j];
                count[bit]--;
            }
            for (int j = 0; j < (r - l); j++)
            {
                arr[l + j] = help[j];
            }
        }
    }

    int get_bit(int num, int index) const
    {
        const int radix = 10;
        int i = 0;
        int res = num % radix;
        while (i < index)
        {
            if (num == 0) return 0;
            i++;
            num /= 10;
            res = num % radix;
        }

        return res;
    }

    int maxbits(int max) const
    {
        const int radix = 10;
        int res = 1;
        while (max / radix != 0)
        {
            res++;
            max /= radix;
        }
        return res;
    }
public:
    void execute(vector<int> &arr) const override
    {
        if (arr.size() < 2u)
        {
            return;
        }

        int m = INT32_MIN;
        for (auto&& v : arr)
        {
            if (v > m)
            {
                m = v;
            }
        }
        sort(arr, 0, arr.size(), maxbits(m));
    }
};

// 测试类
class test
{
public:
    test(i_sort *s)
        : m_sort_(s)
    {
    }

    void set_sort(i_sort *s)
    {
        m_sort_ = s;
    }

private:
    void test_case(const string &name, vector<int> &arr, vector<int> &res)
    {
        cout << "Test " << name << ":";
        auto start = std::chrono::steady_clock::now();
        m_sort_->execute(arr);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = (end - start);

        if (arr == res)
        {
            cout << "true[" << diff.count() << " s]";
        }
        else
        {
            cout << "false";
        }
        cout << "\n";
    }

    void generate_random(vector<int> *arr, int total)
    {
        time_t t = time(nullptr);
        srand48(t);
        for (int i = 0; i < total; i++)
        {
            int v = random() % 10000;
            arr->push_back(v);
        }
    }

public:
    void execute(const string &name = "unknown")
    {

        vector<int> *parr = new vector<int> {5, 4, 3, 2, 1};
        vector<int> *pres = new vector<int> {1, 2, 3, 4, 5};
        test_case("case1 (" + name + ")", *parr, *pres);
        delete parr;
        delete pres;

        parr = new vector<int> {8, 2, 4, 9, 7};
        pres = new vector<int> {2, 4, 7, 8, 9};
        test_case("case2 (" + name + ")", *parr, *pres);
        delete parr;
        delete pres;

        parr = new vector<int> {3, 3, 8, 7, 2, 9, 4};
        pres = new vector<int> {2, 3, 3, 4, 7, 8, 9};
        test_case("case3 (" + name + ")", *parr, *pres);
        delete parr;
        delete pres;

        parr = new vector<int> {37, 34, 18, 17, 22, 19, 14};
        pres = new vector<int> {14, 17, 18, 19, 22, 34, 37};
        test_case("case3 (" + name + ")", *parr, *pres);
        delete parr;
        delete pres;

        cout << "\n";
    }

    void execute(const string &name, i_sort *verify)
    {
        auto parr = new vector<int>;
        generate_random(parr, (int)1E5);
        auto pres = new vector<int>;
        *pres = *parr;
        verify->execute(*pres);
        test_case("time test (" + name + ")", *parr, *pres);
        delete pres;
        delete parr;
    }
private:
    i_sort *m_sort_;
};

int main()
{
#define ENABLE_TIME_TEST 1

    // 正确性测试
    // 测试冒泡排序
    i_sort *sort = new bubble_sort;
    test t(sort);
    t.execute("bubble sort");
    delete sort;

    // 测试选择排序
    sort = new select_sort;
    t.set_sort(sort);
    t.execute("select sort");
    delete sort;

    // 测试插入排序
    sort = new insert_sort;
    t.set_sort(sort);
    t.execute("insert sort");
    delete sort;

    // 测试归并排序
    sort = new merge_sort;
    t.set_sort(sort);
    t.execute("merge sort");
    delete sort;

    // 测试快速排序
    sort = new quick_sort;
    t.set_sort(sort);
    t.execute("quick sort");
    delete sort;

    // 测试堆排序
    sort = new heap_sort;
    t.set_sort(sort);
    t.execute("heap sort");
    delete sort;

    // 测试桶排序
    sort = new bucket_sort;
    t.set_sort(sort);
    t.execute("bucket sort");
    delete sort;

#if ENABLE_TIME_TEST
    // 时间测试
    // 测试归并排序
    i_sort *verify = nullptr;
    sort = new merge_sort;
    verify = new insert_sort;
    t.set_sort(sort);
    t.execute("merge sort", verify);
    delete sort;
    delete verify;

    verify = new quick_sort;

    // 测试冒泡排序
    sort = new bubble_sort;
    t.set_sort(sort);
    t.execute("bubble sort", verify);
    delete sort;

    // 测试选择排序
    sort = new select_sort;
    t.set_sort(sort);
    t.execute("select sort", verify);
    delete sort;

    // 测试插入排序
    sort = new bubble_sort;
    t.set_sort(sort);
    t.execute("insert sort", verify);
    delete sort;

    // 测试快速排序
    sort = new quick_sort;
    t.set_sort(sort);
    t.execute("quick sort", verify);
    delete sort;

    // 测试堆排序
    sort = new heap_sort;
    t.set_sort(sort);
    t.execute("heap sort", verify);
    delete sort;

    // 测试桶排序
    sort = new bucket_sort;
    t.set_sort(sort);
    t.execute("bucket sort", verify);
    delete sort;

    delete verify;
#endif // ENABLE_TIME_TEST
#undef ENABLE_TIME_TEST

    return 0;
}