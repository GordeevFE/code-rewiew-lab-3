#include <iostream>
#include <string>
#include "HeaderTask02.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * Настраивает кодировку консоли для русского языка
 */
void SetupConsole()
{
#ifdef _WIN32
    SetConsoleCP(1251);      // Установка кодировки ввода
    SetConsoleOutputCP(1251); // Установка кодировки вывода
#endif
}

/**
 * Отображает меню программы
 */
void DisplayMenu()
{
    std::cout << "=== ТЕЛЕГРАФ — АЗБУКА МОРЗЕ ===\n";
    std::cout << "Программа преобразует текст в последовательность точек и тире.\n";
    std::cout << "Допустимые символы: буквы русского алфавита (заглавные/строчные) и пробелы.\n";
    std::cout << "Для выхода введите 'exit'.\n\n";
}

/**
 * Обрабатывает ввод пользователя и выводит результат
 */
void ProcessUserInput()
{
    std::string UserInput;

    while (true)
    {
        std::cout << "Введите сообщение: ";
        std::getline(std::cin, UserInput);

        // Проверка на выход
        if (UserInput == "exit")
        {
            std::cout << "До свидания!\n";
            break;
        }

        // Проверка на пустой ввод
        if (UserInput.empty())
        {
            std::cout << "Ошибка: сообщение не может быть пустым.\n";
            continue;
        }

        // Валидация ввода
        if (!MorseCode::IsValidInput(UserInput))
        {
            std::cout << "Ошибка: обнаружены недопустимые символы.\n";
            std::cout << "Пожалуйста, используйте только русские буквы и пробелы.\n";
            continue;
        }

        // Преобразование в азбуку Морзе
        std::string MorseResult = MorseCode::TextToMorse(UserInput);
        std::cout << "Результат в азбуке Морзе:\n";
        std::cout << MorseResult << "\n\n";
    }
}

int main()
{
    SetupConsole();
    DisplayMenu();
    ProcessUserInput();
    return 0;
}
