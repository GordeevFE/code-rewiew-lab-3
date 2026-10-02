// https://chatgpt.com
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// Óçåë äåðåâà
struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value);
};

// Êëàññ äåðåâà
class Tree
{
private:
    TreeNode* root;

    // Ðåêóðñèâíîå ïîñòðîåíèå äåðåâà èç ïðåôèêñíîé ñòðîêè
    TreeNode* BuildTree(const string& expr, int& pos);

    // Ðåêóðñèâíîå óïðîùåíèå äåðåâà
    TreeNode* SimplifyTree(TreeNode* node);

    // Âû÷èñëåíèå ïîääåðåâà
    int Evaluate(TreeNode* node);

    // Óäàëåíèå äåðåâà (îñâîáîæäåíèå ïàìÿòè)
    void DeleteTree(TreeNode* node);

    // Ïå÷àòü äåðåâà áîêîì
    void printTreeH(TreeNode const* node,
        string const& rpref,
        string const& cpref,
        string const& lpref) const;

public:
    Tree();
    ~Tree();

    // Çàãðóçêà âûðàæåíèÿ èç ôàéëà è ïîñòðîåíèå äåðåâà
    void LoadFromFile(const string& filename);

    // Óïðîùåíèå äåðåâà (óáðàòü + è -)
    void Simplify();

    // Ïå÷àòü äåðåâà
    void PrintTree() const;

    TreeNode* GetRoot() const;
};
