#include <iostream>
#include <locale>
#include <windows.h>
#include "HeaderTask03.h"

int main()
{
    // Âêëþ÷àåì UTF-8 â êîíñîëè Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::locale::global(std::locale(""));

    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    Telegraph TelegraphApp;

    std::wstring Input;

    std::wcout << L"=== Òåëåãðàô (Àçáóêà Ìîðçå) ===\n";
    std::wcout << L"Ââåäèòå ñîîáùåíèå íà ðóññêîì ÿçûêå:\n";

    std::getline(std::wcin, Input);

    if (Input.empty())
    {
        std::wcout << L"Îøèáêà: ïóñòàÿ ñòðîêà!\n";
        return 1;
    }

    std::string Result = TelegraphApp.EncodeMessage(Input);

    std::cout << "\nÐåçóëüòàò:\n";
    std::cout << Result << std::endl;

    main();
    return 0;
}
