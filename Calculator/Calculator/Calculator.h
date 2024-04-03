#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

class Calculator
{
private:
    void Var(const string& identifier);
    void Let(const string& input);
    void Fn(const string& input);
    double Eval(const string& identifier);
    void Print(const string& identifier);
    void PrintVars();
    void PrintFns();

    unordered_map<string, double> vars_;
    unordered_map<string,pair<string, pair<char, string>>> fns_;

public:
    Calculator();

    bool ExecuteCommand();
};

#endif
