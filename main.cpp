#include <iostream>
#include "GenStack.h"
#include <fstream>
using namespace std;

int main(int argc, const char * argv[])
{
  // delimiterFromFile - a string that will be used to read each line from the
  // file given.
  string delimiterFromFile = "";
// fileName holds the file name and is stored in argv
string fileName = argv[1];
// file - is the stream object
ifstream file;
// if there are less than 2 command line arguments, then its invalid
 if(argc < 2)
 {
   cout << "Invalid command line arguments" << endl;
   return 1;
 }
 // keeps track of the number of strings
 int lineTracker = 1;
 // stack - our new stack
 GenStack<char> *stack = new GenStack<char>(5);
 // open the file
 file.open(fileName);
 cout << "Reading from file" << endl;
 while(!file.eof())
 {
   file >> delimiterFromFile;
  // if the file does not fail
  if(!file.fail())
  {
    // if we find a '{', '(', '[' then push onto the stack
     for(int i = 0; i < delimiterFromFile.length(); ++i)
     {
       cout << "Diag: i:" << i << endl;
       cout << "Line: " <<lineTracker<< endl;
       if(delimiterFromFile[i] == '{')
       {
          cout << "Diag: pushing '{' " << endl;
          cout << "Diag: delimiter " << i << ": " << delimiterFromFile[i] << endl;
          // push onto the stack
          stack->push(delimiterFromFile[i]);
          cout << "Diag: completed push of '{' "<< endl;
       }
       else if(delimiterFromFile[i] == '[')
       {
         cout << "Diag: pushing '[' " << endl;
         stack->push(delimiterFromFile[i]);
       }
       else if (delimiterFromFile[i] == '(')
       {
         cout << "Diag: pushing '(' " << endl;
         stack->push(delimiterFromFile[i]);
       }
       // if we encounter a '}', ']', ')'
       // pop the top from the stack
       else if (delimiterFromFile[i] == '}')
       {
         if(stack->isEmpty())
         {
          cout << "Error: found unmatched '}' (stack empty)" << " on line: " << lineTracker<< endl;
           return false;
         }
         if(stack->peek() != '{')
         {
           cout << "Error: '}' does not match " << stack->peek()<< " on line: " << lineTracker<< endl;
           return false;
         }
         stack->pop();
       }

       else if (delimiterFromFile[i] == ']')
       {
         if(stack->isEmpty())
         {
           cout << "Error: found unmatched ']' (stack empty)" << " on line: " << lineTracker<< endl;
           return false;
         }
         if(stack->peek() != '[')
         {
            cout << "Error: ']' does not match " << stack->peek()<<" on line: " << lineTracker<< endl;
           return false;
         }
         stack->pop();
       }

       else if (delimiterFromFile[i] == ')')
       {
         if(stack->isEmpty())
         {
           cout << "Error: found unmatched ')' (stack empty)" << " on line: " << lineTracker<< endl;
           return false;
         }
         if(stack->peek() != '(')
         {
           cout << "Error: ')' does not match " << stack->peek()<<" on line: " << lineTracker<< endl;
           return false;
         }
         stack->pop();
       }

     }
     lineTracker++;


   }
 }
 // Check, if the stack is empty
 // if it is empty then we have a match
 if(stack->isEmpty())
 {
   cout << "delimiter syntax is correct" << endl;
   cout << "would you like to analyze another file? " << endl;
 }
 // symbols did not match
 else
 {
   cout << "Error: end of file reached without closing delimiter: " << stack->peek()<< endl;
 }
 file.close();
 delete stack;

  return 0;
}
