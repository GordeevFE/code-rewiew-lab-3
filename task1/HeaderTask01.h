// https://deepseek.com
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * Êëàññ äëÿ ïðåîáðàçîâàíèÿ òåêñòà â àçáóêó Ìîðçå
 * Ñîîòâåòñòâóåò ñòàíäàðòó Epic Games C++ Coding Standard
 */
class FTelegraph
{
public:
    // Êîíñòðóêòîð è äåñòðóêòîð
    FTelegraph();
    ~FTelegraph() = default;

    // Çàïðåùàåì êîïèðîâàíèå (RAII ïðèíöèï)
    FTelegraph(const FTelegraph&) = delete;
    FTelegraph& operator=(const FTelegraph&) = delete;

    // Îñíîâíûå ìåòîäû
    std::string ConvertToMorse(const std::string& InputText) const;
    bool IsValidRussianLetter(char Symbol) const;
    std::string GetAvailableSymbols() const;

    // Ìåòîäû äëÿ UI
    void PrintWelcomeMessage() const;
    void PrintHelp() const;

    // Ìåòîä äëÿ óñòàíîâêè ðóññêîé êîäèðîâêè
    static void SetupRussianConsole();

private:
    // Ñëîâàðü àçáóêè Ìîðçå äëÿ ðóññêèõ áóêâ
    std::unordered_map<char, std::string> MorseDictionary;

    // Âñïîìîãàòåëüíûå ìåòîäû
    std::string ConvertCharToMorse(char Symbol) const;
    std::string ToUpperCase(const std::string& Text) const;
    bool IsRussianLetter(char Symbol) const;
    char ToRussianUpper(char Symbol) const;
};
