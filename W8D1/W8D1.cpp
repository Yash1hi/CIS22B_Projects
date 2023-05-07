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
    Variable(string name, string desc): m_name(name), m_desc(desc) {
        string errorMsg = '';
        if ((name[0] < 97 || name[0] > 122) && (name[0] < 65 || name[0] > 92)) {
            errorMsg = "Variable name can only start with uppercase or lowercase letters.";
        }
        for (int i = 0; i < name.length(); i++) {
            if (name[i] == ' ') {
                errorMsg = "Variable name cannot contain a space (' ')";
            }
        }
        if (error != '') {
            throw new VarNameException(errorMsg);
        }
    }

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

class VarNameException : public runtime_error {
    public:
        VarNameException(string errMsg): runtime_error(errMsg)  {}
};

Variable* createVariableObject(string name, string desc, string value) {
    bool isError = false;
    do {
        try {
            if (value == '') {
                new Variable v1(name, desc);
            }
            else {
                new VariableString v1(name, desc, value);
            }
            isError = false;
        }
        catch (VarNameException *pErrObj) {
            cout << pErrObj->what() << endl;
            cout << "Please enter a new value: ";
            isError = true;
        }
    } while (isError);
}

int main() {

}