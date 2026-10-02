#include "HeaderTask01.h"

/**
 * @brief Загрузка выражения из файла
 * @param InFilename Имя файла
 * @return true если загрузка успешна, false в противном случае
 */
bool ExpressionTree::LoadFromFile(const std::string& InFilename)
{
    std::ifstream File(InFilename);
    if (!File.is_open())
    {
        std::cerr << "Ошибка: Не удалось открыть файл " << InFilename << std::endl;
        return false;
    }

    std::string Line;
    std::getline(File, Line);
    File.close();

    if (Line.empty())
    {
        std::cerr << "Ошибка: Файл пуст" << std::endl;
        return false;
    }

    // Разбиваем строку на токены (разделитель - пробел)
    std::vector<std::string> Tokens;
    std::stringstream SS(Line);
    std::string Token;

    while (SS >> Token)
    {
        Tokens.push_back(Token);
    }

    if (Tokens.empty())
    {
        std::cerr << "Ошибка: Не найдено токенов в выражении" << std::endl;
        return false;
    }

    return BuildFromPrefix(Tokens);
}

/**
 * @brief Проверка корректности токенов
 * @param InTokens Вектор токенов
 * @return true если токены корректны
 */
bool ExpressionTree::ValidateTokens(const std::vector<std::string>& InTokens)
{
    if (InTokens.empty())
        return false;

    int OperandCount = 0;
    int OperatorCount = 0;

    for (const auto& Token : InTokens)
    {
        // Проверяем, является ли токен числом
        bool bIsNumber = true;
        for (char C : Token)
        {
            if (!isdigit(C))
            {
                bIsNumber = false;
                break;
            }
        }

        if (bIsNumber)
        {
            // Проверяем, что число от 0 до 9
            int Num = std::stoi(Token);
            if (Num < 0 || Num > 9)
            {
                std::cerr << "Ошибка: Число " << Num << " вне диапазона [0,9]" << std::endl;
                return false;
            }
            OperandCount++;
        }
        else if (Token.length() == 1 && (Token[0] == '+' || Token[0] == '-' ||
            Token[0] == '*' || Token[0] == '/'))
        {
            OperatorCount++;
        }
        else
        {
            std::cerr << "Ошибка: Недопустимый токен: " << Token << std::endl;
            return false;
        }
    }

    // В префиксной форме количество операндов должно быть на 1 больше количества операторов
    if (OperandCount != OperatorCount + 1)
    {
        std::cerr << "Ошибка: Неверное количество операндов и операторов. "
            << "Операндов: " << OperandCount << ", операторов: " << OperatorCount << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Рекурсивное построение дерева из токенов
 * @param InTokens Вектор токенов
 * @param InOutIndex Индекс текущего токена
 * @return Узел дерева
 */
std::shared_ptr<TreeNode> ExpressionTree::BuildTreeRecursive(const std::vector<std::string>& InTokens, int& InOutIndex)
{
    if (InOutIndex >= static_cast<int>(InTokens.size()))
        return nullptr;

    std::string CurrentToken = InTokens[InOutIndex];
    InOutIndex++;

    // Проверяем, является ли токен операцией
    if (CurrentToken.length() == 1 && (CurrentToken[0] == '+' || CurrentToken[0] == '-' ||
        CurrentToken[0] == '*' || CurrentToken[0] == '/'))
    {
        int OpCode;
        switch (CurrentToken[0])
        {
        case '+': OpCode = OPERATION_ADD; break;
        case '-': OpCode = OPERATION_SUB; break;
        case '*': OpCode = OPERATION_MUL; break;
        case '/': OpCode = OPERATION_DIV; break;
        default: return nullptr;
        }

        std::shared_ptr<TreeNode> Node = std::make_shared<TreeNode>(OpCode);

        // Рекурсивно строим левое и правое поддеревья
        Node->Left = BuildTreeRecursive(InTokens, InOutIndex);
        Node->Right = BuildTreeRecursive(InTokens, InOutIndex);

        return Node;
    }
    else
    {
        // Это операнд (число от 0 до 9)
        int Value = std::stoi(CurrentToken);
        return std::make_shared<TreeNode>(Value);
    }
}

/**
 * @brief Построение дерева из префиксного выражения
 * @param InTokens Вектор токенов
 * @return true если построение успешно, false в противном случае
 */
bool ExpressionTree::BuildFromPrefix(const std::vector<std::string>& InTokens)
{
    // Проверяем корректность токенов
    if (!ValidateTokens(InTokens))
    {
        return false;
    }

    int Index = 0;
    Root = BuildTreeRecursive(InTokens, Index);

    if (!Root)
    {
        std::cerr << "Ошибка: Не удалось построить дерево" << std::endl;
        return false;
    }

    // Проверяем, что использованы все токены
    if (Index != static_cast<int>(InTokens.size()))
    {
        std::cerr << "Ошибка: Не все токены были использованы при построении дерева" << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Упрощение дерева (удаление операций сложения и вычитания)
 */
void ExpressionTree::SimplifyAddSub()
{
    if (Root)
    {
        Root = SimplifyNode(Root);
    }
}

/**
 * @brief Рекурсивное упрощение узла (удаление только операций + и -)
 * @param InNode Текущий узел
 * @return Упрощенный узел
 */
std::shared_ptr<TreeNode> ExpressionTree::SimplifyNode(std::shared_ptr<TreeNode> InNode)
{
    if (!InNode)
        return nullptr;

    // Если узел - операнд, возвращаем его
    if (!IsOperation(InNode))
        return InNode;

    // Рекурсивно упрощаем левое и правое поддеревья
    InNode->Left = SimplifyNode(InNode->Left);
    InNode->Right = SimplifyNode(InNode->Right);

    // Если узел является операцией сложения или вычитания, заменяем его на результат
    if (IsAddOrSub(InNode))
    {
        int Result = EvaluateNode(InNode);
        return std::make_shared<TreeNode>(Result);
    }

    // Операции умножения и деления остаются в дереве
    return InNode;
}

/**
 * @brief Вычисление значения дерева
 * @return Результат вычисления
 */
int ExpressionTree::Evaluate()
{
    if (!Root)
        return 0;

    return EvaluateNode(Root);
}

/**
 * @brief Вычисление значения узла
 * @param InNode Узел для вычисления
 * @return Результат вычисления
 */
int ExpressionTree::EvaluateNode(std::shared_ptr<TreeNode> InNode)
{
    if (!InNode)
        return 0;

    // Если узел - операнд, возвращаем его значение
    if (!IsOperation(InNode))
        return InNode->Value;

    int LeftVal = EvaluateNode(InNode->Left);
    int RightVal = EvaluateNode(InNode->Right);

    switch (InNode->Value)
    {
    case OPERATION_ADD:
        return LeftVal + RightVal;
    case OPERATION_SUB:
        return LeftVal - RightVal;
    case OPERATION_MUL:
        return LeftVal * RightVal;
    case OPERATION_DIV:
        if (RightVal == 0)
        {
            std::cerr << "Ошибка: Деление на ноль" << std::endl;
            return 0;
        }
        return LeftVal / RightVal;
    default:
        return 0;
    }
}

/**
 * @brief Проверка, является ли узел операцией
 * @param InNode Узел для проверки
 * @return true если узел - операция, false в противном случае
 */
bool ExpressionTree::IsOperation(std::shared_ptr<TreeNode> InNode) const
{
    return InNode && InNode->Value < 0;
}

/**
 * @brief Проверка, является ли узел операцией сложения или вычитания
 * @param InNode Узел для проверки
 * @return true если узел - сложение или вычитание
 */
bool ExpressionTree::IsAddOrSub(std::shared_ptr<TreeNode> InNode) const
{
    return InNode && (InNode->Value == OPERATION_ADD || InNode->Value == OPERATION_SUB);
}

/**
 * @brief Получение строкового представления значения узла
 * @param InNode Узел
 * @return Строковое представление
 */
std::string ExpressionTree::GetNodeValueString(std::shared_ptr<TreeNode> InNode)
{
    if (!InNode)
        return "";

    if (InNode->Value < 0)
    {
        switch (InNode->Value)
        {
        case OPERATION_ADD: return "-1";
        case OPERATION_SUB: return "-2";
        case OPERATION_MUL: return "-3";
        case OPERATION_DIV: return "-4";
        default: return "?";
        }
    }
    else
    {
        return std::to_string(InNode->Value);
    }
}

/**
 * @brief Рекурсивный вывод дерева боком с красивым форматированием
 * @param InNode Текущий узел
 * @param InRightPrefix Префикс для правого поддерева
 * @param InCurrentPrefix Префикс для текущего узла
 * @param InLeftPrefix Префикс для левого поддерева
 */
void ExpressionTree::PrintTreeHorizontal(std::shared_ptr<TreeNode> InNode,
    const std::string& InRightPrefix,
    const std::string& InCurrentPrefix,
    const std::string& InLeftPrefix)
{
    if (!InNode)
        return;

    // Выводим правое поддерево
    if (InNode->Right)
    {
        PrintTreeHorizontal(InNode->Right,
            InRightPrefix + "    ",
            InRightPrefix + "--- ",
            InRightPrefix + "|   ");
    }

    // Выводим текущий узел
    std::cout << InCurrentPrefix << GetNodeValueString(InNode) << std::endl;

    // Выводим левое поддерево
    if (InNode->Left)
    {
        PrintTreeHorizontal(InNode->Left,
            InLeftPrefix + "|   ",
            InLeftPrefix + "--- ",
            InLeftPrefix + "    ");
    }
}

/**
 * @brief Вывод дерева в красивой форме боком
 * @param bShowSimplified Флаг, указывающий, какое дерево выводить
 */
void ExpressionTree::PrintTree(bool bShowSimplified)
{
    if (bShowSimplified)
    {
        std::cout << "\n=== Упрощенное дерево ===" << std::endl;
    }
    else
    {
        std::cout << "\n=== Исходное дерево ===" << std::endl;
    }

    if (!Root)
    {
        std::cout << "Дерево пусто" << std::endl;
        return;
    }

    // Выводим дерево с красивым форматированием
    PrintTreeHorizontal(Root);
    std::cout << std::endl;
}
