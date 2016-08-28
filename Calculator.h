#ifndef CALCULATOR_RPN_H
#define CALCULATOR_RPN_H
#include <bits/stdc++.h>
using namespace std;
class Calculator {
public:
    pair<double,string> Calculate(string input);
private:
    string GetExpression (string input);
    double Counting(string input,string &error);
    bool IsDelimeter(char c);
    bool IsOperator(char c);
    int8_t GetPriority(char s);
    string IsValid(string input);
};

#endif //CALCULATOR_RPN_H
