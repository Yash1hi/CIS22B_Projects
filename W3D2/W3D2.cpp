#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

void prettyPrint(string & input, int result) {
    int num1, num2;
    string op, str1, str2, str3;

    stringstream expression(input);
    expression >> num1 >> op >> num2;
    str1 = to_string(num1);
    str2 = to_string(num2);
    str3 = to_string(result);
    
    string space1(10-str1.length(), ' ');
    string space2(10-str2.length(), ' ');
    string space3(10-str3.length(), ' ');

    cout << space1 << str1 << "         " << op << space2 << str2 << "         " << "=" << space3 << str3 << endl;
}

void evaluateEquation(string & input, int & expressionCount, int & largestValue, string & largestExpression) {
    int num1, num2, result;
    string op;

    stringstream expression(input);
    expression >> num1 >> op >> num2;
    
    if(input.find('+')<input.length()) {
        result = num1 + num2;
        op = '+';
    }
    else if(input.find('-')<input.length()) {
        result = num1 - num2;
        op = '-';
    }
    else if(input.find('*')<input.length()) {
        result = num1 * num2;
        op = '*';
    }
    else if(input.find('/')<input.length()) {
        result = num1 / num2;
        op = '/';
    }
    else if(input.find('%')<input.length()) {
        result = num1 % num2;
        op = '%';
    }

    if(expressionCount == 1 || result > largestValue) {
        largestValue = result;
        largestExpression = input;
    }
    
    string expr = to_string(num1) + " " + op + " " + to_string(num2);
    prettyPrint(expr, result);
}

void getNewExpression(string & allExpressions, int & expressionCount, int & largestValue, string & largestExpression) {
    string input;
    int num1, num2;

    cout << endl << "Please enter an expression: " << endl;
    getline(cin >> ws, input);
    for(int index = 0; index < input.length(); index++) {
        if (input[index] != '0' && input[index] != '1' && input[index] != '2' && input[index] != '3' && input[index] != '4' &&
            input[index] != '5' && input[index] != '6' && input[index] != '7' && input[index] != '8' && input[index] != '9' &&
            input[index] != '+' && input[index] != '-' && input[index] != '*' && input[index] != '/' && input[index] != '%' && input[index] != ' ') {
                cout << endl << "Invalid operand. Number is expected." << endl;
                return;
        }
    }


    allExpressions += input + ";";
    // cout << "Input: " << input << endl;
    expressionCount++;
    evaluateEquation(input, expressionCount, largestValue, largestExpression);
}

void showLargest(string & largestExpression, int & largestValue) {
    if (largestExpression == "") {
        cout << endl << "There is no expression." << endl;
        return;
    }
    cout << endl << "The largest expression:" << endl;
    // cout << largestExpression << " = " << largestValue << endl;
    prettyPrint(largestExpression, largestValue);
}

void showAll(string & allExpressions) {
    if (allExpressions == "") {
        cout << endl << "There is no expression." << endl;
        return;
    }
    cout << endl << "All expressions: " << endl;
    string curr = "";
    for(int index = 0; index < allExpressions.length(); index++) {
        if(allExpressions[index] == ';') {
            int test1, test2 = 0;
            string hi = "hello";
            evaluateEquation(curr, test1, test2, hi);
            curr = "";
        }
        else {
            curr += allExpressions[index];
        }
    }
}

int main() {
    string allExpressions = "";
    string largestExpression;
    int largestValue;
    int expressionCount = 0;

    cout << "Welcome to expression recording program." << endl;
    string option;
    for( ; option != "4"; ) {
        cout << endl << "Expression Menu:";
        cout << endl << "1. Enter a new expression";
        cout << endl << "2. Show the largest expression";
        cout << endl << "3. Show all expressions";
        cout << endl << "4. exit";
        // cout << "Largest Value: " << largestValue << endl;
        // cout << "Largest Expression: " << largestExpression << endl;
        cout << endl << "Enter your option: ";
        getline(cin >> ws, option);
        if(option == "1") {
            getNewExpression(allExpressions, expressionCount, largestValue, largestExpression);
        }
        else if (option == "2") {
            showLargest(largestExpression, largestValue);
        }
        else if (option == "3") {
            showAll(allExpressions);
        }
        else if (option != "4") {
            cout << endl << "Invalid selection. Please try again." << endl;
        }
    } 
    cout << endl << "Thank you. Goodbye.";
}