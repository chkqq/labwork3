#include "calculator.h"

Calculator::Calculator() {
    vars_["pi"] = 3.14159265;
    vars_["e"] = 2.71828182;
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

bool Calculator::ExecuteCommand()
{
    string command;
    cin >> command;

    if (command == "var") 
    {
        string identifier;
        cin >> identifier;
        Var(identifier);
    }
    else if (command == "let") 
    {
        string input;
        cin >> input;
        Let(input);
    }
    else if (command == "fn") 
    {
        string input;
        cin >> input;
        Fn(input);
    }
    else if (command == "print") 
    {
        string identifier;
        cin >> identifier;
        Print(identifier);
    }
    else if (command == "printvars") 
    {
        PrintVars();
    }
    else if (command == "printfns")
    {
        PrintFns();
    }
    else if (command == "exit") 
    {
        return false;
    }
    else if (command == "help") 
    {
        PrintMenu();
    }
    else
    {
        cout << "Error: Unknown command. Type 'help' for available commands." << endl;
    }

    return true;
}

void Calculator::Var(const string& identifier) 
{
    if (vars_.find(identifier) == vars_.end() && fns_.find(identifier) == fns_.end())
    {
        vars_[identifier] = NAN;
    }
    else
    {
        cout << "Error: Identifier already exists." << endl;
    }
}

void Calculator::Let(const string& input) 
{
    string identifier, value;
    size_t eq_pos = input.find('=');

    if (eq_pos != string::npos) 
    {
        identifier = input.substr(0, eq_pos);
        value = input.substr(eq_pos + 1);

        try 
        {
            double val = std::stod(value);
            vars_[identifier] = val;
        }
        catch (...) 
        {
            cout << "Error: Invalid value." << endl;
        }
    }
    else 
    {
        cout << "Error: Invalid syntax. Use '=' to assign value." << endl;
    }
}

void Calculator::Fn(const string& input) 
{
    string identifier, identifier1, operation, identifier2;
    size_t eq_pos = input.find('=');

    if (eq_pos != string::npos)
    {
        identifier = input.substr(0, eq_pos);
        string expr = input.substr(eq_pos + 1);

        size_t op_pos = expr.find_first_of("+-*/");

        if (op_pos != string::npos)
        {
            identifier1 = expr.substr(0, op_pos);
            operation = expr[op_pos];
            identifier2 = expr.substr(op_pos + 1);
            fns_[identifier] = make_pair(identifier1, make_pair(operation.empty() ? ' ' : operation[0], identifier2));
        }
        else 
        {
            identifier1 = expr;
            fns_[identifier] = make_pair(identifier1, make_pair(' ', ""));
        }
    }
    else 
    {
        cout << "Error: Invalid syntax. Use '=' to define function." << endl;
    }
}


double Calculator::Eval(const string& identifier)
{
    if (vars_.find(identifier) != vars_.end())
    {
        return vars_[identifier];
    }
    else if (fns_.find(identifier) != fns_.end())
    {
        auto fn_def = fns_[identifier];
        if (fn_def.second.first == ' ') 
        {
            return Eval(fn_def.first);
        }
        else
        {
            double arg1 = Eval(fn_def.first);
            double arg2 = Eval(fn_def.second.second);
            switch (fn_def.second.first)
            {
            case '+':
                return arg1 + arg2;
            case '-':
                return arg1 - arg2;
            case '*':
                return arg1 * arg2;
            case '/':
                if (arg2 != 0) 
                {
                    return arg1 / arg2;
                }
                else 
                {
                    return NAN;
                }
            default:
                return NAN;
            }
        }
    }
    else
    {
        cout << "Error: Identifier not found." << endl;
        return NAN;
    }
}

void Calculator::Print(const string& identifier) 
{
    if (vars_.find(identifier) != vars_.end()) 
    {
        cout << fixed << setprecision(2) << vars_[identifier] << endl;
    }
    else if (fns_.find(identifier) != fns_.end()) 
    {
        cout << fixed << setprecision(2) << Eval(identifier) << endl;
    }
    else 
    {
        cout << "Error: Identifier not found." << endl;
    }
}

void Calculator::PrintVars()
{
    for (const auto& pair : vars_) 
    {
        cout << pair.first << ":" << fixed << setprecision(2) << pair.second << endl;
    }
}

void Calculator::PrintFns()
{
    for (const auto& pair : fns_) 
    {
        cout << pair.first << ":" << std::fixed << setprecision(2) << Eval(pair.first) << endl;
    }
}