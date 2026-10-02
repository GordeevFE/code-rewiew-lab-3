#include "HeaderTask01.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <clocale>

FTelegraph::FTelegraph()
{
    // Èíèöèàëèçàöèÿ ñëîâàðÿ àçáóêè Ìîðçå äëÿ ðóññêîãî àëôàâèòà
    // Èñïîëüçóåì çàãëàâíûå áóêâû êàê êëþ÷è
    MorseDictionary = {
        {'À', ".-"}, {'Á', "-..."}, {'Â', ".--"}, {'Ã', "--."},
        {'Ä', "-.."}, {'Å', "."}, {'Æ', "...-"}, {'Ç', "--.."},
        {'È', ".."}, {'É', ".---"}, {'Ê', "-.-"}, {'Ë', ".-.."},
        {'Ì', "--"}, {'Í', "-."}, {'Î', "---"}, {'Ï', ".--."},
        {'Ð', ".-."}, {'Ñ', "..."}, {'Ò', "-"}, {'Ó', "..-"},
        {'Ô', "..-."}, {'Õ', "...."}, {'Ö', "-.-."}, {'×', "---."},
        {'Ø', "----"}, {'Ù', "--.-"}, {'Ú', ".--.-."}, {'Û', "-.--"},
        {'Ü', "-..-"}, {'Ý', "..-.."}, {'Þ', "..--"}, {'ß', ".-."}
    };
}

void FTelegraph::SetupRussianConsole()
{
#ifdef _WIN32
    // Óñòàíàâëèâàåì êîäèðîâêó êîíñîëè Windows íà CP1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    // Óñòàíàâëèâàåì ëîêàëü äëÿ êîððåêòíîãî ââîäà/âûâîäà ðóññêèõ áóêâ
    setlocale(LC_ALL, "Russian");
    std::setlocale(LC_ALL, "Russian");
}

bool FTelegraph::IsRussianLetter(char Symbol) const
{
    // Ïðîâåðÿåì, ÿâëÿåòñÿ ëè ñèìâîë ðóññêîé áóêâîé (êàê çàãëàâíîé, òàê è ñòðî÷íîé)
    unsigned char Char = static_cast<unsigned char>(Symbol);

    // Äèàïàçîíû ðóññêèõ áóêâ â CP1251
    // À-ß: 192-223, à-ÿ: 224-255, ¨: 168, ¸: 184
    return (Char >= 192 && Char <= 255) || Char == 168 || Char == 184;
}

char FTelegraph::ToRussianUpper(char Symbol) const
{
    unsigned char Char = static_cast<unsigned char>(Symbol);

    // Ïðåîáðàçîâàíèå ñòðî÷íûõ ðóññêèõ áóêâ â çàãëàâíûå (CP1251)
    if (Char >= 224 && Char <= 255)
    {
        // à-ÿ -> À-ß
        return static_cast<char>(Char - 32);
    }
    else if (Char == 184) // ¸ -> ¨
    {
        return static_cast<char>(168);
    }

    // Åñëè ñèìâîë óæå çàãëàâíûé èëè íå ðóññêèé, âîçâðàùàåì êàê åñòü
    return Symbol;
}

std::string FTelegraph::ToUpperCase(const std::string& Text) const
{
    std::string Result;
    Result.reserve(Text.length());

    for (char Symbol : Text)
    {
        if (IsRussianLetter(Symbol))
        {
            Result += ToRussianUpper(Symbol);
        }
        else
        {
            // Äëÿ íå ðóññêèõ ñèìâîëîâ èñïîëüçóåì ñòàíäàðòíûé toupper
            Result += static_cast<char>(std::toupper(static_cast<unsigned char>(Symbol)));
        }
    }

    return Result;
}

bool FTelegraph::IsValidRussianLetter(char Symbol) const
{
    // Ïðîâåðÿåì, ÿâëÿåòñÿ ëè ñèìâîë ðóññêîé áóêâîé è åñòü ëè îí â ñëîâàðå
    return IsRussianLetter(Symbol) && MorseDictionary.find(Symbol) != MorseDictionary.end();
}

std::string FTelegraph::GetAvailableSymbols() const
{
    std::string AvailableSymbols;
    for (const auto& Pair : MorseDictionary)
    {
        AvailableSymbols += Pair.first;
        AvailableSymbols += " ";
    }
    return AvailableSymbols;
}

std::string FTelegraph::ConvertCharToMorse(char Symbol) const
{
    auto It = MorseDictionary.find(Symbol);
    if (It != MorseDictionary.end())
    {
        return It->second;
    }
    return "";
}

std::string FTelegraph::ConvertToMorse(const std::string& InputText) const
{
    if (InputText.empty())
    {
        return "";
    }

    std::string UpperText = ToUpperCase(InputText);
    std::string Result;

    for (char Symbol : UpperText)
    {
        if (Symbol == ' ')
        {
            // Ïðîáåë ìåæäó ñëîâàìè (â àçáóêå Ìîðçå ýòî ïàóçà)
            Result += "  ";
        }
        else if (IsValidRussianLetter(Symbol))
        {
            std::string MorseCode = ConvertCharToMorse(Symbol);
            Result += MorseCode;
            Result += " "; // Ïðîáåë ìåæäó áóêâàìè
        }
        else
        {
            // Íåêîððåêòíûé ñèìâîë - âûáðàñûâàåì èñêëþ÷åíèå
            std::string ErrorMsg = "Íåêîððåêòíûé ñèìâîë: '";
            ErrorMsg += Symbol;
            ErrorMsg += "' (êîä: " + std::to_string(static_cast<unsigned char>(Symbol)) + ")";
            throw std::invalid_argument(ErrorMsg);
        }
    }

    // Óäàëÿåì ïîñëåäíèé ïðîáåë, åñëè îí åñòü
    if (!Result.empty() && Result.back() == ' ')
    {
        Result.pop_back();
    }

    return Result;
}

void FTelegraph::PrintWelcomeMessage() const
{
    std::cout << "========================================\n";
    std::cout << "       ÒÅËÅÃÐÀÔ - ÀÇÁÓÊÀ ÌÎÐÇÅ        \n";
    std::cout << "========================================\n";
    std::cout << "Ïðîãðàììà äëÿ ïðåîáðàçîâàíèÿ òåêñòà\n";
    std::cout << "â àçáóêó Ìîðçå (ðóññêèé àëôàâèò)\n";
    std::cout << "========================================\n\n";
}

void FTelegraph::PrintHelp() const
{
    std::cout << "\n=== ÑÏÐÀÂÊÀ ===\n";
    std::cout << "Äîñòóïíûå ñèìâîëû (ðóññêèå áóêâû):\n";
    std::cout << GetAvailableSymbols() << "\n";
    std::cout << "Ïîääåðæèâàþòñÿ çàãëàâíûå è ñòðî÷íûå áóêâû\n";
    std::cout << "Ñèìâîëû â àçáóêå Ìîðçå: '.' (òî÷êà) è '-' (òèðå)\n";
    std::cout << "Ïðîáåëû ìåæäó ñëîâàìè ñîõðàíÿþòñÿ\n";
    std::cout << "Äëÿ âûõîäà ââåäèòå 'exit', 'quit' èëè 'âûõîä'\n";
    std::cout << "Äëÿ ñïðàâêè ââåäèòå 'help' èëè 'ïîìîùü'\n";
    std::cout << "================\n\n";
}
