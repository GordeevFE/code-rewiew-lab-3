// https://alice.yandex.ru/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <memory>

/**
 * Узел дерева: хранит данные и указатели на левое и правое поддеревья.
 */
struct TreeNode
{
    int Data;
    std::shared_ptr<TreeNode> Left;
    std::shared_ptr<TreeNode> Right;

    /**
     * Конструктор узла с инициализацией данных.
     * @param Value Значение, которое будет храниться в узле.
     */
    explicit TreeNode(int Value)
        : Data(Value)
        , Left(nullptr)
        , Right(nullptr)
    {
    }
};

/**
 * Класс дерева для работы с арифметическими выражениями в префиксной форме.
 */
class Tree
{
public:

    /**
     * Конструктор по умолчанию. Инициализирует корень дерева как nullptr.
     */
    Tree()
        : Root(nullptr)
    {
    }

    /**
     * Строит дерево из префиксного выражения.
     * @param Expression Строка с префиксным выражением.
     * @return true, если построение успешно, false в противном случае.
     */
    bool BuildFromPrefix(const std::string& Expression);

    /**
     * Преобразует дерево: заменяет поддеревья со сложением и вычитанием их вычисленными значениями.
     */
    void TransformTree();

    /**
     * Выводит дерево в красивой форме боком.
     */
    void PrintTree() const;

    /**
     * Возвращает указатель на корень дерева.
     * @return Указатель на корень дерева.
     */
    std::shared_ptr<TreeNode> GetRoot() const { return Root; }

private:

    std::shared_ptr<TreeNode> Root;

    /**
     * Вспомогательная функция для рекурсивного построения дерева из префиксной записи.
     * @param Expr Строка с выражением.
     * @param Pos Текущая позиция в строке.
     * @return Указатель на построенный узел дерева.
     */
    std::shared_ptr<TreeNode> ParsePrefix(const std::string& Expr, size_t& Pos);

    /**
     * Рекурсивно вычисляет и заменяет поддеревья с операциями сложения и вычитания.
     * @param Node Текущий узел дерева.
     * @return Вычисленное значение поддерева.
     */
    int EvaluateAndReplace(std::shared_ptr<TreeNode>& Node);

    /**
     * Вспомогательная функция для вывода дерева в боковой форме.
     * @param Node Текущий узел для вывода.
     * @param RPref Префикс для правого поддерева.
     * @param CPref Префикс для текущего узла.
     * @param LPref Префикс для левого поддерева.
     */
    void PrintTreeH(std::shared_ptr<TreeNode> const& Node,
        const std::string& RPref,
        const std::string& CPref,
        const std::string& LPref) const;
};
