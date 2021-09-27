
/**
 * 打印一个二叉树
 */

#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using std::cout;
using std::stack;
using std::queue;
using std::vector;
using std::swap;
using std::string;
using std::to_string;

template <typename T>
class Printer;

template <typename T>
class BTree
{
public:
    friend class Printer<T>;

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

    void Size(size_t &width, size_t &height)
    {
        width = 0;
        height = 0;
        vector<Node*> current, child;
        if (_root)
        {
            current.push_back(_root);
        }
        while (!current.empty())
        {
            height++;
            if (current.size() > width)
            {
                width = current.size();
            }

            for (auto && e : current)
            {
                if (e->_left)
                {
                    child.push_back(e->_left);
                }
                if (e->_right)
                {
                    child.push_back(e->_right);
                }
            }

            swap(current, child);
            child.clear();
        }
    }

private:
    Node *_root;
};

template <typename T>
class Printer
{
public:
    typedef BTree<T> BTree_t;
    typedef typename BTree<T>::Node Node_t;

    void operator()(BTree_t &btree)
    {
        vector<string> treestr;
        Generate(btree._root, treestr);
        Print(treestr);
    }

private:

    void Generate(
        Node_t *root, vector<string> &out
    )
    {
        Generate(root, out, "", 0);
    }

    void Generate(
        Node_t *root,
        vector<string> &out,
        const string &prefix,
        int depth
    )
    {
        if (root->_left)
        {
            Generate(root->_left, out, left, depth+1);
        }

        out.emplace_back(GenerateRow(depth, prefix, root));

        if (root->_right)
        {
            Generate(root->_right, out, right, depth+1);
        }
    }

    string GenerateRow(int depth, const string &prefix, Node_t *node)
    {
        string res = "";
        for (int i = 1; i < depth; i++)
        {
            res += space;
        }
        res = res + prefix + to_string(node->_val);
        return res;
    }

    void Print(vector<string> &treestr)
    {
        for (auto p = treestr.begin(); p != treestr.end(); p++)
        {
            cout << *p << "\n";
        }
    }

    static const string left;
    static const string right;
    static const string space;
};

template <typename T>
const string Printer<T>::left = "┌──";

template <typename T>
const string Printer<T>::right = "└──";

template <typename T>
const string Printer<T>::space = "   ";

class Test
{
    typedef BTree<int> BTree_t;
    typedef BTree_t::Node Node_t;
    typedef Printer<int> Printer_t;

public:
/**
 *                1
 *              /    \
 *             2      3
 *           /  \    /  \
 *          4    5  6    7 
 */
    static void Test_Size()
    {
        cout << "Test_PreOrderTraversal: \n";

        BTree_t btree;
        btree.Append({1, 2, 3, 4, 5, 6, 7});

        size_t w, h;
        btree.Size(w, h);
        cout << "widht: " << w << ", height: " << h << "\n";

        cout << "\n\n";
    }

    static void Test_Printer()
    {
        cout << "Test_PreOrderTraversal: \n";

        BTree_t btree;
        btree.Append({1, 2, 3, 4, 5, 6, 7, 8, 9});

        Printer_t printer;
        printer(btree);

        cout << "\n\n";
    }
};

int main()
{
    Test::Test_Size();
    Test::Test_Printer();
    return 0;
}