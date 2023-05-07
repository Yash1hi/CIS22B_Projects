#include <iostream>
using namespace std;

void findSmallest(int array[], int size, int & smallest, bool & last, int & count) {
    smallest = array[0];
    count = 0;
    for(int i = 0; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
            count = 1;
        }
        else if (array[i] == smallest) {
            count++;
        } 
    }
    last = (smallest == array[size-1]);
}

void changeAllDigitsToTheGivenChar(char replace, char cstring[], int & count, int & same) {
    count = 0;
    same = 0;
    for (int i=0; cstring[i] != '\0'; i++) {
        if (cstring[i] == '0' || cstring[i] == '1' || cstring[i] == '2' ||
            cstring[i] == '3' || cstring[i] == '4' || cstring[i] == '5' || 
            cstring[i] == '6' || cstring[i] == '7' || cstring[i] == '8' ||
            cstring[i] == '9') {
            cstring[i] = replace;
            count++;
        }
        else if (cstring[i] == replace) {
            same++;
        }
    }
}

bool testFindSmallest() {
    int smallest, count;
    bool last;

    int size = 6;
    int testArray1[6] = {10, 50, 20, 30, 40, 10};
    findSmallest(testArray1, size, smallest, last, count);
    if (smallest != 10 || last != true || count != 2) { cout << "T1"; return false; }

    size = 5;
    int testArray2[5] = {50, 20, 30, 40, 10};
    findSmallest(testArray2, size, smallest, last, count);
    if (smallest != 10 || last != true || count != 1) { cout << "T2"; return false; }

    size = 4;
    int testArray3[4] = {10, 10, 30, 40};
    findSmallest(testArray3, size, smallest, last, count);
    if (smallest != 10 || last != false || count != 2) { cout << "T3"; return false; }

    return true;
}

bool testChangeAllDigitsToTheGivenChar() {
    char replace; 
    int count, same;

    char cstring1[6] = {'H', '1', '0', '2', 'o', '\0'};
    replace = '?';
    changeAllDigitsToTheGivenChar(replace, cstring1, count, same);
    if (count != 3 || same != 0) { return false; }

    char cstring2[6] = {'?', '1', '0', '2', '?', '\0'};
    changeAllDigitsToTheGivenChar(replace, cstring2, count, same);
    if (count != 3 || same != 2) { return false; }

    char cstring3[1] = {'\0'};
    changeAllDigitsToTheGivenChar(replace, cstring3, count, same);
    if (count != 0 || same != 0) { return false; }

    char cstring4[2] = {'?', '\0'};
    changeAllDigitsToTheGivenChar(replace, cstring4, count, same);
    if (count != 0 || same != 1) { return false; }

    char cstring5[2] = {'1', '\0'};
    changeAllDigitsToTheGivenChar(replace, cstring5, count, same);
    if (count != 1 || same != 0) { return false; }

    return true;

}

int main() {
    if (testFindSmallest()) {
        cout << "Testing findSmallest: " << "Passed!" << endl;
    }
    else {
        cout << "Testing findSmallest: " << "Failed..." << endl;
    }
    if (testChangeAllDigitsToTheGivenChar()) {
        cout << "Testing changeAllDigitsToTheGivenChar: " << "Passed!" << endl;
    }
    else {
        cout << "Testing changeAllDigitsToTheGivenChar: " << "Failed..." << endl;
    }
}