/**
 * 判断一棵树是否是搜索二叉树
 *  left <= root <= right
 */

#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <stack>

using std::cout;
using std::string;
using std::vector;
using std::queue;
using std::stack;
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
    virtual ~BSTChecker() = default;
};

class BSTChecker1
    : public BSTChecker<int>
{
public:
    bool IsBST(TreeNode<int> *root) override
    {
        temp = INT32_MIN;
        return IsBSTSub(root);
    }

    /**
     * 中序遍历,若为增序,则为搜索二叉树 (递归实现)
     */
    bool IsBSTSub(TreeNode<int> *root)
    {
        bool ret = true;
        if (root == nullptr)
        {
            return ret;
        }

        ret = IsBSTSub(root->left);
        if (ret == false)
        {
            return false;
        }

        if (root->val < temp)
        {
            return false;
        }
        else
        {
            temp = root->val;
        }

        ret = IsBSTSub(root->right);
        if (ret == false)
        {
            return false;
        }

        return true;
    }

private:
    int temp;
};

class BSTChecker2
    : public BSTChecker<int>
{
public:
    bool IsBST(TreeNode<int> *root) override
    {
        return IsBSTSub(root);
    }

    /**
     * 中序遍历,若为增序,则为搜索二叉树 (循环实现)
     */
    bool IsBSTSub(TreeNode<int> *root)
    {
        stack<TreeNode<int>*> s;
        auto node = root;
        int temp = INT32_MIN;

        while (!s.empty() || node)
        {
            if (node)
            {
                s.push(node);
                node = node->left;
            }
            else
            {
                node = s.top();
                s.pop();
                if (node->val < temp)
                {
                    return false;
                }
                else
                {
                    temp = node->val;
                }

                node = node->right;
            }
        }

        return true;
    }
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
    typedef BSTChecker2 BSTChecker2_t;
    typedef TreeNode<Type> TreeNode_t;
    typedef Printer<Type> Printer_t;

    class TestTree
    {
    public:
        TestTree()
            : root(nullptr)
        {
        }

        virtual ~TestTree()
        {
            if (root)
            {
                delete root;
                root = nullptr;
            }
        }

        TreeNode_t *Create()
        {
            if (root == nullptr)
            {
                root = CreateSub();
            }
            return root;
        }

    protected:
        virtual TreeNode_t *CreateSub() = 0;
    
    private:
        TreeNode_t *root;
    };

    class TestTree1
        : public TestTree
    {
    protected:
        TreeNode_t *CreateSub() override
        {
            TreeNode_t* root = new TreeNode_t(1);
            TreeNode_t *left = root->Left(2);
            TreeNode_t * right = root->Right(3);
            left = left->Right(4);
            right = right->Left(5);
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

    protected:
        TreeNode_t *CreateSub() override
        {
            TreeNode_t* root = new TreeNode_t(1);
            CreateSub(root);
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
    protected:
        TreeNode_t *CreateSub() override
        {
            TreeNode_t* root = new TreeNode_t(2);
            root->Left(1)->Left(0);
            root->Right(3);
            return root;
        }
    };

    static void Test_IsBST(BSTChecker_t &bstchecker, TreeNode_t *tree)
    {
        cout << "check IsBST result: "
             << (bstchecker.IsBST(tree) ? "true" : "false") << "\n";
    }

public:
    static void Test_IsBST()
    {
        Printer_t printer;
        std::map<string, BSTChecker_t*> bstCheckers =
        {
            {"bstchecker1", new BSTChecker1_t},
            {"bstchecker2", new BSTChecker2_t},
        };
        std::map<string, TestTree*> trees = {
            {"TestTree1", new TestTree1},
            {"TestTree2", new TestTree2},
            {"TestTree3", new TestTree3},
        };

        for (auto &&bstChecker : bstCheckers)
        {
            for (auto &&tree : trees)
            {
                cout << "Test " << bstChecker.first << "-" << tree.first << ":\n";
                auto p = tree.second->Create();
                Test_IsBST(*(bstChecker.second), p);
                printer(p);
                cout << "\n";
            }
        }

        for (auto &&bstChecker : bstCheckers)
        {
            delete bstChecker.second;
        }

        for (auto &&tree : trees)
        {
            delete tree.second;
        }
    }
};

int main()
{
    Test::Test_IsBST();
    return 0;
}