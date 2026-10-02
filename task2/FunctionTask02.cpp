#include "HeaderTask02.h"

bool Tree::BuildFromPrefix(const std::string& Expression)
{
    size_t Pos = 0;
    Root = ParsePrefix(Expression, Pos);
    return Root != nullptr;
}

std::shared_ptr<TreeNode> Tree::ParsePrefix(const std::string& Expr, size_t& Pos)
{
    if (Pos >= Expr.size())
    {
        return nullptr;
    }

    char Current = Expr[Pos++];

    // Ïðîïóñêàåì ïðîáåëû
    while (Pos < Expr.size() && Expr[Pos] == ' ')
    {
        Pos++;
    }

    if (isdigit(Current))
    {
        // Îïåðàíä (öèôðà 0–9)
        return std::make_shared<TreeNode>(Current - '0');
    }
    else
    {
        // Îïåðàöèÿ
        int OpCode;
        switch (Current)
        {
        case '+':
            OpCode = -1;
            break;
        case '-':
            OpCode = -2;
            break;
        case '*':
            OpCode = -3;
            break;
        case '/':
            OpCode = -4;
            break;
        default:
            return nullptr; // Íåèçâåñòíàÿ îïåðàöèÿ
        }

        auto Node = std::make_shared<TreeNode>(OpCode);
        Node->Left = ParsePrefix(Expr, Pos);
        Node->Right = ParsePrefix(Expr, Pos);
        return Node;
    }
}

void Tree::TransformTree()
{
    if (Root)
    {
        EvaluateAndReplace(Root);
    }
}

int Tree::EvaluateAndReplace(std::shared_ptr<TreeNode>& Node)
{
    if (!Node)
    {
        return 0;
    }

    // Åñëè ýòî ëèñò (îïåðàíä), âîçâðàùàåì åãî çíà÷åíèå
    if (!Node->Left && !Node->Right)
    {
        return Node->Data;
    }

    // Ðåêóðñèâíî âû÷èñëÿåì çíà÷åíèÿ ïîääåðåâüåâ
    int LeftVal = EvaluateAndReplace(Node->Left);
    int RightVal = EvaluateAndReplace(Node->Right);

    // Âûïîëíÿåì îïåðàöèþ â çàâèñèìîñòè îò êîäà
    switch (Node->Data)
    {
    case -1: // Ñëîæåíèå (+)
    case -2: // Âû÷èòàíèå (-)
    {
        int Result;
        if (Node->Data == -1)
        {
            Result = LeftVal + RightVal;
        }
        else
        {
            Result = LeftVal - RightVal;
        }
        // Çàìåíÿåì óçåë ñ îïåðàöèåé íà óçåë ñ ðåçóëüòàòîì
        Node = std::make_shared<TreeNode>(Result);
        return Result;
    }
    case -3: // Óìíîæåíèå (*)
    case -4: // Äåëåíèå (/)
    {
        if (Node->Data == -4 && RightVal == 0)
        {
            throw std::runtime_error("Îøèáêà: äåëåíèå íà íîëü");
        }
        return (Node->Data == -3) ? LeftVal * RightVal : LeftVal / RightVal;
    }
    default:
        throw std::runtime_error("Íåèçâåñòíàÿ îïåðàöèÿ â äåðåâå");
    }
}

void Tree::PrintTree() const
{
    PrintTreeH(Root, "", "", "");
    std::cout << std::endl;
}

void Tree::PrintTreeH(std::shared_ptr<TreeNode> const& Node,
    const std::string& RPref,
    const std::string& CPref,
    const std::string& LPref) const
{
    if (!Node)
    {
        return;
    }

    if (Node->Right)
    {
        PrintTreeH(Node->Right,
            RPref + "    ",
            RPref + "--- ",
            RPref + "|   ");
    }

    std::cout << CPref << Node->Data << std::endl;

    if (Node->Left)
    {
        PrintTreeH(Node->Left,
            LPref + "|   ",
            LPref + "--- ",
            LPref + "    ");
    }
}
