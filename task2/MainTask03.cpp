#include "HeaderTask03.h"

int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        Tree tree;

        // Çàãðóçêà èç ôàéëà
        tree.LoadFromFile("filename.txt");

        cout << "Èñõîäíîå äåðåâî:\n";
        tree.PrintTree();

        // Óïðîùåíèå
        tree.Simplify();

        cout << "Ïðåîáðàçîâàííîå äåðåâî:\n";
        tree.PrintTree();

        // Âûâîä óêàçàòåëÿ íà êîðåíü
        cout << "Àäðåñ êîðíÿ: " << tree.GetRoot() << endl;
    }
    catch (const exception& ex)
    {
        cout << "Îøèáêà: " << ex.what() << endl;
    }

    return 0;
}
