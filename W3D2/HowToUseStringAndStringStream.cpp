#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

void  printStringInfo(const string & s)
{
   /*
          s : object
          . : member operator
          length() : method
    */
   cout << "Length:  " <<  s.length() << endl ;
   cout << "Empty:   " <<  boolalpha << s.empty()  << endl ;
   cout << "First character: " << s.at(0) << endl ;
   for(int count=0; count < s.length() ; count++)
       cout << "Ch: " << s.at( count ) << endl ;

   for(int count=0; count < s.length() ; count++)
       cout << "Ch: " << s[ count ] << endl ;
}

int main()
{
   string msg = "Hello" ;  // msg is just another variable: msg is a C++ object
   printStringInfo(msg);

   stringstream sout ;  // sout stringstream object - behave and use just like cout
   
   string part1 = "Hello" ;
   string part2 = ", World!" ;
   string greeting = part1 + part2 ;  // concatenate strings
   cout << greeting << endl; 

   string header = "The price is" ;
   double price  = 1.2355 ; 
   string description = header + to_string(price) ; // to_string is a function that may not be avail

   sout << fixed ; 
   sout << header << setprecision(2) <<  price << endl ;
   string formatted = sout.str() ;  // conver the buffer stream back a string object
   cout << formatted ;

   string item = "9.7865  a box of candies" ;
   stringstream  sin(item) ;  // sin is an input stringstream object just like cin

   double unitPrice ;
   sin >> unitPrice ; // read the data from the "sin" object - unitPrice will contain 9.7865

   string itemDesc ;
   getline(sin, itemDesc) ; // read online from the sin - which contains "    a box of candies"
   cout << itemDesc;

   return 0 ;
}