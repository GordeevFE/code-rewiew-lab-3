// https://deepseek.com
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

// Êîäû îïåðàöèé
const int OPERATION_ADD = -1;      // Ñëîæåíèå
const int OPERATION_SUB = -2;      // Âû÷èòàíèå
const int OPERATION_MUL = -3;      // Óìíîæåíèå
const int OPERATION_DIV = -4;      // Äåëåíèå íàöåëî

// Ñòðóêòóðà óçëà äåðåâà
struct TreeNode
{
    int Value;                              // Çíà÷åíèå óçëà (îòðèöàòåëüíîå - îïåðàöèÿ, íåîòðèöàòåëüíîå - îïåðàíä)
    std::shared_ptr<TreeNode> Left;         // Ëåâûé ïîòîìîê
    std::shared_ptr<TreeNode> Right;        // Ïðàâûé ïîòîìîê

    // Êîíñòðóêòîð
    TreeNode(int InValue) : Value(InValue), Left(nullptr), Right(nullptr) {}
};

// Êëàññ äëÿ ðàáîòû ñ äåðåâîì âûðàæåíèé
class ExpressionTree
{
public:
    ExpressionTree() : Root(nullptr) {}

    // Ïîñòðîåíèå äåðåâà èç ïðåôèêñíîãî âûðàæåíèÿ
    bool BuildFromPrefix(const std::vector<std::string>& InTokens);

    // Çàãðóçêà âûðàæåíèÿ èç ôàéëà
    bool LoadFromFile(const std::string& InFilename);

    // Ïðåîáðàçîâàíèå äåðåâà (óäàëåíèå îïåðàöèé ñëîæåíèÿ è âû÷èòàíèÿ)
    void SimplifyAddSub();

    // Âû÷èñëåíèå çíà÷åíèÿ äåðåâà
    int Evaluate();

    // Âûâîä äåðåâà â êðàñèâîé ôîðìå áîêîì
    void PrintTree(bool bShowSimplified = false);

    // Ïîëó÷åíèå êîðíÿ äåðåâà
    std::shared_ptr<TreeNode> GetRoot() const { return Root; }

private:
    std::shared_ptr<TreeNode> Root;

    // Ðåêóðñèâíîå ïîñòðîåíèå äåðåâà èç òîêåíîâ
    std::shared_ptr<TreeNode> BuildTreeRecursive(const std::vector<std::string>& InTokens, int& InOutIndex);

    // Ðåêóðñèâíîå óïðîùåíèå äåðåâà (óäàëåíèå îïåðàöèé ñëîæåíèÿ è âû÷èòàíèÿ)
    std::shared_ptr<TreeNode> SimplifyNode(std::shared_ptr<TreeNode> InNode);

    // Âû÷èñëåíèå çíà÷åíèÿ óçëà
    int EvaluateNode(std::shared_ptr<TreeNode> InNode);

    // Ðåêóðñèâíûé âûâîä äåðåâà áîêîì ñ êðàñèâûì ôîðìàòèðîâàíèåì
    void PrintTreeHorizontal(std::shared_ptr<TreeNode> InNode,
        const std::string& InRightPrefix = "",
        const std::string& InCurrentPrefix = "",
        const std::string& InLeftPrefix = "");

    // Ïîëó÷åíèå ñòðîêîâîãî ïðåäñòàâëåíèÿ çíà÷åíèÿ óçëà
    std::string GetNodeValueString(std::shared_ptr<TreeNode> InNode);

    // Ïðîâåðêà, ÿâëÿåòñÿ ëè óçåë îïåðàöèåé
    bool IsOperation(std::shared_ptr<TreeNode> InNode) const;

    // Ïðîâåðêà, ÿâëÿåòñÿ ëè óçåë îïåðàöèåé ñëîæåíèÿ èëè âû÷èòàíèÿ
    bool IsAddOrSub(std::shared_ptr<TreeNode> InNode) const;

    // Ïðîâåðêà êîððåêòíîñòè òîêåíîâ
    bool ValidateTokens(const std::vector<std::string>& InTokens);
};
