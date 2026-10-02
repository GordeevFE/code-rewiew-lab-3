#include "HeaderTask01.h"
#include <iostream>
#include <string>
#include <limits>

/**
 * Îáðàáàòûâàåò ïîëüçîâàòåëüñêèé ââîä è âûâîäèò ðåçóëüòàò
 */
void ProcessUserInput(FTelegraph& Telegraph, const std::string& Input)
{
    try
    {
        if (Input.empty())
        {
            std::cout << "Îøèáêà: Ââåäåíà ïóñòàÿ ñòðîêà\n";
            return;
        }

        // Ïðîâåðêà íà ïóñòóþ ñòðîêó ñ ïðîáåëàìè
        bool OnlySpaces = true;
        for (char Symbol : Input)
        {
            if (Symbol != ' ')
            {
                OnlySpaces = false;
                break;
            }
        }

        if (OnlySpaces)
        {
            std::cout << "Îøèáêà: Ñòðîêà ñîäåðæèò òîëüêî ïðîáåëû\n";
            return;
        }

        std::string MorseResult = Telegraph.ConvertToMorse(Input);

        std::cout << "\n=== ÐÅÇÓËÜÒÀÒ ===\n";
        std::cout << "Èñõîäíîå ñîîáùåíèå: " << Input << "\n";
        std::cout << "Àçáóêà Ìîðçå: " << MorseResult << "\n";
        std::cout << "==================\n\n";
    }
    catch (const std::invalid_argument& Exception)
    {
        std::cout << "\n!!! ÎØÈÁÊÀ !!!\n";
        std::cout << Exception.what() << "\n";
        std::cout << "Èñïîëüçóéòå òîëüêî ðóññêèå áóêâû è ïðîáåëû.\n";
        std::cout << "Ââåäèòå 'help' äëÿ ñïèñêà äîñòóïíûõ ñèìâîëîâ.\n\n";
    }
    catch (const std::exception& Exception)
    {
        std::cout << "\n!!! ÍÅÈÇÂÅÑÒÍÀß ÎØÈÁÊÀ !!!\n";
        std::cout << Exception.what() << "\n\n";
    }
}

/**
 * Îñíîâíàÿ ôóíêöèÿ ïðîãðàììû
 */
int main()
{
    // Óñòàíàâëèâàåì ðóññêóþ êîäèðîâêó êîíñîëè
    FTelegraph::SetupRussianConsole();

    FTelegraph Telegraph;

    // Âûâîäèì ïðèâåòñòâåííîå ñîîáùåíèå
    Telegraph.PrintWelcomeMessage();
    Telegraph.PrintHelp();

    std::string UserInput;

    // Îñíîâíîé öèêë ïðîãðàììû
    while (true)
    {
        std::cout << "Ââåäèòå ñîîáùåíèå: ";

        // Î÷èùàåì ïîòîê ââîäà ïåðåä getline äëÿ êîððåêòíîé ðàáîòû
        std::getline(std::cin, UserInput);

        // Ïðîâåðêà íà îøèáêó ââîäà
        if (std::cin.eof())
        {
            std::cout << "\nÄî ñâèäàíèÿ! Ñïàñèáî çà èñïîëüçîâàíèå ïðîãðàììû.\n";
            break;
        }

        // Ïðîâåðêà íà êîìàíäû âûõîäà
        if (UserInput == "exit" || UserInput == "quit" ||
            UserInput == "âûõîä" || UserInput == "ÂÛÕÎÄ")
        {
            std::cout << "\nÄî ñâèäàíèÿ! Ñïàñèáî çà èñïîëüçîâàíèå ïðîãðàììû.\n";
            break;
        }

        // Ïðîâåðêà íà êîìàíäó ñïðàâêè
        if (UserInput == "help" || UserInput == "HELP" ||
            UserInput == "ïîìîùü" || UserInput == "ÏÎÌÎÙÜ")
        {
            Telegraph.PrintHelp();
            continue;
        }

        // Îáðàáîòêà îáû÷íîãî ââîäà
        ProcessUserInput(Telegraph, UserInput);
    }

    return 0;
}
