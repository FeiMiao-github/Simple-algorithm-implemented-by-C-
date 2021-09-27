/**
 * for-loop 遍历二叉树 
 */

#include <iostream>
#include <stack>
#include <queue>
#include <functional>

using std::queue;
using std::stack;
using std::function;
using std::cout;

template <typename T>
class Traversal;

template <typename T>
class BTree
{
public:
    friend class Traversal<T>;

    struct Node
    {
        T _val;
        Node *_left;
        Node *_right;

        Node(const T &val, Node *left = nullptr, Node *right = nullptr)
            : _val(val),
              _left(left),
              _right(right)
        {
        }
    };

    BTree()
        : _root(nullptr)
    {
    }

    ~BTree()
    {
        queue<Node*> q;
        q.push(_root);
        _root = nullptr;

        while (!q.empty())
        {
            Node* tmp = q.front();
            q.pop();

            if (tmp->_left)
            {
                q.push(tmp->_left);
            }

            if (tmp->_right)
            {
                q.push(tmp->_right);
            }

            delete tmp;
        }
    }

    void Append(T &v)
    {
        Append({v});
    }
    
    void Append(const std::initializer_list<T> &list)
    {
        auto p = list.begin();
        auto check_finish = [&p, &list]() -> auto
        {
            return list.end() == p;
        };
        auto insert_at = [&p, &list](Node* &pos)
        {
            if (pos == nullptr)
            {
                if (p != list.end())
                {
                    pos = new Node(*p);
                    p++;
                }
            }
        };

        if (check_finish())
        {
            return;
        }

        insert_at(_root);
        if (check_finish())
        {
            return;
        }

        queue<Node*> q;
        q.push(_root);
        while (!q.empty())
        {
            Node *tmp = q.front();
            q.pop();

            insert_at(tmp->_left);
            if (check_finish())
            {
                return;
            }

            insert_at(tmp->_right);
            if (check_finish())
            {
                return;
            }

            q.push(tmp->_left);
            q.push(tmp->_right);
        }
    }

private:
    Node *_root;
};

template <typename T>
class Traversal
{
public:
    typedef typename BTree<T>::Node Node;
    /**
     * root -> left -> right
     */
    static void PreOrderTraversal(BTree<T> &btree, const function<void(Node*)> &f)
    {
        if (!btree._root)
        {
            return;
        }

        stack<Node*> s;
        s.push(btree._root);
        while (!s.empty())
        {
            Node* tmp = s.top();
            s.pop();

            f(tmp);
            if (tmp->_right)
            {
                s.push(tmp->_right);
            }

            if (tmp->_left)
            {
                s.push(tmp->_left);
            }
        }
    }

       /**
     * left -> root -> right
     */
    static void InOrderTraversal(BTree<T> &btree, const function<void(Node*)> &f)
    {
        stack<Node*> s;
        Node *tmp = btree._root;

        // 实现一
        // while (true)
        // {
        //     while (tmp)
        //     {
        //         s.push(tmp);
        //         tmp = tmp->_left;
        //     }

        //     if (s.empty())
        //     {
        //         return;
        //     }
        //     else
        //     {
        //         tmp = s.top();
        //         s.pop();
        //         f(tmp);
        //         tmp = tmp->_right;
        //     }
        // }

        // 实现二
        while (!s.empty() || tmp)
        {
            if (tmp)
            {
                s.push(tmp);
                tmp = tmp->_left;
            }
            else
            {
                tmp = s.top();
                s.pop();

                f(tmp);
                tmp = tmp->_right;
            }
        }
    }

    /**
     * left -> right -> root
     */
    static void PostOrderTraversal(BTree<T> &btree, const function<void(Node*)> &f)
    {
        stack<Node*> s;
        Node *lastPeek = nullptr;
        Node *tmp = btree._root;
        while (!s.empty() || tmp)
        {
            while (tmp)
            {
                s.push(tmp);
                tmp = tmp->_left;
            }

            tmp = s.top();
            if (tmp->_right && tmp->_right != lastPeek)
            {
                tmp = tmp->_right;
            }
            else
            {
                f(tmp);
                s.pop();
                lastPeek = tmp;
                tmp = nullptr;
            }
        }
    }
};

class Test
{
    typedef BTree<int> BTree_t;
    typedef BTree_t::Node Node_t;
    typedef Traversal<int> Traversal_t;

    static void PrintNode(Node_t *node)
    {
        cout << node->_val << "->";
    }

public:
/**
 *                1
 *              /    \
 *             2      3
 *           /  \    /  \
 *          4    5  6    7 
 */
    static void Test_PreOrderTraversal()
    {
        cout << "Test_PreOrderTraversal: \n";

        BTree_t btree;
        btree.Append({1, 2, 3, 4, 5, 6, 7});
        Traversal_t::PreOrderTraversal(btree, PrintNode);

        cout << "\n\n";
    }

    static void Test_InOrderTraversal()
    {
        cout << "Test_InOrderTraversal: \n";

        BTree_t btree;
        btree.Append({1, 2, 3, 4, 5, 6, 7});
        Traversal_t::InOrderTraversal(btree, PrintNode);

        cout << "\n\n";
    }

    static void Test_PostOrderTraversal()
    {
        cout << "Test_PostOrderTraversal: \n";

        BTree_t btree;
        btree.Append({1, 2, 3, 4, 5, 6, 7});
        Traversal_t::PostOrderTraversal(btree, PrintNode);

        cout << "\n\n";
    }
};

int main()
{
    Test::Test_PreOrderTraversal();
    Test::Test_InOrderTraversal();
    Test::Test_PostOrderTraversal();
    return 0;
}