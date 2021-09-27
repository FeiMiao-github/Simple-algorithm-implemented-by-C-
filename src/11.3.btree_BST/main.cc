/**
 * 判断一棵树是否是搜索二叉树
 *  left <= root <= right
 */

#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::string;
using std::vector;
using std::queue;
using std::to_string;

template <typename T>
struct TreeNode
{
    TreeNode *left;
    TreeNode *right;
    T val;

    TreeNode(const T &val)
        : left(nullptr),
          right(nullptr),
          val(val)
    {}

    ~TreeNode()
    {
        if (left)
        {
            delete left;
            left = nullptr;
        }

        if (right)
        {
            delete right;
            right = nullptr;
        }
    }

    TreeNode* Left(const T &val)
    {
        if (left)
        {
            delete left;
        }

        left = new TreeNode(val);
        return left;
    }

    TreeNode* Right(const T &val)
    {
        if (right)
        {
            delete right;
        }

        right = new TreeNode(val);
        return right;
    }
};

template <typename T>
class BSTChecker
{
public:
    virtual bool IsBST(TreeNode<T> *root) = 0;
};

class BSTChecker1
    : public BSTChecker<int>
{
public:
    bool IsBST(TreeNode<int> *root) override
    {
        bool ret = true;
        temp = INT32_MIN;
        if (root != nullptr)
        {
            ret = IsBSTSub(root);
        }
        return ret;
    }

    /**
     * 中序遍历,若为增序,则为搜索二叉树 
     */
    bool IsBSTSub(TreeNode<int> *root)
    {
        bool ret = true;

        if (root->left)
        {
            ret = IsBSTSub(root->left);
            if (ret == false)
            {
                return false;
            }
        }

        if (root->val < temp)
        {
            return false;
        }
        else
        {
            temp = root->val;
        }

        if (root->right)
        {
            ret = IsBSTSub(root->right);
            if (ret == false)
            {
                return false;
            }
        }

        return true;
    }

private:
    int temp;
};

template <typename T>
class Printer
{
    typedef TreeNode<T> Node_t;
public:
    void operator()(Node_t *root)
    {
        vector<string> treestr;
        Generate(root, treestr);
        Print(treestr);
    }

private:

    void Generate(
        Node_t *root, vector<string> &out
    )
    {
        if (root)
        {
            Generate(root, out, "", 0);
        }
    }

    void Generate(
        Node_t *root,
        vector<string> &out,
        const string &prefix,
        int depth
    )
    {
        if (root->left)
        {
            Generate(root->left, out, left, depth+1);
        }

        out.emplace_back(GenerateRow(depth, prefix, root));

        if (root->right)
        {
            Generate(root->right, out, right, depth+1);
        }
    }

    string GenerateRow(int depth, const string &prefix, Node_t *node)
    {
        string res = "";
        for (int i = 1; i < depth; i++)
        {
            res += space;
        }
        res = res + prefix;
        res += to_string(node->val);
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
    typedef int Type;
    typedef BSTChecker<Type> BSTChecker_t;
    typedef BSTChecker1 BSTChecker1_t;
    typedef TreeNode<Type> TreeNode_t;
    typedef Printer<Type> Printer_t;

    static void Test_IsBST(BSTChecker_t &bstchecker, TreeNode_t *tree)
    {
        cout << "check IsBST result: "
             << (bstchecker.IsBST(tree) ? "true" : "false") << "\n";
    }

    class TestTree
    {
    public:
        TestTree()
            : root(nullptr)
        {
        }

        ~TestTree()
        {
            if (root)
            {
                delete root;
                root = nullptr;
            }
        }

        virtual TreeNode_t *Create() = 0;
    protected:
        TreeNode_t *root;
    };

    class TestTree1
        : public TestTree
    {
    public:
        TreeNode_t *Create() override
        {
            if (root == nullptr)
            {
                root = new TreeNode_t(1);
                TreeNode_t *left = root->Left(2);
                TreeNode_t * right = root->Right(3);
                left = left->Right(4);
                right = right->Left(5);
            }
            return root;
        }
    };

    class TestTree2
        : public TestTree
    {
    public:
        TestTree2(int k = 30)
            : total(k)
        {
        }

        TreeNode_t *Create() override
        {
            if (root == nullptr)
            {
                root = new TreeNode_t(1);
                CreateSub(root);
            }
            return root;
        }

    private:
        void CreateSub(TreeNode_t *node)
        {
            int no = 1;
            queue<TreeNode_t*> q;
            q.push(node);

            while (!q.empty())
            {
                TreeNode_t* tmp = q.front();
                q.pop();

                if (no < total)
                {
                    no += 1;
                    q.push(tmp->Left(no));
                }

                if (no < total)
                {
                    no += 1;
                    q.push(tmp->Right(no));
                }
            }
        }

    private:
        int total;
    };

    class TestTree3
        : public TestTree
    {
    public:
        TreeNode_t *Create() override
        {
            root = new TreeNode_t(2);
            root->Left(1);
            root->Right(3);
            return root;
        }
    };

public:
    static void Test_IsBST()
    {
        BSTChecker1_t bstChecker1;
        TestTree1 tree1;
        TestTree2 tree2;
        TestTree3 tree3;
        TreeNode_t *tree = nullptr;
        Printer_t printer;

        tree = tree1.Create();
        cout << "Test BSTChecker1_t:\n";
        Test_IsBST(bstChecker1, tree);
        printer(tree);

        cout << "\n\nTest BSTChecker1_t: (tree2)\n";
        tree = tree2.Create();
        Test_IsBST(bstChecker1, tree);
        printer(tree);

        cout << "\n\nTest BSTChecker1_t: (tree2)\n";
        tree = tree3.Create();
        Test_IsBST(bstChecker1, tree);
        printer(tree);

        // cout << "\n\nTest BSTChecker2_t:\n";
    }
};

int main()
{
    Test::Test_IsBST();
    return 0;
}