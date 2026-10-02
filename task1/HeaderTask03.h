// https://chatgpt.com
#pragma once

#include <string>
#include <unordered_map>

class Telegraph
{
public:
    Telegraph();

    std::string EncodeMessage(const std::wstring& Message);

private:
    std::unordered_map<wchar_t, std::string> MorseMap;

    void InitializeMorse();
    wchar_t ToUpperRus(wchar_t Symbol);
};
