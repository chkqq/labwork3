#include "CalculatorConsoleHandler.h"

using namespace std;

using CommandFunction = std::function<void(Calculator&)>;

void AddVar(Calculator& calc) {
    std::string identifier;
    std::cin >> identifier;
    calc.AddVar(identifier);
}

void Let(Calculator& calc) {
    std::string input;
    std::cin >> input;
    calc.Let(input);
}

void AddFn(Calculator& calc) {
    std::string input;
    std::cin >> input;
    calc.AddFn(input);
}

void Print(const std::string& identifier) {
    const auto& m_vars = calc.GetVars();
    const auto& m_fns = calc.GetFns();

    if (m_vars.find(identifier) != m_vars.end()) {
        std::cout << identifier << ": " << calc.Eval(identifier) << std::endl;
    }
    else if (m_fns.find(identifier) != m_fns.end()) {
        std::cout << identifier << ": " << calc.Eval(identifier) << std::endl;
    }
    else {
        std::cout << "Error: Identifier not found." << std::endl;
    }
}

void PrintVars(Calculator& calc) {
    const auto& m_vars = calc.GetVars();

    for (const auto& pair : m_vars) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void PrintFns(Calculator& calc) {
    const auto& m_fns = calc.GetFns();

    for (const auto& pair : m_fns) {
        std::cout << pair.first << ": " << calc.Eval(pair.first) << std::endl;
    }
}

void PrintMenu()
{
    cout << "Available commands:" << endl
        << "var <identifier>: Declare a variable." << endl
        << "let <identifier1> = <identifier2>: Assign a value to a variable." << endl
        << "fn <identifier> = <identifier1> <operation> <identifier2>: Declare a function." << endl
        << "print <identifier>: Print the value of a variable or a function." << endl
        << "printvars: Print all variables." << endl
        << "printfns: Print all functions." << endl
        << "exit: Exit the program." << endl;
}

void AddVarCommand()
{
    std::string identifier;
    std::cin >> identifier;
    calc.AddVar(identifier);
}

void LetCommand()
{
    std::string input;
    std::cin >> input;
    calc.Let(input);
}

void AddFnCommand()
{
    std::string input;
    std::cin >> input;
    calc.AddFn(input);
}

void PrintCommand()
{
    std::string identifier;
    std::cin >> identifier;
    Print(identifier);
}

void PrintVarsCommand()
{
    PrintVars(calc);
}

void PrintFnsCommand()
{
    PrintFns(calc);
}

void HelpCommand()
{
    PrintMenu();
}

bool ExecuteCommand()
{
    std::string command;
    std::cin >> command;

    static std::map<std::string, void (*)()> commandMap = {
        {"var", AddVarCommand},
        {"let", LetCommand},
        {"fn", AddFnCommand},
        {"print", PrintCommand},
        {"printvars", PrintVarsCommand},
        {"printfns", PrintFnsCommand},
        {"exit", nullptr},
        {"help", HelpCommand}
    };

    auto it = commandMap.find(command);
    if (it != commandMap.end())
    {
        if (it->second)
        {
            it->second();
        }
        else
        {
            return false;
        }
    }
    else
    {
        std::cout << "Error: Unknown command. Type 'help' for available commands." << std::endl;
    }

    return true; 
}