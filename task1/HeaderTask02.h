// https://alice.yandex.ru
#pragma once

#include <string>
#include <unordered_map>

/**
 * Класс для преобразования текста в азбуку Морзе
 */
class MorseCode
{
public:
    /**
     * Преобразует текст в азбуку Морзе
     * @param Text Входной текст на русском языке
     * @return Строка с точками и тире
     */
    static std::string TextToMorse(const std::string& Text);

    /**
     * Проверяет, содержит ли строка только допустимые символы
     * @param Text Входной текст
     * @return true, если все символы допустимы
     */
    static bool IsValidInput(const std::string& Text);

private:
    /** Словарь для преобразования букв в код Морзе */
    static const std::unordered_map<char, std::string> MorseMap;

    /** Вспомогательная функция для преобразования одного символа */
    static std::string CharToMorse(char C);
};
