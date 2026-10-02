#include "HeaderTask01.h"
#include <windows.h>

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 */
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Имя файла прописано в коде
    std::string Filename = "filename.txt";

    std::cout << "========================================" << std::endl;
    std::cout << "   Арифметическое выражение в префиксной форме" << std::endl;
    std::cout << "========================================" << std::endl;

    ExpressionTree Tree;

    // Загружаем выражение из файла
    if (!Tree.LoadFromFile(Filename))
    {
        std::cerr << "\nОшибка: Не удалось загрузить выражение из файла " << Filename << "!" << std::endl;
        std::cerr << "Убедитесь, что файл существует и содержит корректное выражение." << std::endl;
        std::cerr << "Формат: операторы и операнды разделены пробелами" << std::endl;
        return 1;
    }


    // Выводим исходное дерево
    Tree.PrintTree(false);

    // Вычисляем значение исходного выражения
    int OriginalValue = Tree.Evaluate();
    std::cout << "Значение исходного выражения: " << OriginalValue << std::endl;

    // Упрощаем дерево
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Выполняется упрощение дерева (удаление операций + и -)..." << std::endl;
    Tree.SimplifyAddSub();

    // Выводим упрощенное дерево
    Tree.PrintTree(true);

    // Вычисляем значение упрощенного дерева
    int SimplifiedValue = Tree.Evaluate();
    std::cout << "Значение упрощенного выражения: " << SimplifiedValue << std::endl;

    // Выводим корень упрощенного дерева
    std::shared_ptr<TreeNode> Root = Tree.GetRoot();
    if (Root)
    {
        std::cout << "\n----------------------------------------" << std::endl;
        std::cout << "=== Корень упрощенного дерева ===" << std::endl;
        std::cout << "Значение узла: " << Root->Value;
        if (Root->Value < 0)
        {
            std::string OpName;
            switch (Root->Value)
            {
            case OPERATION_ADD: OpName = "сложение (+)"; break;
            case OPERATION_SUB: OpName = "вычитание (-)"; break;
            case OPERATION_MUL: OpName = "умножение (*)"; break;
            case OPERATION_DIV: OpName = "деление (/)"; break;
            default: OpName = "неизвестно";
            }
            std::cout << " (" << OpName << ")" << std::endl;
        }
        else
        {
            std::cout << " (число)" << std::endl;
        }
        std::cout << "Адрес узла: " << Root.get() << std::endl;
    }
    else
    {
        std::cout << "\nДерево пусто!" << std::endl;
    }

    return 0;
}
