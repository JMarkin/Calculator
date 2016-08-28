#ifndef CALCULATOR_TESTS_H
#define CALCULATOR_TESTS_H
#include <cxxtest/TestSuite.h>
#include "Calculator.h"
#include "Calculator.cpp"

class Tests: public CxxTest::TestSuite {
public:
    void testMinusMinus(void){
        answer=Calc.Calculate("0-(-1)+2-(-1)");
        TS_ASSERT_EQUALS(answer.first,4) ;
        TS_ASSERT_EQUALS(answer.second,"Current") ;
    }
    void testIncorrectInput(void){
        answer=Calc.Calculate("1.1 + 2.1 + abc");
        TS_ASSERT_EQUALS(answer.second,"Некорректный ввод, строка содержит недопустимое выражение - abc") ;
    }
    void testLight(void){
        answer=Calc.Calculate("- 1 + 5 - 3");
        TS_ASSERT_EQUALS(answer.first,1) ;
        TS_ASSERT_EQUALS(answer.second,"Current") ;
    }
    void testNormal(void){
        answer=Calc.Calculate("-10 + (8 * 2.5) - (3 / 1,5)");
        TS_ASSERT_EQUALS(answer.first,8) ;
        TS_ASSERT_EQUALS(answer.second,"Current") ;
    }
    void testMoreScobs(void){
        answer=Calc.Calculate("(1 + (2 * ((2.5 + 2.5) + (3 - 2))) - (3 / 1.5))");
        TS_ASSERT_EQUALS(answer.first,11);
        TS_ASSERT_EQUALS(answer.second,"Current");
    }
    void testMoreSpace(void){
        answer=Calc.Calculate("1+  "
                                      "                        "
                                      "               "
                                      "                                  -1    "
                                      "                                       "
                                      "                                                +       "
                                      "             "
                                      "              "
                                      "                   5");
        TS_ASSERT_EQUALS(answer.first,5);
        TS_ASSERT_EQUALS(answer.second,"Current") ;
    }
    void testDivNullLight(void){
        TS_ASSERT_EQUALS(Calc.Calculate("1/0").second,"Обнаруженно деление на ноль") ;
    }
    void testDivNullNormal(void){
        TS_ASSERT_EQUALS(Calc.Calculate("1/(1+1-2)").second,"Обнаруженно деление на ноль") ;
    }
    void testDivNullHard(void){
        TS_ASSERT_EQUALS(Calc.Calculate("(1+5*3-2*6-17*2.05/9.23)*(0.11-19)*(2+4-25.99)/(12)/((6+5-2)/(12-2*6))").second,"Обнаруженно деление на ноль") ;
    }

private:
    Calculator Calc; pair<double,string> answer;
};


#endif //CALCULATOR_TESTS_H
