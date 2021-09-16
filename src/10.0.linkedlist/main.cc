/**
 * 自定义一个单链表
 *      实现单向链表反转
 */

#include <iostream>
#include <stack>

using std::ostream;
using std::cout;
using std::stack;

template <typename T>
class list;

template <typename T>
ostream& operator<<(ostream& out, list<T> &l);

template <typename Container, typename T>
class iterator
{
public:
    virtual ~iterator() = default;
    virtual bool next(T &val) = 0;
    virtual void init() = 0 ;
};

template <typename T>
class container
{
public:
    virtual ~container() = default;
};

template <typename T>
class list
    : public container<T>
{
public:
    struct _node
    {
        T _value;
        _node *_next;

        _node(T val = 0, _node* next = nullptr)
            : _value(val),
              _next(next)
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

    /*
     * 反转单链表
     */
    void reverse()
    {
        _node* tmp = m_head_;
        _node* next = nullptr;

        if (tmp)
        {
            next = tmp->_next;
            tmp->_next = nullptr;
        }

        while (next)
        {
            m_head_ = next;
            next = m_head_->_next;
            m_head_->_next = tmp;
            tmp = m_head_;
        }
    }

    int size() const
    {
        return m_size_;
    }

    /**
     * 单向链表回文判断(使用栈)
     *      @return 如果是回文,返回true;如果不是,返回false
     */
    bool is_plalindrome1()
    {
        if (size() < 2)
        {
            return true;
        }

        stack<T> st;
        _node *tmp = m_head_;
        while (tmp)
        {
            st.push(tmp->_value);
            tmp = tmp->_next;
        }
        tmp = m_head_;
        while (tmp)
        {
            if (st.top() != tmp->_value)
            {
                return false;
            }
            st.pop();
            tmp = tmp->_next;
        }
        return true;
    }

    /**
     * 单向链表回文判断(使用半栈), 仅仅遍历一次
     *      @return 如果是回文,返回true;如果不是,返回false
     */
    bool is_plalindrome2()
    {
        if (size() < 2)
        {
            return true;
        }

        stack<T> st;
        _node *fast = nullptr, *slow = nullptr;
        fast = slow = m_head_;
        while (fast && fast->_next)
        {
            st.push(slow->_value);
            fast = fast->_next->_next;
            slow = slow->_next;
        }

        if (fast && fast->_next == nullptr) // 奇数项
        {
            slow = slow->_next;
        }

        while (slow)
        {
            if (slow->_value != st.top())
            {
                return false;
            }

            slow = slow->_next;
            st.pop();
        }

        return true;
    }

    /**
     * @brief 根据一个值把链表分为三部分,左部分小于给定值,中间部分等于给定值,
     * 右侧部分大于给定值。保持相对位置不变
     * @param num 给定值
     * 
     */
    void divide(T num)
    {
        _node* l_s = nullptr;
        _node* l_e = nullptr;
        _node* m_s = nullptr;
        _node* m_e = nullptr;
        _node* r_s = nullptr;
        _node* r_e = nullptr;
        _node* pos = m_head_;

        while (pos)
        {
            if (pos->_value == num)
            {
                if (m_s == nullptr)
                {
                    m_s = pos;
                }
                else
                {
                    m_e->_next = pos;
                }
                m_e = pos;
            }
            else if (pos->_value > num)
            {
                if (r_s == nullptr)
                {
                    r_s = pos;
                }
                else
                {
                    r_e->_next = pos;
                }
                r_e = pos;
            }
            else
            {
                if (l_s == nullptr)
                {
                    l_s = pos;
                }
                else 
                {
                    l_e->_next = pos;
                }
                l_e = pos;
            }

            pos = pos->_next;
        }

        if (l_s == nullptr)
        {
            l_s = m_s;
            l_e = m_e;
            m_s = r_s;
            m_e = r_e;
            r_s = r_e = nullptr;
        }
        else if (m_s == nullptr)
        {
            m_s = r_s;
            m_e = r_e;
            r_s = r_e = nullptr;
        }

        if (l_s == nullptr)
        {
            l_s = m_s;
            l_e = m_e;
            m_s = m_e = nullptr;
        }

        if (l_s)
        {
            l_e->_next = m_s;
        }

        if (m_s)
        {
            m_e->_next = r_s;
        }
        m_head_ = l_s;
    }

    friend class ::iterator<list<T>, T>;
private:
    _node *m_head_;
    int m_size_;
};

template <typename T>
class iterator<list<T>, T>
    : public iterator<container<T>, T>
{
public:
    iterator(list<T>* cont)
        : m_container_(cont),
          m_cur_(cont->m_head_)
    {}
    virtual ~iterator() = default;
    virtual bool next(T &val) override
    {
        if (m_cur_)
        {
            val = m_cur_->_value;
            m_cur_ = m_cur_->_next;
            return true;
        }

        return false;
    }

    virtual void init() override
    {
        m_cur_ = m_container_->m_head_;
    }
private:
    list<T> *m_container_;
    typename list<T>::_node *m_cur_;
};

template <typename Container, typename T>
class iterator_proxy
: public ::iterator<Container, T>
{
public:
    iterator_proxy(Container *cont)
        : iterator<Container, T>(cont)
    {
    }

    bool next(T &val) override
    {
        return iterator<Container, T>::next(val);
    }

    void init() override
    {
        return iterator<Container, T>::init();
    }
};

template <typename T>
ostream& operator<<(ostream& out, list<T> &l)
{
    iterator_proxy<list<T>, T> it(&l);
    T val;
    out << "{";
    while (it.next(val))
    {
        out << val << ", ";
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

    iterator_proxy<list<T>, T> it1(&l1);
    iterator_proxy<list<T>, T> it2(&l2);
    T val1, val2;
    while (it1.next(val1) && it2.next(val2))
    {
        if (val1 != val2)
        {
            return false;
        }
    }
    return true;
}

/**
 * 输出两个有序链表的公共部分
 * @param l1 增序链表
 * @param l2 增序链表
 * @param out 公共部分
 */
template <typename T>
void common(list<T> &l1, list<T> &l2, list<T> &out)
{
    iterator_proxy<list<T>, T> it1(&l1);
    iterator_proxy<list<T>, T> it2(&l2);
    T val1, val2;
    bool s1 = it1.next(val1);
    bool s2 = it2.next(val2);
    if ((s1 && s2) == false)
    {
        return;
    }

    while (s1 && s2)
    {
        if (val1 == val2)
        {
            out.push_back(val1);
            s1 = it1.next(val1);
            s2 = it2.next(val2);
        }
        else if (val1 > val2)
        {
            s2 = it2.next(val2);
        }
        else
        {
            s1 = it1.next(val1);
        }
    }
}

/**
 * 单向链表回文判断(快慢指针实现)
 *      @param l 输入链表
 *      @return 如果是回文,返回true;如果不是,返回false
 */
template <typename T>
bool is_plalindrome1(list<T> &l)
{

    return false;
}

class test
{
public: 
    static void test_base()
    {
        cout << "=====================test_base===================\n";
        list<double> l;
        l.push(1);
        l.push(2);
        l.push(3);
        l.push(4);
        cout << l << "\n";
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        cout << l << "\n";

        list<double> l2{4, 3, 2, 1, 2, 3, 4};
        cout << "l == l2: " << ((l == l2) ? "true" : "false") << "\n";

        double tmp;
        l.pop(tmp);
        l.pop_back(tmp);
        cout << l << "\n";

        while (l.pop(tmp))
        {
        }
        cout << l << "\n";
    }

    static void test_reverse()
    {
        cout << "=====================test_reverse===================\n";
        list<double> l;
        /* 测试: 链表反转 */
        l.push(1);
        l.push(2);
        l.push(3);
        l.push(4);
        l.push(5);
        l.push(6);
        cout << "origin: " << l << "\n";
        l.reverse();
        cout << "reverse: " << l << "\n";
    }

    static void test_common()
    {
        cout << "=====================test_common===================\n";
        /* 测试: 输出两个有序链表的公共部分 */
        list<int> l1, l2, out;
        l1.push_back(2);
        l1.push_back(3);
        l1.push_back(5);
        l1.push_back(6);
        l1.push_back(7);

        l2.push_back(1);
        l2.push_back(2);
        l2.push_back(3);
        l2.push_back(6);
        l2.push_back(8);

        common(l1, l2, out);
        cout << "l1 : " << l1 << "\n";
        cout << "l2 : " << l2 << "\n";
        cout << "out: " << out << "\n";
    }

    static void test_is_plalindrome()
    {
        cout << "=====================test_is_plalindrome===================\n";
        list<double> l1{4, 3, 2, 1, 2, 3, 4};
        bool ret = l1.is_plalindrome1();
        cout << "l1 is plalindrome1 list: " << ret << "\n";
        ret = l1.is_plalindrome2();
        cout << "l1 is plalindrome2 list: " << ret << "\n"; 

        double val;
        l1.pop(val);
        ret = l1.is_plalindrome1();
        cout << "l1 is plalindrome1 list: " << ret << "\n"; 
        ret = l1.is_plalindrome2();
        cout << "l1 is plalindrome2 list: " << ret << "\n"; 

        list<double> l2 {4, 3, 2, 2, 3, 4};
        ret = l2.is_plalindrome1();
        cout << "l2 is plalindrome1 list: " << ret << "\n";
        ret = l2.is_plalindrome2();
        cout << "l2 is plalindrome2 list: " << ret << "\n"; 

        list<int> l3{3, 2};
        ret = l3.is_plalindrome1();
        cout << "l3 is plalindrome1 list: " << ret << "\n";
        ret = l3.is_plalindrome2();
        cout << "l3 is plalindrome2 list: " << ret << "\n";

        list<int> l4{3, 3};
        ret = l4.is_plalindrome1();
        cout << "l4 is plalindrome1 list: " << ret << "\n";
        ret = l4.is_plalindrome2();
        cout << "l4 is plalindrome2 list: " << ret << "\n"; 
    }

    static void test_divide()
    {
        cout << "=====================test_divide===================\n";

        list<double> l1{4, 3, 2, 1, 2, 3, 4};
        cout << "l1: " << l1 << "\n";
        l1.divide(3);
        cout << "l1: " << l1 << "\n";

        list<double> l2{5, 4, 3, 2, 1, 2, 3, 4};
        cout << "l2: " << l2 << "\n";
        l2.divide(3);
        cout << "l2: " << l2 << "\n";

        double value;
        while (l2.pop(value));
        cout << "l2: " << l2 << "\n";
        l2.divide(3);
        cout << "l2: " << l2 << "\n";

        l2.push(1);
        cout << "l2: " << l2 << "\n";
        l2.divide(3);
        cout << "l2: " << l2 << "\n";

        l2.push(4);
        cout << "l2: " << l2 << "\n";
        l2.divide(3);
        cout << "l2: " << l2 << "\n";
    }
};

int main()
{
    test::test_base();
    test::test_common();
    test::test_reverse();
    test::test_is_plalindrome();
    test::test_divide();
    return 0;
}