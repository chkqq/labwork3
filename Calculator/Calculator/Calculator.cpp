#include "calculator.h"

using namespace std;

Calculator::Calculator() {
    m_vars["pi"] = 3.14159265;
    m_vars["e"] = 2.71828182;
}

bool IsValidIdentifier(const string& identifier) 
{
    if (identifier.empty() || isdigit(identifier[0])) 
    {

        cout << "Error: Invalid identifier. Identifiers cannot be empty, start with a digit." << endl;
        return false;
    }

    for (char ch : identifier) 
    {
        if (!isalnum(ch) && ch != '_')
        {

            cout << "Error: Invalid identifier. Identifiers can only contain alphanumeric characters." << endl;
            return false;
        }
    }

    return true;
}

void Calculator::AddVar(const string& identifier) 
{
    if (!IsValidIdentifier(identifier)) 
        return;
    if (m_vars.find(identifier) == m_vars.end() && m_fns.find(identifier) == m_fns.end())
    {
        m_vars[identifier] = NAN;
    }
    else
    {
        cout << "Error: Identifier "<< identifier <<" already exists." << endl;
    }
}

void Calculator::Let(const string& input)   
{
    string identifier, value;
    size_t eq_pos = input.find('=');

    if (eq_pos != string::npos) 
    {
        identifier = input.substr(0, eq_pos);
        if (!IsValidIdentifier(identifier))
            return;
        value = input.substr(eq_pos + 1);

        try 
        {
            double val = stod(value);
            m_vars[identifier] = val;
        }
        catch (...) 
        {
            cout << "Error: Invalid value:" << value << endl;
        }
    }
    else 
    {
        cout << "Error: Invalid syntax. Use '=' to assign value." << endl;
    }
}

void Calculator::AddFn(const std::string& input)
{
    std::string identifier, identifier1, action, identifier2;
    size_t eq_pos = input.find('=');

    if (eq_pos != std::string::npos)
    {
        identifier = input.substr(0, eq_pos);
        if (!IsValidIdentifier(identifier))
            return;
        if (m_fns.find(identifier) != m_fns.end())
        {
            std::cout << "Error: Function with identifier " << identifier << " already exists." << std::endl;
            return;
        }
        std::string expr = input.substr(eq_pos + 1);

        size_t op_pos = expr.find_first_of("+-*/");

        if (op_pos != std::string::npos)
        {
            identifier1 = expr.substr(0, op_pos);
            if (!IsValidIdentifier(identifier1))
                return;
            action = expr[op_pos];
            identifier2 = expr.substr(op_pos + 1);
            if (!IsValidIdentifier(identifier2))
                return;
            m_fns[identifier] = { identifier1, action, identifier2, FnType::Operation };
        }
        else
        {
            identifier1 = expr;
            m_fns[identifier] = { identifier1, "", "", FnType::Identifier };
        }
    }
    else
    {
        std::cout << "Error: Invalid syntax. Use '=' to define function." << std::endl;
    }
}


double Calculator::Eval(const std::string& identifier)
{
    if (m_vars.find(identifier) != m_vars.end())
    {
        return m_vars[identifier];
    }
    else if (m_fns.find(identifier) != m_fns.end())
    {
        auto fn_def = m_fns[identifier];
        if (fn_def.fnType == FnType::Identifier)
        {
            return Eval(fn_def.identifier1);
        }
        else
        {
            double arg1 = Eval(fn_def.identifier1);
            double arg2 = Eval(fn_def.identifier2);
            switch (fn_def.action[0])
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
        std::cout << "Error: Identifier " << identifier << " not found." << std::endl;
        return NAN;
    }
}
