#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

bool checkHelpOption(int argc, char * argv[]) {
    for(int i = 0; i < argc; i++) {
        if (argv[i][2] == '\0') {
            if ((argv[i][0] == '/' && (argv[i][1] == '?' || argv[i][1] == 'h')) || (argv[i][0] == '-' && argv[i][1] == '?')) {
                return true;
            }
        }
    }
    return false;
}

void * getDynamicPointerToMaxAndMin(double array[], int size, double* pMax, double* pMin) {
    pMax = new double;
    pMin = new double;
    double max = array[0];
    double min = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }
    *pMax = max;
    *pMin = min;
}

int main(int argc, char * argv[]) {
}