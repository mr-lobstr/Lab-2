#include <iostream>
#include <string>
#include "data_struct/stack.h"
using namespace std;
using namespace data_struct;

bool is_operator (char c) {
    return c == '*' or c == '/'
        or c == '+' or c == '-'
        or c == '^';
}

bool is_bracket (char c) {
    return c == '(' or c == ')';
}

int priority (string const& str) {
    return str == "^" ? 3
         : (str == "*" or str == "/") ? 2
         : (str == "+" or str == "-") ? 1
         : 0;
}

auto parse (string const& str) {
    DynamicArray<string> tokens;
    int brackets = 0;
    bool isOperand = true;

    for (auto beg = str.begin(); beg != str.end(); ++beg) {       
        if (is_operator (*beg)) {
            if (isOperand) throw runtime_error (
                "за " + tokens.back() + " должен следовать операнд\n"
            );

            tokens.push_back ({beg, beg + 1}); 
            isOperand = true;
        } else if (is_bracket (*beg)) {
            if (*beg == '(') {
                ++brackets;
            } else if (*beg == ')') {
                --brackets;
            }

            tokens.push_back ({beg, beg + 1});            
        } else if (not isspace (*beg)) {
            if (not isOperand) throw runtime_error (
                "за " + tokens.back() + " должен следовать оператор\n"
            );

            isOperand = false;

            auto it = algs::find_if (beg, str.end(), [] (char c) {
                return isspace (c) or is_bracket (c) or is_operator (c);
            });

            tokens.push_back ({beg, it});
            beg = it - 1;
        }
    }

    if (brackets != 0) throw runtime_error (
        "не хватает " + to_string (abs (brackets))
      + (brackets > 0 ? " )" : " (")
      + " скобок"
    );

    return tokens;
}

string to_infix (DynamicArray<string> const& tokens) {
    string result;
    Stack<string> operators;

    for (auto& token : tokens) {
        if (token == "(") {
            operators.push (token);
        } else if (token == ")") {
            while (operators.top() != "(") {
                result += operators.top() + " ";
                operators.pop();      
            }

            operators.pop();
        } else if (is_operator (token[0])) {
            while (not operators.empty()) {
                if (priority (token) > priority (operators.top()))
                    break;
                
                result += operators.top() + " ";
                operators.pop();
            }

            operators.push (token);
        } else {
            result += token + " ";
        }
    }

    while (not operators.empty()) {                
        result += operators.top();
        operators.pop();
    }

    return result;
}

int main()
{
    string s;
    getline (cin, s);
    
    auto tokens = parse (s);
    auto infix = to_infix (tokens);

    cout << infix << endl;
}