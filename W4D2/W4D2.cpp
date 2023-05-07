#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Degree {
    private:
        string m_subject;
        int m_year;
        bool m_cgl;

    public: 
        Degree(string subject, int year, bool cgl): 
            m_subject(subject), m_year(year), m_cgl(cgl)
        {}

        string toString() {
            string cl;
            if (m_cgl) {
                cl = "yes";
            }
            else {
                cl = "no";
            }
            stringstream output;
            output << "SUBJECT(" << m_subject << ") GRAD-YEAR(" << m_year << ") CUMME-LAUDE(" << cl << ")";
            return output.str();
        }

        bool hasTheSameGradYear(Degree & another)
        {
            return (m_year == another.m_year) ;
        }

        bool isInvalid() {
            return (m_year < 0 || m_subject == "");
        }

        Degree clone() {
            Degree clone(m_subject, m_year, m_cgl);
            return clone;
        }
};

class Task {
    private: 
        int m_day;
        int m_month;
        string m_name;

    public: 
        Task(int day, int month, string name): 
            m_day(day), m_month(month), m_name(name)
        {}

        bool hasTheSameDate(Task & other) {
            return (other.m_day == m_day && other.m_month == m_month);
        }

        bool contains(string search) {
            int j = 0;
            for (int i = 0; i < m_name.length(); i++) {
                if (m_name[i] == search[j]) {
                    j++;
                }
                else {
                    if (m_name[i] == search[0]) {
                        j = 1;
                    }
                    else {
                        j = 0;
                    }
                }
                if (j ==search.length()) {
                    return true;
                }
            }
            return false;
        }

        string toString() {
            stringstream output;
            output << "TASK(" << m_name << ") DATE(" << m_month << "/" << m_day << ")";
            return output.str();
        }
};

bool testDegree() {
    Degree d1("Computer Science", 2022, true);
    Degree d2("", 2022, false);
    Degree d3("Computer Science", -40, true);
    Degree d4 = d1.clone();
    return (!(d1.toString() != "SUBJECT(Computer Science) GRAD-YEAR(2022) CUMME-LAUDE(yes)" ||
            !(d2.isInvalid()) || !(d3.isInvalid()) || !(d1.hasTheSameGradYear(d2)) || 
            d4.toString() != "SUBJECT(Computer Science) GRAD-YEAR(2022) CUMME-LAUDE(yes)"));
}

bool testTask() {
    Task t1(18, 10, "Midterm Exam");
    Task t2(18, 10, "Birthday");

    return (!(t1.toString() != "TASK(Midterm Exam) DATE(10/18)" || !(t1.contains("term")) || 
            !(t1.hasTheSameDate(t2))));
}

int main() {
    cout << "Testing Degree: " << boolalpha << testDegree() << endl;
    cout << "Testing Task: " << boolalpha << testTask() << endl;
}