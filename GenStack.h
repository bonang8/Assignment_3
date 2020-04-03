#include <iostream>
#include <stdexcept> // defines logic_error exception
using namespace std;

// make the class generic by utilizing a template class 
template <typename GenStackType> class GenStack {
    // genStackArray is the stack based array that is type GenStackType
    GenStackType*genStackArray;
    // m_Size - holds the size
    int m_Size;
    int top;

  public:
    // constructor
    GenStack()
    {
      m_Size = 10;
      top = -1;
      genStackArray = new GenStackType(10);
    }
    // overloaded constructor
    GenStack(int size)
    {
      m_Size = size;
      top = -1;
      genStackArray = new GenStackType(m_Size);
    }
    // destructor
    ~GenStack()
    {
      // deleting pointer to an array of GenStackType elements
      delete[] genStackArray;
    }

    // createNewStack - allows it to automatically allocate more room for itself when it fills up
    void createNewStack()
    {
      // tempSize - holds the new maximized size
      int tempSize = 0;
      // Assign m_tempSize it to the newly computed bigger size
      tempSize = m_Size + m_Size;
      // Create temp ptr to the newly allocated array whose size is bigger
      GenStackType* genNewStackArray = new GenStackType[tempSize];
      // Populate the new array with the old array elements
      for( int i = 0; i < m_Size; ++i)
      {
         genNewStackArray[i] = genStackArray[i];
      }
      delete genStackArray;
      genStackArray = genNewStackArray;
      // assign the m_tempSize to m_size
      m_Size = tempSize;

    }
    // push - pushes GenStackTypes onto the stack
    void push(GenStackType object)
    {
      // if the stack is full
      // call the newStack function to allocate more space
      if(isFull())
      {
        cout << "Info: stack is full when attempting to push"<< endl;
        cout << "expanding stack size" << endl;
        createNewStack();
        genStackArray[++top] = object;
      }
      // else push normally onto the stack
      else
      {
        genStackArray[++top] = object;
      }
    }

    GenStackType pop() throw(logic_error)
    {
      // if empty, throw logic_error and state the error.
      if(isEmpty())
      {
         throw logic_error("Error: stack is empty on pop");
      }
      return genStackArray[top--];
    }
    // isEmpty - checks if its empty
    bool isEmpty()
    {
      return(top == -1);
    }
    //isFull - checks if full
    bool isFull()
    {
      return (top == m_Size - 1);
    }
    // peek - allows you to check at the top of the stack without popping off
    // the top of the stack.
    GenStackType peek()
    {
      if(!isEmpty())
      {
        return genStackArray[top];
      }
      else
      {
        return -1;
      }
    }

};
