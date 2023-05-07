#include <iostream>
using namespace std;

void getScoreInfo(int studentScoreList[][5], int rows, int & pass, int & perfect) {
    pass = perfect = 0;
    for(int row = 0; row < rows; row++) {
        int countPass = 0;
        bool isPerfect = true;
        for(int col = 0; col < 5; col++) {
            if(studentScoreList[row][col] >= 50) {
                countPass++;
            }
            if(studentScoreList[row][col] != 100) {
                isPerfect = false;
            }
        }
        if(countPass >= 3) {
            pass++;
        }
        if(isPerfect) {
            perfect++;
        }
    }
}

void analyzeSurvey(char survey[][4], int rows, int & neutral, int (&yesCount)[4]) {
    neutral = 0;
    yesCount[0] = yesCount[1] = yesCount[2] = yesCount[3] = 0;
    for(int row = 0; row < rows; row++) {
        int numYes = 0;
        for(int col = 0; col < 4; col++) {
            if (survey[row][col] == 'Y') {
                yesCount[col] += 1;
                numYes += 1;
            }
        }
        if (numYes == 2) {
            neutral += 1;
        }
    }
}

bool testGetScoreInfo() {
    bool done = true;
    int perfect, pass;

    int studentScoreList1[][5] = { {100, 100, 100, 100, 100 } };
    getScoreInfo(studentScoreList1, 1, pass, perfect);
    if (pass != 1 || perfect != 1) { done = false; }

    int studentScoreList2[][5] = { {0, 0, 0, 0, 0 } };
    getScoreInfo(studentScoreList2, 1, pass, perfect);
    if (pass != 0 || perfect != 0) { done = false; }

    int studentScoreList3[][5] = { {50, 0, 50, 50, 0 } };
    getScoreInfo(studentScoreList3, 1, pass, perfect);
    if (pass != 1 || perfect != 0) { done = false; }

    int studentScoreList4[][5] = { {50, 0,  0, 50, 0 } };
    getScoreInfo(studentScoreList4, 1, pass, perfect);
    if (pass != 0 || perfect != 0) { done = false; }

    int studentScoreList5[][5] = { {100, 100, 100, 100, 100 },
                                   {50, 0,  0, 50, 0 } };
    getScoreInfo(studentScoreList5, 2, pass, perfect);
    if (pass != 1 || perfect != 1) { done = false; }

    int studentScoreList6[][5] = { {30, 50, 70, 90, 100 },
                                   {100, 100, 100, 100, 100},
                                   {10, 20, 50, 60, 80  },
                                   {100, 100, 40, 40, 40},
                                   {100, 100, 100, 100, 100},
                                   {100, 50, 40, 30, 100} };
    getScoreInfo(studentScoreList6, 6, pass, perfect);
    if (pass != 5 || perfect != 2) { done = false; }

    int studentScoreList7[][5] = { {30, 50, 70, 90, 100 },
                                   {10, 20, 50, 60, 80  },
                                   {100, 100, 40, 40, 40} } ;

    getScoreInfo(studentScoreList7, 3, pass, perfect);
    if (pass != 2 || perfect != 0) { done = false; }    

    return done;
}

bool testAnalyzeSurvey() {
    int neutral;
    bool passed = true;

    int analyzeCount1[4];
    char survey1[][4] = { {'Y', 'Y', 'N', 'N'} };
    analyzeSurvey(survey1, 1, neutral, analyzeCount1);
    if (neutral != 1 || analyzeCount1[0] != 1 || analyzeCount1[1] != 1
        || analyzeCount1[2] != 0 || analyzeCount1[3] != 0) {passed = false; cout << "Failed1" << endl;}

    int analyzeCount2[4];
    char survey2[][4] = { {'Y', 'Y', 'Y', 'Y'} };
    analyzeSurvey(survey2, 1, neutral, analyzeCount2);
    if (neutral != 0 || analyzeCount2[0] != 1 || analyzeCount2[1] != 1
        || analyzeCount2[2] != 1 || analyzeCount2[3] != 1) {passed = false; cout << "Failed2" << endl;}

    int analyzeCount3[4];
    char survey3[][4] = { {'N', 'N', 'N', 'N'} };
    analyzeSurvey(survey3, 1, neutral, analyzeCount3);
    if (neutral != 0 || analyzeCount3[0] != 0 || analyzeCount3[1] != 0
        || analyzeCount3[2] != 0 || analyzeCount3[3] != 0) {passed = false; cout << "Failed3" << endl;}

    int analyzeCount4[4];
    char survey4[][4] = { {'Y', 'Y', 'N', 'N'}, 
                           {'Y', 'N', 'Y', 'N'} };
    analyzeSurvey(survey4, 2, neutral, analyzeCount4);
    if (neutral != 2 || analyzeCount4[0] != 2 || analyzeCount4[1] != 1
        || analyzeCount4[2] != 1 || analyzeCount4[3] != 0) {passed = false; cout << "Failed4" << endl;}

    int analyzeCount5[4];
    char survey5[][4] = { {'Y', 'Y', 'N', 'N'},
                           {'Y', 'N', 'Y', 'N'},
                           {'Y', 'Y', 'Y', 'Y'},
                           {'N', 'N', 'N', 'N'} };
    analyzeSurvey(survey5, 4, neutral, analyzeCount5);
    if (neutral != 2 || analyzeCount5[0] != 3 || analyzeCount5[1] != 2
        || analyzeCount5[2] != 2 || analyzeCount5[3] != 1) {passed = false; cout << "Failed5" << endl;}

    int analyzeCount6[4];
    char survey6[][4] = { {'Y', 'Y', 'N', 'N'},
                           {'Y', 'N', 'Y', 'N'},
                           {'Y', 'Y', 'Y', 'N'},
                           {'Y', 'N', 'N', 'N'},
                           {'Y', 'Y', 'N', 'N'} };
    analyzeSurvey(survey6, 5, neutral, analyzeCount6);
    if (neutral != 3 || analyzeCount6[0] != 5 || analyzeCount6[1] != 3
        || analyzeCount6[2] != 2 || analyzeCount6[3] != 0) {passed = false; cout << "Failed6" << endl;}

    return passed;
}

int main() {
    cout << "Testing getScoreInfo: ";
    if (testGetScoreInfo()) {
        cout << "Passed!" << endl;
    }
    else {
        cout << "Failed..." << endl;
    }

    cout << "Testing getAnalyzeSurvey: ";
    if (testAnalyzeSurvey()) {
        cout << "Passed!" << endl;
    }
    else {
        cout << "Failed..." << endl;
    }
}