#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Exam {
    private:
        string m_name;
        int m_score;

    public:
        Exam(string name, int score): m_name(name), m_score(score) {}

        bool isPerfect() {
            return (m_score == 100);
        }

        bool isPassing() {
            return (m_score >= 70);
        }

        string toString() {
            stringstream output;
            string pf;
            if (m_score >= 70) {
                pf = "Pass";
            }
            else if (m_score < 70) {
                pf = "Fail";
            }
            output << "EXAM(" << m_name << ") SCORE(" << m_score << ") RESULT(" << pf << ")";
            return output.str();
        }

        bool isGreater(Exam other) {
            return m_score > other.m_score;
        }

        void increment(int amount) {
            m_score += amount;
        }
};

void getExamListInfo(Exam examList[], int size, int & perfect, int & pass, int & highest) {
    perfect = 0;
    pass = 0;
    highest = 0;

    for (int i = 0; i < size; i++) {
        if (examList[i].isPerfect()) {
            perfect++;
        }
        if (examList[i].isPassing()) {
            pass++;
        }
        if (examList[i].isGreater(examList[highest])) {
            highest = i;
        }
    }
}

void getInfoAfterIncrement(Exam *examList[], int size, int increment, int & pass, vector<Exam> & passedVector) {
    pass = 0;
    for (int i = 0; i < size; i++) {
        examList[i]->increment(increment);
        if (examList[i]->isPassing()) {
            pass++;
            passedVector.push_back(*examList[i]);
        }
    }
}

void getMatchFirstLastCount(int argc, char * argv[], int & same, int & one) {
    same = 0;
    one = 0;
    for (int i = 0; i < argc; i++) {
        char first = argv[i][0];
        char last;
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (argv[i][j+1] == '\0') {
                last = argv[i][j];
                if (j == 0) {
                    one += 1;
                }
            }
        }
        if (first == last) {
            same += 1;
        }
    }
}

bool testExam() {
    Exam e1("CIS22", 100), e2("MATH1C", 65), e3("CHEM16", 75);
    if (e1.toString() != "EXAM(CIS22) SCORE(100) RESULT(Pass)") { cout << endl << "Failed ToString" << endl; return false; }
    if (e2.isPerfect() != false || e1.isPerfect() != true) { cout << endl << "Failed isPerfect" << endl; return false; }
    if (e2.isPassing() != false || e3.isPassing() != true) { cout << endl << "Failed isPassing" << endl; return false; }
    if (e2.isGreater(e3) != false || e1.isGreater(e2) != true) { cout << endl << "Failed isGreater" << endl; return false; }
    e2.increment(20);
    if (e2.isGreater(e3) != true) { cout << endl << "Failed increment" << endl; return false; }
    return true;
}

bool testGetExamListInfo() {
    Exam examList[] = { Exam("Midterm1 Exam", 90), Exam("Midterm2 Exam", 80),  
                       Exam("Final Exam", 50),    Exam("Extra Credit", 100), 
                       Exam("Initial Test", 0),   Exam("Homework1", 69)      } ; 
    int perfect, pass, highest;
    getExamListInfo(examList, 6, perfect, pass, highest);
    return (perfect == 1 && pass == 3 && highest == 3);
}

bool testGetInfoAfterIncrement() {
    int pass;
    vector<Exam> examsPassed;
    Exam * pExamList[] = { new Exam("Midterm1 Exam", 90), 
                          new Exam("Midterm2 Exam", 80),  
                          new Exam("Final Exam", 50), 
                          new Exam("Extra Credit", 100), 
                          new Exam("Initial Test", 0), 
                          new Exam("Homework1", 69)      } ;
    getInfoAfterIncrement(pExamList, 6, 10, pass, examsPassed);
    return (pass == 4 && examsPassed[0].toString() == "EXAM(Midterm1 Exam) SCORE(100) RESULT(Pass)"
            && examsPassed[1].toString() == "EXAM(Midterm2 Exam) SCORE(90) RESULT(Pass)"
            && examsPassed[2].toString() == "EXAM(Extra Credit) SCORE(110) RESULT(Pass)"
            && examsPassed[3].toString() == "EXAM(Homework1) SCORE(79) RESULT(Pass)");
}

int main() {
    cout << "Testing Exam: " << boolalpha << testExam() << endl;
    cout << "Testing getExamListInfo: " << boolalpha << testGetExamListInfo() << endl;
    cout << "Testing getInfoAfterIncrement: " << boolalpha << testGetInfoAfterIncrement() << endl;
}