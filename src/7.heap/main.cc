/**
 * 堆的简单实现(完全二叉树) 
 *      功能: 查找最小值或最大值
 *      时间复杂度 logn
 */

#include <iostream>
#include <vector>

using namespace std;

class custom_heap
{
public:
    void insert(const int &n)
    {
        m_heap_.push_back(n);
        int index = m_heap_.size() - 1;
        int parentIndex = (index - 1) / 2;
        while (m_heap_[index] > m_heap_[parentIndex])
        {
            swap(m_heap_[index], m_heap_[parentIndex]);
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
    }

    void heapify(int index, int heapsize)
    {
        int left = 2 * index + 1;
        while (left < heapsize)
        {
            int largest = (
                    left + 1 < heapsize
                    && (m_heap_[left] < m_heap_[left+1])
                )
                ? left + 1 : left;
            largest = m_heap_[index] < m_heap_[largest]
                ? largest : index;
            
            if (largest == index)
            {
                break;
            }
            swap(m_heap_[largest], m_heap_[index]);
            index = largest;
            left = 2 * index + 1;;
        }
    }

    friend ostream& operator<<(ostream& out, custom_heap &h)
    {
        out << '{';
        for (auto&& v : h.m_heap_)
        {
            out << v << ',';
        }
        out << '}';
        return out;
    }

    vector<int> m_heap_;
};

void test_custom_heap()
{
    custom_heap ch;
    time_t seed = time(nullptr);
    srand(seed);
    
    for (int i = 0; i < 10; i++)
    {
        ch.insert(rand() % 100);
    }

    cout << "custom_heap:" << ch << '\n';
    ch.m_heap_[0] = 0;
    cout << "custom_heap:" << ch << '\n';
    ch.heapify(0, ch.m_heap_.size());
    cout << "custom_heap:" << ch << '\n';
}

int main()
{
    test_custom_heap();
    return 0;
}