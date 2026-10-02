#include "HeaderTask02.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        std::string Filename;
        Filename = "filename.txt";

        // Чтение выражения из файла
        std::ifstream InputFile(Filename);
        if (!InputFile.is_open())
        {
            throw std::runtime_error("Ошибка: не удалось открыть файл " + Filename);
        }

        std::string Expression;
        std::getline(InputFile, Expression);
        InputFile.close();

        if (Expression.empty())
        {
            throw std::runtime_error("Ошибка: файл пуст");
        }

        // Создаём дерево и строим его из выражения
        Tree TreeInstance;
        if (!TreeInstance.BuildFromPrefix(Expression))
        {
            throw std::runtime_error("Ошибка: некорректное префиксное выражение");
        }

        // Выводим исходное дерево
        std::cout << "Исходное дерево:" << std::endl;
        TreeInstance.PrintTree();

        // Преобразуем дерево — заменяем поддеревья со сложением и вычитанием их значениями
        TreeInstance.TransformTree();

        // Выводим преобразованное дерево
        std::cout << "Преобразованное дерево (без операций сложения и вычитания):" << std::endl;
        TreeInstance.PrintTree();

        // Выводим указатель на корень (для демонстрации)
        auto RootPtr = TreeInstance.GetRoot();
        std::cout << "Указатель на корень: " << RootPtr.get() << std::endl;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Ошибка: " << Exception.what() << std::endl;
        return 1; // Код ошибки при обработке известных исключений
    }
    catch (...)
    {
        std::cerr << "Неизвестная ошибка произошла во время выполнения программы." << std::endl;
        return 2; // Код для неизвестных ошибок
    }

    return 0; // Успешное завершение программы
}
