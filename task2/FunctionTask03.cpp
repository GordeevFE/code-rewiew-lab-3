#include "HeaderTask03.h"

// Êîíñòðóêòîð óçëà
TreeNode::TreeNode(int value)
{
    data = value;
    left = nullptr;
    right = nullptr;
}

// Êîíñòðóêòîð äåðåâà
Tree::Tree()
{
    root = nullptr;
}

// Äåñòðóêòîð äåðåâà
Tree::~Tree()
{
    DeleteTree(root);
}

// Óäàëåíèå äåðåâà
void Tree::DeleteTree(TreeNode* node)
{
    if (!node) return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

// Çàãðóçêà èç ôàéëà è ïîñòðîåíèå äåðåâà
void Tree::LoadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file)
        throw runtime_error("Îøèáêà îòêðûòèÿ ôàéëà");

    string expr;
    file >> expr;

    int pos = 0;
    root = BuildTree(expr, pos);

    if (pos != expr.size())
        throw runtime_error("Íåêîððåêòíîå âûðàæåíèå");
}

// Ïîñòðîåíèå äåðåâà èç ïðåôèêñíîãî âûðàæåíèÿ
TreeNode* Tree::BuildTree(const string& expr, int& pos)
{
    if (pos >= expr.size())
        throw runtime_error("Îøèáêà ðàçáîðà âûðàæåíèÿ");

    char ch = expr[pos++];

    // Îïåðàíä
    if (isdigit(ch))
    {
        return new TreeNode(ch - '0');
    }

    // Îïåðàöèÿ
    int op;
    switch (ch)
    {
    case '+': op = -1; break;
    case '-': op = -2; break;
    case '*': op = -3; break;
    case '/': op = -4; break;
    default:
        throw runtime_error("Íåèçâåñòíûé ñèìâîë");
    }

    TreeNode* node = new TreeNode(op);
    node->left = BuildTree(expr, pos);
    node->right = BuildTree(expr, pos);

    return node;
}

// Âû÷èñëåíèå ïîääåðåâà
int Tree::Evaluate(TreeNode* node)
{
    if (!node)
        throw runtime_error("Îøèáêà âû÷èñëåíèÿ");

    // Åñëè ÷èñëî
    if (node->data >= 0)
        return node->data;

    int left = Evaluate(node->left);
    int right = Evaluate(node->right);

    switch (node->data)
    {
    case -1: return left + right;
    case -2: return left - right;
    case -3: return left * right;
    case -4:
        if (right == 0)
            throw runtime_error("Äåëåíèå íà íîëü");
        return left / right;
    }

    throw runtime_error("Íåèçâåñòíàÿ îïåðàöèÿ");
}

// Óïðîùåíèå äåðåâà (çàìåíà + è - íà ÷èñëî)
TreeNode* Tree::SimplifyTree(TreeNode* node)
{
    if (!node) return nullptr;

    node->left = SimplifyTree(node->left);
    node->right = SimplifyTree(node->right);

    if (node->data == -1 || node->data == -2)
    {
        int value = Evaluate(node);

        DeleteTree(node->left);
        DeleteTree(node->right);

        node->left = nullptr;
        node->right = nullptr;
        node->data = value;
    }

    return node;
}

// Çàïóñê óïðîùåíèÿ
void Tree::Simplify()
{
    root = SimplifyTree(root);
}

// Ïå÷àòü äåðåâà
void Tree::printTreeH(TreeNode const* node,
    string const& rpref,
    string const& cpref,
    string const& lpref) const
{
    if (!node) return;

    if (node->right)
    {
        printTreeH(node->right,
            rpref + "    ",
            rpref + "--- ",
            rpref + "|   ");
    }

    cout << cpref << node->data << endl;

    if (node->left)
    {
        printTreeH(node->left,
            lpref + "|   ",
            lpref + "--- ",
            lpref + "    ");
    }
}

// Ïóáëè÷íûé âûâîä äåðåâà
void Tree::PrintTree() const
{
    printTreeH(root, "", "", "");
    cout << endl;
}

// Ïîëó÷èòü êîðåíü
TreeNode* Tree::GetRoot() const
{
    return root;
}
