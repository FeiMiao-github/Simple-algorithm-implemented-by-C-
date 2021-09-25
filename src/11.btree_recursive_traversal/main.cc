/**
 *  二叉树递归遍历
 */

#include <iostream>
#include <queue>
#include <functional>

using std::queue;
using std::function;
using std::cout;

template <typename T>
class BTree
{
public:
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

    /**
     * root -> left -> right
     */
    void PreOrderTraversal(const function<void(Node*)> &f)
    {
        PreOrderTraversalSub(f, _root);
    }

    /**
     * left -> root -> right
     */
    void InOrderTraversal(const function<void(Node*)> &f)
    {
        InOrderTraversalSub(f, _root);
    }

    /**
     * left -> right -> root
     */
    void PostOrderTraversal(const function<void(Node*)> &f)
    {
        PostOrderTraversalSub(f, _root);
    }

private:
    void PreOrderTraversalSub(const function<void(Node*)> &f, Node *node)
    {
        if (node)
        {
            f(node);
            PreOrderTraversalSub(f, node->_left);
            PreOrderTraversalSub(f, node->_right);
        }
    }

    void InOrderTraversalSub(const function<void(Node*)> &f, Node *node)
    {
        if (node)
        {
            InOrderTraversalSub(f, node->_left);
            f(node);
            InOrderTraversalSub(f, node->_right);
        }
    }

    void PostOrderTraversalSub(const function<void(Node*)> &f, Node *node)
    {
        if (node)
        {
            PostOrderTraversalSub(f, node->_left);
            PostOrderTraversalSub(f, node->_right);
            f(node);
        }
    }

private:
    Node *_root;
};

class Test
{
    typedef BTree<int>::Node Node_t;

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

        BTree<int> btree;
        btree.Append({1, 2, 3, 4, 5, 6, 7});
        btree.PreOrderTraversal(PrintNode);

        cout << "\n\n";
    }

    static void Test_InOrderTraversal()
    {
        cout << "Test_InOrderTraversal: \n";

        BTree<int> btree;
        btree.Append({1, 2, 3, 4, 5, 6, 7});
        btree.InOrderTraversal(PrintNode);

        cout << "\n\n";
    }

    static void Test_PostOrderTraversal()
    {
        cout << "Test_PostOrderTraversal: \n";

        BTree<int> btree;
        btree.Append({1, 2, 3, 4, 5, 6, 7});
        btree.PostOrderTraversal(PrintNode);

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