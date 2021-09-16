/**
 *  target: 测试一个链表是否有环
 *  
 */

#include <iostream>
#include <stack>
#include <unordered_set>
#include <thread>

using std::ostream;
using std::cout;
using std::stack;
using std::unordered_set;

template <typename T>
class list;

template <typename T>
ostream& operator<<(ostream& o, list<T> &l);

/**
 *  可能有环的链表
 */
template <typename T>
class list
{
public:
    struct _node
    {
        T _value;
        _node *_next;
        /**
         *  随机节点可以是链表中的节点,也可以是 nullptr
         */
        _node *_rand;

        _node(T val = 0, _node* next = nullptr)
            : _value(val),
              _next(next),
              _rand(nullptr)
        {}
    };

    list()
        : m_head_(nullptr),
          m_size_(0)
    {
    }

    /* 删除 复制构造函数,删除赋值运算符,删除移动构造函数 */
    list(const list&) = delete;
    list(list&&) = delete;
    list& operator=(const list&) = delete;
    list& operator=(list&&) = delete;

    /**
     * 最后一个节点_next指向节点位置,如果大于节点总数,则_next设置为nullptr
     */
    list(const std::initializer_list<int> &list, int pos)
    {
        _node *loop = nullptr;
        _node **tmp = &m_head_;

        int count = 0;
        for (auto p = list.begin(); p != list.end(); p++)
        {
            *tmp = new _node(*p);
            if (count == pos)
            {
                loop = *tmp;
            }
            count++;
            tmp = &((*tmp)->_next);
        }

        (*tmp) = loop;
        m_size_ = list.size();
    }

    ~list()
    {
        _node *tmp = m_head_;
        while (m_size_ > 0)
        {
            m_size_--;
            m_head_ = tmp->_next;
            delete tmp;
            tmp = m_head_;
        }
    }

    /**
     * @brief 检查链表是否有环
     * @return 有环,返回环入口节点;无环,返回nullptr
     */
    _node *check_loop()
    {
#define USE_HASHTABLE 0
#if USE_HASHTABLE
        /* 时间复杂度O(n), 空间复杂度O(n) */
        _node *tmp = m_head_;
        unordered_set<_node*> set;

        while (tmp)
        {
            if (set.find(tmp) != set.end())
            {
                break;
            }
            set.insert(tmp);
            tmp = tmp->_next;
        }

        return tmp;
#else
        /* 使用快慢指针 */
        /* 分析: (s:慢指针 q:快指针)
                链表共有size个节点,环有loop_size个节点(0 <= loop_size <= size)
                非环节点有(size - loop_size)个
                s到达环入口节点时 (size - loop_size), q位于2 * (size - loop_size)
                环上相距 (size - loop_size) % loop_size
                所以在 s 在 (size - loop_size) % loop_size + (size - loop_size)
                相遇

                size 7, loop_size 3
                    s = size - loop_size = 4到达入口节点
                    此时,q = (2 * s - s) % loop_size + s = 5

                    s记作 unloop_size
                    s与q相距 loop_size - unloop_size % loop_size = 2
                    所以在 s = 6 时相遇

                    再次执行快指针 unloop_size 次，慢指针移动至
                    loop_size - unloop_size % loop_size + unloop_size % loop_size

        */
        _node * ret = nullptr;
       if (!m_head_ || !m_head_->_next)
       {
           return ret;
       }

       _node *quick = m_head_;
       _node *slow = m_head_;

       while (quick && slow)
       {
           if (!quick->_next || !quick->_next->_next)
           {
               quick = nullptr;
               break;
           }
           else
           {
               quick = quick->_next->_next;
           }
           slow = slow->_next;

            if (quick == slow)
           {
               break;
           }
       }

       if (quick)
       {
           while (quick != slow)
           {
               quick = quick->_next;
               slow = slow->_next;
           }
           ret = quick;
       }

        return ret;
#endif // USE_HASHTABLE
#undef USE_HASHTBALE
    }

    friend ostream& operator<< <T>(ostream& o, list &l);
private:
    _node *m_head_;
    int m_size_;
};

template <typename T>
ostream& operator<<(ostream& o, list<T> &l)
{
    using _node = typename list<T>::_node;

    int s = l.m_size_;
    _node *tmp = l.m_head_;

    o << '{';
    while (s > 0)
    {
        s--;
        o << tmp->_value << "->";
        tmp = tmp->_next;
    }
    o << '(';
    if (tmp)
    {
        o << tmp->_value;
    }
    else
    {
        o << "null";
    }
    o << ')';
    o << '}';
    return o;
}

template <typename T>
using node_t = typename list<T>::_node;

class test
{
    static void test_check_loop_run(list<int>& l)
    {
        cout << l << '\n';

        node_t<int> *node = l.check_loop();
        cout << "check result: ";
        if (node)
        {
            cout << node->_value << "\n";
        }
        else
        {
            cout << "(null)" << "\n";
        }
    }
public:
    static void test_check_loop()
    {
        list<int> *l = new list<int>({5, 6, 1, 2, 3, 7}, 10);
        test_check_loop_run(*l);
        delete l;

        l = new list<int>({5, 6, 1, 2, 3, 7}, 3);
        test_check_loop_run(*l);
        delete l;
    }
};

// i % size = (2 * i + k) % size
// loop_size <= total
void print_sq_pointer_i(int total, int loop_size)
{
    int non_loop = total - loop_size;
    int low_pos = 0;
    int quick_pos = non_loop;
    while ((low_pos % loop_size) != ((2 * low_pos + quick_pos) % loop_size))
    {
        low_pos++;
    }
    low_pos += non_loop;
    quick_pos += non_loop;
    std::cout << "total: " << total
        << ", loop_size: " << loop_size
        << " ==> (" << low_pos << ", " << quick_pos << ")\n";
}

int main()
{
    test::test_check_loop();

    print_sq_pointer_i(6, 3);
    return 0;
}