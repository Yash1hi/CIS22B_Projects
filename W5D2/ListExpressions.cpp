#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

class Expression {
    private:
        int m_operand1;
        int m_operand2;
        char m_operator;
        
    public:
        Expression(int op1, int op2, char op3): m_operand1(op1), m_operand2(op2), m_operator(op3) {}

        string toString() {
            string str1, str2, str3;

            str1 = to_string(m_operand1);
            str2 = to_string(m_operand2);
            int result;
            if(m_operator == '+') {
                result = m_operand1 + m_operand2;
            }
            else if(m_operator == '-') {
                result = m_operand1 - m_operand2;
            }
            else if(m_operator == '*') {
                result = m_operand1 * m_operand2;
            }
            else if(m_operator == '/') {
                result = m_operand1 / m_operand2;
            }
            else if(m_operator == '%') {
                result = m_operand1 % m_operand2;
            }
            str3 = to_string(result);
            
            string space1(10-str1.length(), ' ');
            string space2(10-str2.length(), ' ');
            string space3(10-str3.length(), ' ');
            stringstream finalString;
            finalString << space1 << str1 << "         " << m_operator << space2 << str2 << "         " << "=" << space3 << str3 << endl;

            return finalString.str();
        }

        int getResult() {
            int result;
            if(m_operator == '+') {
                result = m_operand1 + m_operand2;
            }
            else if(m_operator == '-') {
                result = m_operand1 - m_operand2;
            }
            else if(m_operator == '*') {
                result = m_operand1 * m_operand2;
            }
            else if(m_operator == '/') {
                result = m_operand1 / m_operand2;
            }
            else if(m_operator == '%') {
                result = m_operand1 % m_operand2;
            }
            return result;
        }

        char getOperator() {
            return m_operator;
        }
};

void add(vector<Expression> & expressionList) {
    bool valid = true;
    bool hasOp = false;
    string input;
    cout << "Please enter an expression: " << endl;
    getline(cin >> ws, input);

    for(int index = 0; index < input.length(); index++) {
        if (hasOp && (input[index] != '0' && input[index] != '1' && input[index] != '2' && input[index] != '3' && input[index] != '4' &&
            input[index] != '5' && input[index] != '6' && input[index] != '7' && input[index] != '8' && input[index] != '9' && input[index] != ' ')) {
                cout << "Invalid operand. Number is expected." << endl;
                valid = false;
                break;
        }
        if (input[index] == '+' || input[index] == '-' || input[index] == '*' || 
            input[index] == '/' || input[index] == '%') {
                hasOp = true;
        }
    }
    
    int op1, op2;
    char op3;
    stringstream expression(input);
    expression >> op1 >> op3 >> op2;
    Expression e1(op1, op2, op3);

    if (!hasOp) {
            valid = false;
            cout << endl << "Unsupported expression operator." << endl;
    }
    if (valid) {
        expressionList.push_back(e1);
        cout << e1.toString();
    }
}

void listAll(vector<Expression> & expressionList) {
    cout << "All expressions: " << endl;
    for (int i = 0; i < expressionList.size(); i++) {
        cout << expressionList[i].toString();
    }
}

void listByOperator(vector<Expression> & expressionList) {
    char op;
    bool hasOp = false;
    cout << "Please enter the operator: " << endl;
    cin >> op;

    for (int i = 0; i < expressionList.size(); i++) {
        if (expressionList[i].getOperator() == op) {
            cout << expressionList[i].toString();
            hasOp = true;
        }
    }
    if (!hasOp) {
        cout << "No expression is found with the operator: " << op << endl;
    }
}

void listSummary(vector<Expression> & expressionList) {
    cout << "Total number of expressions: " << expressionList.size() << endl;

    int largest = expressionList[0].getResult();
    int smallest = expressionList[0].getResult();
    
    char operators[] = {'+', '-', '*', '/', '%'};
    for (int i = 0; i < 5; i++) {
        int count = 0;
        for (int j = 0; j < expressionList.size(); j++) {
            if (expressionList[j].getOperator() == operators[i]) {
                count += 1;
            }
            if (expressionList[j].getResult() > largest) {
                largest = expressionList[j].getResult();
            }
            if (expressionList[j].getResult() < smallest) {
                smallest = expressionList[j].getResult();
            }
        }
        cout << "Number of '" << operators[i] << "' expressions:   " << count << endl;
    }

    cout << "Largest expression:          " << largest << endl;
    cout << "Smallest expression:         " << smallest << endl;
    
}

void choiceLoop() {
    cout << "Welcome to expression management program." << endl;
    string choice;
    vector<Expression> expressionList;

    do {
        cout << "Please enter a command (add, listall, listbyoperator, listsummary, and exit): ";
        cin >> choice;
        
        if (choice == "add") {
            add(expressionList);
        }
        else if (choice == "listall") {
            if (expressionList.size() == 0) {
                cout << "There is no expression." << endl;
            }
            else {
                listAll(expressionList);
            }
        }
        else if (choice == "listbyoperator") {
            if (expressionList.size() == 0) {
                cout << "There is no expression." << endl;
            }
            else {
                listByOperator(expressionList);
            }
        }
        else if (choice == "listsummary") {
            if (expressionList.size() == 0) {
                cout << "There is no expression." << endl;
            }
            else {
                listSummary(expressionList);   
            }
        }
        else if (choice == "exit") {
            cout << endl << "Thank you. Goodbye.";
        }
        else {
            cout << "Unsupported command. Please try again." << endl;
        }

    }
    while (choice != "exit");
}

int main() {
    choiceLoop();
}