/**
 *  target: 复制一个带有随机节点的链表
 *  
 */

#include <iostream>
#include <stack>
#include <unordered_map>

using std::ostream;
using std::cout;
using std::stack;
using std::unordered_map;

template <typename T>
class list;

template <typename T>
ostream& operator<<(ostream& out, list<T> &l);

template <typename T>
bool operator==(list<T> &l1, list<T> &l2);

/**
 *  带有随机节点的链表
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

    list(const std::initializer_list<T> &arr)
        : m_head_(nullptr),
          m_size_(0)
    {
        for (auto && v: arr)
        {
            push_back(v);
        }
    }

// #define USE_HASHTABLE
    /* 定义复制构造函数 */
    list(const list &origin)
        : m_head_(nullptr),
          m_size_(origin.m_size_)
    {
#define USE_HASHTABLE true
#if USE_HASHTABLE

        unordered_map<_node*,_node*> nodemap;
        _node *tmp = origin.m_head_;
        while (tmp)
        {
            nodemap.insert({tmp, new _node(tmp->_value)});
            tmp = tmp->_next;
        }

        for (auto p = nodemap.begin(); p != nodemap.end(); p++)
        {
            p->second->_next = nodemap[p->first->_next];
            p->second->_rand = nodemap[p->first->_rand];
        }
        m_head_ = nodemap[origin.m_head_];

#else

        _node *tmp = origin.m_head_;
        while (tmp)
        {
            _node *next = tmp->_next;
            tmp->_next = new _node(tmp->_value, next);
            tmp = next;
        }

        tmp = origin.m_head_;
        while (tmp)
        {
            _node *next = tmp->_next;
            if (tmp->_rand)
            {
                next->_rand = tmp->_rand->_next;
            }
            tmp = next->_next;
        }

        tmp = origin.m_head_;
        if (!tmp)
        {
            return;
        }
        else
        {
            m_head_ = tmp->_next;
            tmp->_next = m_head_->_next;
            tmp = tmp->_next;
        }

        _node *h = m_head_;
        while (tmp)
        {
            h->_next = tmp->_next;
            h = h->_next;
            tmp->_next = h->_next;
            tmp = tmp->_next;
        }
#endif
    }
#undef USE_HASHTABLE

    ~list()
    {
        _node *tmp = m_head_;
        while (tmp)
        {
            tmp = m_head_->_next;
            delete m_head_;
            m_head_ = tmp;
        }
    }

    list& operator=(const list &l) = delete;

    // 在头部插入新节点
    void push(T val)
    {
        _node *tmp = new _node(val, m_head_);
        m_head_ = tmp;

        m_size_++;
    }

    // 在尾部插入新节点
    void push_back(T val)
    {
        _node** tmp = &m_head_;
        while (*tmp)
        {
            tmp = &((*tmp)->_next);
        }

        (*tmp) = new _node(val);

        m_size_++;
    }

    // 从头部弹出节点
    bool pop(T &out)
    {
        _node *tmp = m_head_;
        if (tmp == nullptr)
        {
            return false;
        }

        out = tmp->_value;
        m_head_ = m_head_->_next;
        delete tmp;

        m_size_--;
        return true;
    }

    // 从尾部弹出节点
    bool pop_back(T &out)
    {
        if (m_head_ == nullptr)
        {
            return false;
        }

        _node **tmp = &m_head_;
        while ((*tmp)->_next != nullptr)
        {
            tmp = &((*tmp)->_next);
        }
        out = (*tmp)->_value;
        delete *tmp;
        *tmp = nullptr;

        m_size_--;
        return true;
    }

    int size() const
    {
        return m_size_;
    }

    /**
     * 为 _node._rand 节点随机赋值 
     */
    void set_random_node()
    {
        std::srand(time(nullptr));

        _node *tmp = m_head_;
        while (tmp)
        {
            int i = rand() % (m_size_ + 1);
            tmp->_rand = get_node(i);
            tmp = tmp->_next;
        }
    }

    friend ostream& operator<< <>(ostream& out, list &l);
    friend bool operator== <>(list<T> &l1, list<T> &l2);
private:
    /**
     * 获取第i个节点(0 <= i <= size - 1)
     */
    _node *get_node(int i)
    {
        if (i < 0 || i >= m_size_)
        {
            return nullptr;
        }

        _node *ret = m_head_;
        while (i > 0)
        {
            ret = ret->_next;
            i--;
        }
        return ret;
    }
private:
    _node *m_head_;
    int m_size_;
};

template <typename T>
ostream& operator<<(ostream& out, list<T> &l)
{
    typename list<T>::_node* tmp = l.m_head_;
    out << "{";
    while (tmp)
    {

        out << tmp->_value << "->";
        if (tmp->_rand)
        {
            out << tmp->_rand->_value;
        }
        else
        {
            out << "(null)";
        }
        out << ",";
        tmp = tmp->_next;
    }
    out << "}"; 
    return out;
}

template <typename T>
bool operator==(list<T> &l1, list<T> &l2)
{
    if (l1.size() != l2.size())
    {
        return false;
    }

    typename list<T>::_node *p1 = l1.m_head_;
    typename list<T>::_node *p2 = l2.m_head_;

    while (p1)
    {
        if (p1->_value != p2->_value)
        {
            return false;
        }
        p1 = p1->_next;
        p2 = p2->_next;
    }

    return true;
}

class test
{
public:
    static void test_base()
    {
        cout << "===========================test_base=======================\n";
        list<int> l1{1, 2, 3, 4};
        cout << "l1: " << l1 << "\n";
    }

    static void test_set_random()
    {
        cout << "======================test_set_random======================\n";
        list<int> l1{1, 2, 3, 4};
        l1.set_random_node();
        cout << "l1: " << l1 << "\n";
    }

    static void test_list_copy_constructor()
    {
        cout << "=================test_list_copy_constructor================\n";
        list<int> l1{1, 2, 3, 4};
        l1.set_random_node();
        cout << "l1: " << l1 << "\n";

        list<int> l2 = l1;
        cout << "l2: " << l2 << "\n";
    }
};

int main()
{
    test::test_base();
    test::test_set_random();
    test::test_list_copy_constructor();
    return 0;
}