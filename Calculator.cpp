#include "Calculator.h"
pair<double,string> Calculator::Calculate(string input) {
    pair<double,string> answer=make_pair(0,IsValid(input));
    if(answer.second!="Current"){
        return answer;
    }
    string error="Current";
    answer.first=Counting(GetExpression(input),error);
    answer.second=error;
    return answer;
}

//Счет обратной польской записи
double Calculator::Counting(string input,string &error) {
    double result=0;
    stack<double> temp;
    for(size_t i=0;i<input.length();i++){
        if(isdigit(input[i])){
            string str ="";
            while(!IsDelimeter(input[i])&&!IsOperator(input[i])
                  &&i<input.length()){
                if(input[i]==',')
                    input[i]='.';
                str+=input[i];
                i++;
            }
            string::size_type  sz;
            temp.push(stod(str,&sz));
            i--;
        }else
            if(IsOperator(input[i])){
                double a=temp.top(); temp.pop();
                double b=0;
                if(!temp.empty()&&input[i]!='#') {
                    b=temp.top();
                    temp.pop();
                }
                switch(input[i]){
                    case '+': result =b+a; break;
                    case '-': result =b-a; break;
                    case '*': result =b*a; break;
                    case '/':
                        if(a!=0) result=b/a;
                        else {error="Обнаруженно деление на ноль"; return 0;} break;
                    default: result=-a; break;
                }
                temp.push(result);
            }
    }
    return temp.top();
}

// Перевод в обратную польскую запись
string Calculator::GetExpression(string input) {
    string output ="";
    stack<char> operStack;
    bool mayUnary=true;
    for(size_t i=0;i<input.length();i++){
        if(IsDelimeter(input[i]))
            continue;
        if(isdigit(input[i])){
            while(!IsDelimeter(input[i])&&!IsOperator(input[i])
                  &&i<input.length()){
                output+=input[i];
                i++;
            }
            output+=" ";
            i--;
            mayUnary=false;
        }
        if(IsOperator(input[i])){
            if(input[i]=='(') {
                operStack.push(input[i]);
                mayUnary=true;
            }
            else
                if(input[i]==')'){
                    char s= operStack.top();
                    operStack.pop();
                    while(s!='('){
                        output+=s;
                        s=operStack.top();
                        operStack.pop();
                    }
                    mayUnary=false;
                } else{
                    char curop=input[i];
                    if(mayUnary&&curop=='-') curop ='#';
                    if(!operStack.empty())
                        if(GetPriority(curop)<=GetPriority(operStack.top())) {
                            output += operStack.top();
                            operStack.pop();
                        }
                    operStack.push(curop);
                    mayUnary=true;
                }
        }
    }
    while(!operStack.empty()) {
        output += operStack.top();
        operStack.pop();
    }
    return output;
}

bool Calculator::IsDelimeter(char c) {
    return c==' ';
}

bool Calculator::IsOperator(char c) {
    vector<char> operators={'+','/','-','*','(',')','#'};
    // # - унарное отрицание
    return find(operators.begin(), operators.end(), c) != operators.end();
}

int8_t Calculator::GetPriority(char s) {
    switch (s)
    {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
        default: return 4;
    }
}

string Calculator::IsValid(string input) {
    string error="Некорректный ввод";
    int id=0,error_id=1,i=0;
    stack<char> scobs;
    for(i=0;i<input.length()&&error_id==1;i++)
        if(isdigit(input[i])) error_id=0;
    i=0;
    while(i<input.length()&&id!=-1&&error_id==0){
        if(IsDelimeter(input[i])) {
            i++;
            continue;
        }
        switch(id){
            case 0:
                if(input[i]=='('){
                    scobs.push('(');
                    id=0;
                    i++;
                }else{
                    if(isdigit(input[i])||input[i]=='-') {
                        id = 1;
                    }
                    else if (IsOperator(input[i])&&input[i]!='.') {
                        id = 2;
                    }else{
                        id = -1;
                        error_id=1;
                    }
                }
                break;
            case 1:
                if(!isdigit(input[i])) {
                    if (input[i] == '.' || input[i] == ',') {
                        id = 1;
                        i++;
                    }
                    else if (IsOperator(input[i])) {
                        id = 2;
                    }
                    else {
                        id=-1;
                        error_id=1;
                    }
                } else
                    i++;
                break;
            case 2:
                if(input[i]==')'){
                    if(!scobs.empty()&&scobs.top()=='(') {
                        scobs.pop();
                        i++;
                        id=0;
                    }
                    else{
                        id=-1;
                        error_id=2;
                    }
                } else{
                    i++;
                    id=0;
                }
                break;
        }
    }
    if(!scobs.empty()&&error_id==0)
        error_id=2;
    string error_d="";
    switch(error_id) {
        case 0:
            return "Current";
        case 1:
            for (int i = 0; i < input.length(); i++)
                if (!isdigit(input[i]) && !IsDelimeter(input[i])
                    && !IsOperator(input[i])&&input[i]!='.'&&input[i]!=',')
                    error_d += input[i];
            if(error_d=="")
                return error;
            error += ", строка содержит недопустимое выражение - "+error_d;
            return error;
        case 2:
            error = "Ошибка соблюдения скобок";
            return error;
    }
}
