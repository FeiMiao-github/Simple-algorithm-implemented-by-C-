/**
 *  target: 获取两个链表(不确定是否有环)的相交节点
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
        m_head_ = nullptr;
    }

    /**
     * @brief 检查链表是否有环
     * @return 有环,返回环入口节点;无环,返回nullptr
     * 
     * 时间复杂度 O(n)
     */
    _node *check_loop()
    {
        if (!m_head_ || !m_head_->_next)
        {
            return nullptr;
        }

        _node *slow = m_head_->_next;
        _node *quick = slow->_next;
        while (true)
        {
            if (!quick || !quick->_next)
            {
                return nullptr;
            }
            else if (quick == slow)
            {
                break;
            }

            quick = quick->_next->_next;
            slow = slow->_next;
        }

        quick = m_head_;
        while (quick != slow)
        {
            quick = quick->_next;
            slow = slow->_next;
        }

        return slow;
    }

    /**
     * 获取链表公共节点
     *  分析:
     *         有环
     *               两个均有环才能相交
     *                      交点在环上 固定一个链表的环入口点,移动另一个环的入口点
     *                      交点在环外 共用环入口点
     *         无环
     *              两个均无环才有可能相交
     */
    _node *find_common_node(list &l)
    {
        _node *loop_entry = check_loop();
        _node *l_loop_entry = l.check_loop();

        if (loop_entry == nullptr && l_loop_entry == nullptr)
        {
            return find_common_node_noloop(l);
        }
        else if (loop_entry == l_loop_entry)
        {
            return find_common_node_loop_same_entry(l, loop_entry);
        }
        else if (loop_entry != nullptr && l_loop_entry != nullptr)
        {
            return find_common_node_loop_different_entry(
                loop_entry, l_loop_entry
            );
        }

        return nullptr;
    }

    void append(list &l)
    {
        append(l.m_head_);
    }

    void append(_node *node)
    {
        auto tmp = m_head_;
        if (m_head_ == nullptr)
        {
            m_head_ = node;
            return;
        }

        while (tmp->_next)
        {
            tmp = tmp->_next;
        }

        tmp->_next = node;
    }

    _node* get_node(int i)
    {
        _node* tmp = m_head_;
        while (i-- > 0 && tmp)
        {
            tmp = tmp->_next;
        }
        return tmp;
    }

    friend ostream& operator<< <T>(ostream& o, list &l);
private:
    _node *find_common_node_noloop(list &l)
    {
        return find_same_node(l);
    }
    
    _node *find_common_node_loop_same_entry(list &l, _node* entry)
    {
        return find_same_node(l, entry);
    }

    _node *find_common_node_loop_different_entry(
        _node* entry, _node* lentry
    )
    {
        _node *tmp = lentry;
        _node *ret = nullptr;

        while (tmp->_next != lentry)
        {
            if (tmp->_next == entry)
            {
                ret = entry;
                break;
            }
            tmp = tmp->_next;
        }

        return ret;
    }

    int get_num_from_head(_node *node = nullptr)
    {
        _node* tmp = m_head_;
        int ret = 0;
        while (tmp != node && ret <= m_size_)
        {
            ret ++;
            tmp = tmp->_next;
        }
        return ret;
    }

    _node* find_same_node(list &l, _node *end = nullptr)
    {
        int size = get_num_from_head(end);
        int lsize = l.get_num_from_head(end);

        _node *long_list = m_head_, *short_list = l.m_head_;
        int n = size - lsize;
        if (lsize > size)
        {
            n = lsize - size;
            long_list = l.m_head_;
            short_list = m_head_;
        }
        
        while (n-- > 0)
        {
            long_list = long_list->_next;
        }
        while (long_list != short_list)
        {
            long_list = long_list->_next;
            short_list = short_list->_next;
        }
        return long_list;
    }
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
    static void print_node(node_t<int> *node)
    {
        if (node)
        {
            cout << node->_value << "\n";
        }
        else
        {
            cout << "(null)" << "\n";
        }
    }

    static void test_check_loop_run(list<int>& l)
    {
        cout << l << '\n';

        node_t<int> *node = l.check_loop();
        cout << "check result: ";
        print_node(node);
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

        l = new list<int>({1}, 0);
        test_check_loop_run(*l);
        delete l;
    }

private:
    static void test_find_common_node_run(list<int> &l1, list<int> &l2)
    {
        node_t<int> *node = l1.find_common_node(l2);
        cout << "common node result: ";
        print_node(node);
    }

public:
    static void test_find_common_node()
    {
        cout << "test_find_common_node : \n";

        list<int> *l1 = new list<int>({5, 6, 1, 2, 3, 7}, -1);
        list<int> *l2 = new list<int>({2, 8}, -1);
        list<int> *common = new list<int>({11, 14}, -1);
        cout << "l1: " << *l1 << "\n";
        cout << "l2: " << *l2 << "\n";
        test_find_common_node_run(*l1, *l2);

        cout << "\n";

        cout << "l1: " << *l1 << "\n";
        cout << "l2: " << *l2 << "\n";
        cout << "common: " << *common << "\n";
        l1->append(*common);
        l2->append(*common);
        test_find_common_node_run(*l1, *l2);

        delete l1;
        delete l2;
        delete common;

        cout << "\n";
        l1 = new list<int>({5, 6, 1, 2, 3, 7}, -1);
        l2 = new list<int>({2, 8}, -1);
        common = new list<int>({12, 15, 17, 11, 14}, 2);
        l1->append(*common);
        l2->append(*common);
        cout << "l1: " << *l1 << "\n";
        cout << "l2: " << *l2 << "\n";
        cout << "common: " << *common << "\n";
        test_find_common_node_run(*l1, *l2);
        delete l1;
        delete l2;
        delete common;

        cout << "\n";
        l1 = new list<int>({5, 6, 1, 2, 3, 7}, -1);
        l2 = new list<int>({2, 8}, -1);
        common = new list<int>({12, 15, 17, 11, 14}, 0);
        l1->append(common->get_node(1));
        l2->append(common->get_node(3));
        cout << "l1: " << *l1 << "\n";
        cout << "l2: " << *l2 << "\n";
        cout << "common: " << *common << "\n";
        test_find_common_node_run(*l1, *l2);
        delete l1;
        delete l2;
        delete common;
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
    cout << "\n\n";
    // print_sq_pointer_i(6, 3);
    test::test_find_common_node();
    return 0;
}