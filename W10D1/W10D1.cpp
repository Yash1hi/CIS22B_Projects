#include <iostream> 
#include <string> 
#include <sstream> 
#include <exception> 
#include <iomanip> 
#include <vector> 
using namespace std; 

class User 
{ 
   private: 
        int    m_id ; 
        string m_name ; 
   public: 
        User(int id, string name): m_id(id), m_name(name)  
        { 
        } 
        virtual string toString() 
        { 
           stringstream ss; 
           ss << "ID(" << m_id << ") NAME("<< m_name << ")" ; 
           return ss.str() ; 
        } 
        bool isIDLarger(User & another) 
        { 
           return m_id > another.m_id ; 
        } 
}; 

class BadValueException : public runtime_error {
    public:
        BadValueException(string errMsg): runtime_error(errMsg) {}
};

class Student : public User {
    private:
        double m_gpa; 
    public:
        Student(int id, string name, double gpa): User(id, name), m_gpa(gpa) {
            stringstream error;
            if (id < 0.0 && (gpa > 4.0 || gpa < 0.0)) {
                error << "negative id: " << fixed << setprecision(2) << id << " and out of bound gpa: " << fixed << setprecision(2) << gpa;
                throw new BadValueException(error.str());
            }
            else if (gpa > 4.0 || gpa < 0.0) {
                error << "out of bound gpa: " << fixed << setprecision(2) << gpa;
                throw new BadValueException(error.str());
            }
            else if (id < 0.0) {
                error << "negative id: " << fixed << setprecision(2) << id;
                throw new BadValueException(error.str());
            }    
        }

        string toString() {
            stringstream output;
            output << User::toString() << fixed << setprecision(2) << " GPA(" << m_gpa << ")";
            return output.str(); 
        }

        virtual bool isGPAGreater(Student & another) {
            return m_gpa > another.m_gpa;
        }
};

class GradStudent : public Student {
    private:
        int m_year;
    public:
        GradStudent(int id, string name, double gpa, int year = 2021): Student(id, name, gpa), m_year(year) {}

        string toString() {
            stringstream output;
            output << Student::toString() << " GRADUATION-YEAR(" << m_year << ")";
            return output.str(); 
        }
};

void getLowest(vector<Student*> studentList, Student* & lowestID, Student* & lowestGPA) {
    lowestID = studentList[0];
    lowestGPA = studentList[0];
    for (int i = 1; i < studentList.size(); i++)
    {
        if ((lowestID->isIDLarger(*studentList[i])))
        {
            lowestID = studentList[i];
        }
        if ((lowestGPA->isGPAGreater(*studentList[i])))
        {
            lowestGPA = studentList[i];
        }
    }
}

Student* createOneStudent() {
    int id; 
    string name; 
    double gpa;
    for(int i = 0; i < 3; i++) {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter GPA: ";
        cin >> gpa;
        cout << "Enter name: ";
        cin >> name;
        try {
            Student *s1 = new Student(id, name, gpa);
            cout << s1->toString() << endl;
            return s1;
        }
        catch(BadValueException *pErrObj) {
            cout << "Exception: " << pErrObj->what() << endl;
        }
    }
    cout << "Unable to create student" << endl;
}

bool testStudent() {
    bool passed = true;
    Student s1(10, "John", 3.2);
    if (s1.toString() != "ID(10) NAME(John) GPA(3.20)") { passed = false; }
    Student s2(32, "Sammy", 4.0);
    if (s1.isGPAGreater(s2)) { passed = false; }
    return passed;
}

bool testGradStudent() {
    bool passed = true;
    GradStudent gs1(10, "John", 3.2, 1986);
    if (gs1.toString() != "ID(10) NAME(John) GPA(3.20) GRADUATION-YEAR(1986)") { passed = false; }
    GradStudent gs2(32, "Sammy", 4.0);
    if (gs1.isGPAGreater(gs2)) { passed = false; }
    if (gs2.toString() != "ID(32) NAME(Sammy) GPA(4.00) GRADUATION-YEAR(2021)") { passed = false; }
    return passed;
}

bool testGetLowest() {
    bool passed = true;
    Student *s1 = new Student(10, "John", 1.11);
    Student *s2 = new Student(32, "Sammy", 4.0);
    GradStudent *gs1 = new GradStudent(89, "Linda", 3.41, 1986);
    GradStudent *gs2 = new GradStudent(1, "Steven", 2.1);
    vector<Student*> studentList;
    studentList.push_back(s1);
    studentList.push_back(s2);
    studentList.push_back(gs1);
    studentList.push_back(gs2);
    Student *lowestID;
    Student *lowestGPA;
    getLowest(studentList, lowestID, lowestGPA);
    if (lowestID->toString() != "ID(1) NAME(Steven) GPA(2.10) GRADUATION-YEAR(2021)" 
        || lowestGPA->toString() != "ID(10) NAME(John) GPA(1.11)" ) {
            passed = false;
    }
    return passed;
}


int main() {
    cout << "Testing Student: " << boolalpha << testStudent() << endl;
    cout << "Testing GradStudent: " << boolalpha << testGradStudent() << endl;
    cout << "Testing getLowest: " << boolalpha << testGetLowest() << endl;
    // Test createOneStudent through own input 
}