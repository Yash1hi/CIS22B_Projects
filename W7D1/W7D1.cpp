#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Variable {
  private:
    string m_name;
    string m_desc;
  public:
    Variable(string name, string desc): m_name(name), m_desc(desc) {}

    virtual string toString() {
        return "VAR(" + m_name + ") DESC(" + m_desc + ")";
    }
    
    virtual bool contains(string search) {
        bool contains = false;
        int searchIndex = 0;

        for (int i = 0; i < m_name.length(); i++) {
            char currCharDesc = m_name[i];
            char currCharSearch = search[searchIndex];
            if (currCharDesc > 92) {
                currCharDesc -= 32;
            }
            if (currCharSearch > 92) {
                currCharSearch -= 32;
            }

            if (currCharSearch == currCharDesc) {
                searchIndex++;
            }
            else {
                searchIndex = 0;
            }
            if (searchIndex == search.length()) {
                contains = true;
            }
        }

        searchIndex = 0;
        for (int i = 0; i < m_desc.length(); i++) {
            char currCharDesc = m_desc[i];
            char currCharSearch = search[searchIndex];
            if (currCharDesc > 92) {
                currCharDesc -= 32;
            }
            if (currCharSearch > 92) {
                currCharSearch -= 32;
            }

            if (currCharSearch == currCharDesc) {
                searchIndex++;
            }
            else {
                searchIndex = 0;
            }
            if (searchIndex == search.length()) {
                contains = true;
            }
        }
        return contains;
    }
};

class VariableString : public Variable {
    private:
        string m_value;
    public:
        VariableString(string name, string desc, string value): Variable(name, desc), m_value(value) {}

        string toString()
        {
            return Variable::toString() + " VALUE(" + m_value + ")" ;
        }

        bool contains(string search) {
            bool inValue = false;
            int searchIndex = 0;

            for (int i = 0; i < m_value.length(); i++) {
                char currCharDesc = m_value[i];
                char currCharSearch = search[searchIndex];
                if (currCharDesc > 92) {
                    currCharDesc -= 32;
                }
                if (currCharSearch > 92) {
                    currCharSearch -= 32;
                }

                if (currCharSearch == currCharDesc) {
                    searchIndex++;
                }
                else {
                    searchIndex = 0;
                }
                if (searchIndex == search.length()) {
                    inValue = true;
                }
            }

            return Variable::contains(search) || inValue;
        }
};

vector<Variable*> contains(vector<Variable*> variableList, string search) {
    vector<Variable*> result;
    for (int i = 0; i < variableList.size(); i++) {
        if (variableList[i]->contains(search)) {
            result.push_back(variableList[i]);
        }
    }
    return result;
}

bool testVariable() {
    bool passed = true;
    Variable v1("isSuccessful", "successful flag indicator");

    if (v1.toString() != "VAR(isSuccessful) DESC(successful flag indicator)") { passed = false; }
    if (!(v1.contains("Flag"))) { passed = false; }
    if (!(v1.contains("suCc"))) { passed = false; }
    if (v1.contains("goo goo ga ga")) { passed = false; }

    return passed;
}

bool testVariableString() {
    bool passed = true;
    VariableString v1("greeting", "a welcome message", "\"Hello, World!\"");

    if (v1.toString() != "VAR(greeting) DESC(a welcome message) VALUE(\"Hello, World!\")") { passed = false; }
    if (!(v1.contains("hel"))) { passed = false; }
    if (!(v1.contains("Wel"))) { passed = false; }
    if (v1.contains("goo goo ga ga")) { passed = false; }

    return passed;
}

bool testContains() {
    bool passed = true;
    vector<Variable*> variableList;
    VariableString * v1 = new VariableString("greeting", "a welcome message", "\"Hello, World!\"");
    VariableString * v2 = new VariableString("hello", "success", "fun");
    Variable * v3 = new Variable("isFun", "is it fun");
    Variable * v4 = new Variable("isSuccessful", "successful flag indicator");
    variableList.push_back(v1);
    variableList.push_back(v2);
    variableList.push_back(v3);
    variableList.push_back(v4);

    vector<Variable*> result1 = contains(variableList, "hello");
    if (result1[0]->toString() != "VAR(greeting) DESC(a welcome message) VALUE(\"Hello, World!\")") { passed = false;  }
    if (result1[1]->toString() != "VAR(hello) DESC(success) VALUE(fun)") { passed = false; }
    if (result1.size() != 2) { passed = false; }

    vector<Variable*> result2 = contains(variableList, "fun");
    if (result2[0]->toString() != "VAR(hello) DESC(success) VALUE(fun)") { passed = false; }
    if (result2[1]->toString() != "VAR(isFun) DESC(is it fun)") { passed = false; }
    if (result2.size() != 2) { passed = false; }

    return passed;
}

int main() {
    cout << "Testing Variable: " << boolalpha << testVariable() << endl;
    cout << "Testing VariableString: " << boolalpha << testVariableString() << endl;
    cout << "Testing Contains: " << boolalpha << testContains() << endl;
}