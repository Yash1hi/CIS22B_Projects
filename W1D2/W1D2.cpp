#include <iostream>
using namespace std;

void countTheFirstNumber(int & count, int & first) {
    count = 1;
    int num;
    cin >> first;
    num = first;
    while (num != 0) {
        cin >> num;
        if (num == first) {
            count++;
        }
    }
    if (first == 0) {
        count -= 1;
    }
}

void repeatPasscode(int passcode, bool & passed, int & attempts) {
    int curr;
    attempts = 0;
    passed = false;
    while (curr != passcode && attempts < 3) {
        cout << "Please enter the password: ";
        cin >> curr;
        attempts += 1;
        if (passcode == curr) {
            passed = true;
        }
    }
}

void runTestCases() {
    int count, firstNum;
    countTheFirstNumber(count, firstNum);
    cout << "Count: " << count << "  First Num: " << firstNum << endl;

    int numOfAttempts;
    bool didPass;
    int password = 123;
    cout << endl << "Hint: the password is " << password << endl;
    repeatPasscode(password, didPass, numOfAttempts);
    cout << "Number of Attempts: " << numOfAttempts << "  Did it pass: " << didPass << endl;
}

int main() {
    runTestCases();
}