#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Course {
    private:
        string m_desc;
        int m_units;
        int m_day;

    public:
        Course(string desc, int units, int day): m_desc(desc), m_units(units), m_day(day) {}

        string toString() {
            string dayName;
            if (m_day == 1) { dayName = "Sunday"; }
            else if (m_day == 2) { dayName = "Monday"; }
            else if (m_day == 3) { dayName = "Tuesday"; }
            else if (m_day == 4) { dayName = "Wednesday"; }
            else if (m_day == 5) { dayName = "Thursday"; }
            else if (m_day == 6) { dayName = "Friday"; }
            else if (m_day == 7) { dayName = "Saturday"; }

            stringstream output;
            output << "COURSE(" << m_desc << ") UNITS(" << m_units << ") DAY(" << dayName << ")";
            return output.str();
        }
        
        bool hasTheSameDay(Course & other) {
            return (m_day == other.m_day);
        }

        bool isInvalid() {
            bool containsonlyBlanks = true;
            for (int i = 0; i < m_desc.length(); i++) {
                if (m_desc[i] != ' ') {
                    containsonlyBlanks = false;
                }
            }
            return (m_desc == "" || containsonlyBlanks || m_units < 0 || m_day > 7 || m_day < 1);
        }

        string getDesc() { return m_desc; }
        int getDay() { return m_day; }
        int getUnits() { return m_units; }

};

void analyzeInvalid(Course courses[], int size, int & empty, int & negative, int & invalid, int & numUnits) {
    empty = 0;
    negative = 0;
    invalid = 0;
    numUnits = 0;
    for (int i = 0; i < size; i++) {            
        bool containsOnlyBlanks = true;
        for (int i = 0; i < courses[i].getDesc().length(); i++) {
            if (courses[i].getDesc()[i] != ' ') {
                containsOnlyBlanks = false;
            }
        }
        if (containsOnlyBlanks) {
            empty++;
        }
        if (courses[i].getUnits() < 0) {
            negative++;
        }
        if (courses[i].getDay() < 1 || courses[i].getUnits() > 7) {
            invalid++;
        }
        if (courses[i].isInvalid()) {
            numUnits += courses[i].getUnits();
        }
    }
}

bool testCourse() {
    Course c1("Introduction to C++", 3, 4);
    Course c2("Drama", -10, 4);
    Course c3("Not a class", 1, 0);

    return (c1.toString() == "COURSE(Introduction to C++) UNITS(3) DAY(Wednesday)" && 
            c1.hasTheSameDay(c2) && c2.isInvalid() && c3.isInvalid());
}

bool testAnalyzeInvalid() {
    Course courses[] = {
        Course("", 5, 4),
        Course("Math 1C", 3, 8),
        Course("CIS 22B", -1, 3),
        Course("", 3, 0),
        Course("ENG 13A", 2, 1)
    };
    // cout << endl;
    // for (int i = 0; i < 5; i++) {
    //     cout << i << ": " << courses[i].isInvalid() << "  " << courses[i].toString() << endl;
    // }
    int empty, negative, invalid, numUnits;
    analyzeInvalid(courses, 5, empty, negative, invalid, numUnits);
    cout << "Empty: " << empty << endl;
    cout << "Negative: " << negative << endl;
    cout << "Invalid: " << invalid << endl;
    cout << "numUnits: " << numUnits << endl;
    return (empty == 2 && negative == 1 && invalid == 2 && numUnits == 10);
}

int main() {
    cout << "Testing Course: " << boolalpha << testCourse() << endl;
    cout << "Testing AnalyzeInvalid: " << boolalpha << testAnalyzeInvalid() << endl;
}