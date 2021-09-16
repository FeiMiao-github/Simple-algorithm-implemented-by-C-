/**
 * 自定义一个双向链表
 *      实现双向链表反转
 */

#include <iostream>

using std::ostream;
using std::cout;

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
        _node *_prev;

        _node(T val = 0, _node* next = nullptr, _node* prev = nullptr)
            : _value(val),
              _next(next),
              _prev(prev)
        {}
    };

    list()
        : m_head_(nullptr),
          m_tail_(nullptr),
          m_size_(0)
    {
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
        if (m_head_)
        {
            m_head_->_prev = tmp; 
        }
        m_head_ = tmp;
        if (m_tail_ == nullptr)
        {
            m_tail_ = m_head_;
        }
        m_size_++;
    }

    // 在尾部插入新节点
    void push_back(T val)
    {
        _node *tmp = new _node(val, nullptr, m_tail_);
        if (m_tail_)
        {
            m_tail_->_next = tmp;
        }
        m_tail_ = tmp;
        if (m_head_ == nullptr)
        {
            m_head_ = m_tail_;
        }
        m_size_++;
    }

    // 从头部弹出节点
    bool pop(T &out)
    {
        if (m_head_)
        {
            _node *next = nullptr;
            out = m_head_->_value;
            next = m_head_->_next;
            delete m_head_;
            m_head_ = next;
            m_size_--;
        }
        else
        {
            return false;
        }

        if (m_head_ == nullptr)
        {
            m_tail_ = nullptr;
        }
        else
        {
            m_head_->_prev = nullptr;
        }
        return true;
    }

    // 从尾部弹出节点
    bool pop_back(T &out)
    {
        if (m_tail_)
        {
            _node *prev = m_tail_->_prev;
            out = m_tail_->_value;
            delete m_tail_;
            m_tail_ = prev;
            m_size_--;
        }
        else
        {
            return false;
        }

        if (m_tail_ == nullptr)
        {
            m_head_ = nullptr;
        }
        else
        {
            m_tail_->_next = nullptr;
        }
        return true;
    }

    void reverse()
    {
        _node* prev = nullptr, *next = nullptr;
        _node* tmp = m_tail_;
        while (tmp)
        {
            prev = tmp->_prev;
            next = tmp->_next;
            tmp->_prev = next;
            tmp->_next = prev;
            tmp = prev;
        }
        tmp = m_tail_;
        m_tail_ = m_head_;
        m_head_ = tmp;        
    }

    int size() const
    {
        return m_size_;
    }

    friend class ::iterator<list<T>, T>;
private:
    _node *m_head_;
    _node *m_tail_;
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
    virtual bool next(T &val)
    {
        if (m_cur_)
        {
            val = m_cur_->_value;
            m_cur_ = m_cur_->_next;
            return true;
        }

        return false;
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
private:
    iterator<Container, T>* m_iter_;
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

int main()
{
    list<double> l;
    l.push(1.);
    l.push(2.);
    l.push(3.);
    cout << l << "\n";

    l.push_back(1.);
    l.push_back(2.);
    l.push_back(3.);
    cout << l << "\n";

    double val;
    l.pop(val);
    cout << l << "\n";

    l.pop_back(val);
    cout << l << "\n";

    while (l.pop_back(val)) {}
    cout << l << "\n";

    l.push_back(1.);
    l.push_back(2.);
    l.push_back(3.);
    l.push_back(4.);
    cout << "origin : " << l << "\n";
    l.reverse();
    cout << "reverse: " << l << "\n";
    return 0;
}