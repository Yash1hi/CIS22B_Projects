#include <iostream>
using namespace std;

void checkBoundedList(int *pFirst, int size, int lower, int upper, int & below, int & above, int & equal) {
    below = above = equal = 0;
    int *pCurr  = pFirst;
    for(int count = 0; count < size; count++, pFirst++) {
        if (*pFirst < lower) {
            below++;
        }
        else if (*pFirst > upper) {
            above++;
        }
        else if (*pFirst == upper || *pFirst == lower) {
            equal++;
        }
    }
}

void isSimpleDigitsAndBlanks(char *pCurr, bool & onlyDigits, int & blanks) {
    onlyDigits = true;
    blanks = 0;

    if(*pCurr == '\0') {
        onlyDigits = false;
    }

    for( ; *pCurr != '\0'; pCurr++) {
        if (!(*pCurr == '0' || *pCurr == '1' || *pCurr == '2' ||
           *pCurr == '3' || *pCurr == '4' || *pCurr == '5' ||
           *pCurr == '6' || *pCurr == '7' || *pCurr == '8' ||
           *pCurr == '9' || *pCurr == ' ')) {
            onlyDigits = false;
           }
        if(*pCurr == ' ') {
            blanks += 1;
        }
    }
}

bool testCheckBoundedList() {
    int below, above, equal;
    bool passed = true;

    int numList0[] = {10};
    checkBoundedList(numList0, 1, 10, 30, below, above, equal);
    if(below != 0 || above != 0 || equal != 1) {
        passed = false;
    }
    
    int numList1[] = {10, 20, 30, 40};
    checkBoundedList(numList1, 4, 10, 30, below, above, equal);
    if(below != 0 || above != 1 || equal != 2) {
        passed = false;
    }
   
    int numList2[] = {0, 40, 30, 20, 10, 5};
    checkBoundedList(numList2, 6, 10, 30, below, above, equal);
    if(below != 2 || above != 1 || equal != 2) {
        passed = false;
    }
      
    int numList3[] = {10, 30, 20};  
    checkBoundedList(numList3, 3, 10, 30, below, above, equal);
    if(below != 0 || above != 0 || equal != 2) {
        passed = false;
    }
    
    return passed;
}

bool testIsSimpleDigitsAndBlanks() {
    bool isDigits, passed;
    int blanks;
    passed = true;

    char cString1[] = "1";
    isSimpleDigitsAndBlanks(cString1, isDigits, blanks);
    if(isDigits != true || blanks != 0) {passed = false;}
    
    char cString2[] = "123";
    isSimpleDigitsAndBlanks(cString2, isDigits, blanks);
    if(isDigits != true || blanks != 0) {passed = false; }

    char cString3[] = " 123";
    isSimpleDigitsAndBlanks(cString3, isDigits, blanks);
    if(isDigits != true || blanks != 1) {passed = false;}

    char cString4[] = " 123 ";
    isSimpleDigitsAndBlanks(cString4, isDigits, blanks);
    if(isDigits != true || blanks != 2) {passed = false;}

    char cString5[] = "123 456 789";
    isSimpleDigitsAndBlanks(cString5, isDigits, blanks);
    if(isDigits != true || blanks != 2) {passed = false;}

    char cString6[] = "";
    isSimpleDigitsAndBlanks(cString6, isDigits, blanks);
    if(isDigits != false || blanks != 0) {passed = false;}

    char cString7[] = "A";
    isSimpleDigitsAndBlanks(cString7, isDigits, blanks);
    if(isDigits != false || blanks != 0) {passed = false;}

    char cString8[] = "1A";
    isSimpleDigitsAndBlanks(cString8, isDigits, blanks);
    if(isDigits != false || blanks != 0) {passed = false;}

    char cString9[] = " A";
    isSimpleDigitsAndBlanks(cString9, isDigits, blanks);
    if(isDigits != false || blanks != 1) {passed = false;}

    char cString10[] = " 1 A";
    isSimpleDigitsAndBlanks(cString10, isDigits, blanks);
    if(isDigits != false || blanks != 2) {passed = false;}

    char cString11[] = "123 456 ABC";
    isSimpleDigitsAndBlanks(cString11, isDigits, blanks);
    if(isDigits != false || blanks != 2) {passed = false;}

    return passed;
}

int main() {
    cout << "Testing checkBoundedList: ";
    if (testCheckBoundedList()) {
        cout << "Passed!" << endl;
    }
    else {
        cout << "Failed..." << endl;
    }
    

    cout << "Testing isSimpleDigitsAndBlanks: ";
    if (testIsSimpleDigitsAndBlanks()) {
        cout << "Passed!" << endl;
    }
    else {
        cout << "Failed..." << endl;
    }
}