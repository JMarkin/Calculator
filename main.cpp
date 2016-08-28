#include "Calculator.h"
int main() {
    string InputStr;
    Calculator Calculator;
    setlocale(LC_ALL, "Russian");
    cout<<" Введите выражение: ";
    getline(cin,InputStr);
    pair<double,string> answer=Calculator.Calculate(InputStr);
    if(answer.second=="Current") {
            cout << "Ответ: " << fixed<<setprecision(2)<<answer.first << endl;
    }
    else
        cout<<answer.second<<endl;
    return 0;
}