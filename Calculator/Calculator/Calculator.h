#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <functional>

enum class FnType {
    Identifier,
    Operation
};

struct Function {
    std::string identifier1;
    std::string action;
    std::string identifier2;
    FnType fnType;
};

class Calculator
{
private:
    std::unordered_map<std::string, double> m_vars;
    std::unordered_map<std::string, Function> m_fns;

public:
    Calculator();
    void AddVar(const std::string& identifier);
    void Let(const std::string& input);
    void AddFn(const std::string& input);
    double Eval(const std::string& identifier);

    const std::unordered_map<std::string, double>& GetVars() const { return m_vars; }
    const std::unordered_map<std::string, Function>& GetFns() const { return m_fns; }
};
#endif
