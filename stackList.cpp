//Jehaan Joseph & Thamer Matar
//Title: Stacklist
//Project: Lab Assignment 2

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
#include "stack.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <sstream>

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We have a member field that must be initialised to NULL
//PostCondition: The constructor creates a new class with the appropriate member field
//               (the "top" pointer) initialsed to NULL.
Stack::Stack()
{
    top = NULL; //initialises the top node of the stack list
}


////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We have a class that we are done using and its allocated memory must be returned
//PostCondition: The destructor is called to free the top and every subsequent node created for the stack
Stack::~Stack() //this is the default destructor
{
    StackFramePtr Current = top;
    StackFramePtr After = Current->next;

    while(After != NULL)            //this while loop goes through each node
    {                               //and returns the memory allocated to
        delete Current;             //that node
        Current = After;
        After = After->next;
    }
}

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We have a stack and we are unsure whether it is empty or not
//PostCondition: The function will return true if the stack is empty
//                otherwise it returns false, which means the stack is not empty
bool Stack::empty()
{
    if(top == NULL)
    {
        return true;   //returns true if it is empty
    }
    else
    {
        return false;   //else it returns false
    }
}

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: Strings and their string lengths need to be outputted from the class
//PostCondition: Each string with its string length will be outputted
//                  if the stack is empty, the function outputs a statement saying that it is emtpy
ostream &operator<<(ostream &output, Stack &myStackList)
{
    StackFramePtr location = myStackList.top;

    if(myStackList.top == NULL)                 //checks to see if the stack is empty
    {

        myStackList.top = new StackFrame;       //if the stack is empty, a new node is created
        myStackList.top->next = NULL;           //at the top and
        output << "The stack is empty" << endl; //a statement it outputted saying that the stack is empty
        return output;
    }
    else
    {
        while(location != NULL)                                                             //if the stack is not empty
        {
        output << *(location->str) << " (length = " << location->num_char << ")" << endl;   //each string with its length is
        location = location->next;                                                          //outputted
        }
        output << endl;
    }

    return output;
}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: Strings need to be inputted into the class
//PostCondition: Each new string entered will create a new node in the class
istream &operator>>(istream &input, Stack &myStackList)
{
    string s;               //the string that is entered by the user is stored in a variable
    input >> s;
    myStackList.push(s);    //the string is then pushed into the stack

    return input;
}

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: A new node must be inserted into the top of the stack
//PostCondition: We first check if the stack is empty, if it is then we are inserting the top node
//               If it is not, then we are inserting a node at the top, while pushing back
//               the other nodes
void Stack::push(string& str)
{
    StackFramePtr Temp;

    //Case - empty list
    if(empty() == true)
    {
        top = new StackFrame;//Create a new node head
        top->str = new string(str);//Place the string at the top
        top->num_char= str.size();//Place the size of the string at the top
        top->next = NULL; //setting the next pointer = null
    }
    else
    {
        Temp = new StackFrame;//Create a new node
        Temp -> str = new string(str);//Place the string in the node
        Temp->num_char= str.size();//Place the size of the string in the node
        Temp -> next = top; /////point the new node to the top
        top = Temp;//The top is now the new node
    }
}

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We want to remove the top most value of the stack
//PostCondition: We look at the first node then we go into that node to remove the string and discard it
//               after we remove the string, the succeeding node is made the top
string Stack::pop()
{
    string *topString;
    string output;
    StackFramePtr removeTop;

    if(empty() == true)     //checks to see if the stack is empty
    {
        top = new StackFrame;//Create a new node head
        top->next = NULL; //setting the next pointer = null
        cout << "The stack is empty";//returns error message
        return output;
    }
    else
    {
        topString = top -> str;     //If the stack is not empty
        removeTop = top;
        top = removeTop -> next;
        removeTop -> next = NULL;
        return output;              //removes the top most node
    }

    delete removeTop;
    delete topString;
}

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are removing all strings of a length that are specified by the user
//PostCondition: We first search for the strings that of the length we want to remove, once
//               we find the string, we then move it into another stack and we update the first stack
//               without the strings we removed
StackFramePtr Stack::remove_strings_length(int length)
{
    string removedString;
    StackFramePtr current,stringAfter;
    Stack removedStack;

    if(empty())              //Checks if stack is empty
    {
        top = new StackFrame;//Create a new node head
        top->next = NULL; //setting the next pointer = null
        cout << "The stack is empty";//returns error message
        return NULL;
    }

    while(top && top->num_char == length)   //This loops specifically checks the top of the stack to see if
    {                                       //the length of the string at the top matches the specified length
        current = top;
        removedString = *(current->str);
        removedStack.push(removedString);   //moves the selected string into the new stack
        top = top->next;                    //makes the next node the top
    }

    current = top;
    stringAfter = current->next;

    while(stringAfter != NULL)                  //this loop goes through the rest of the stack
    {                                           //and searches for strings that match the specified length
        if(stringAfter->num_char == length)
        {
            current->next = stringAfter->next;
            removedString = *(stringAfter->str);
            removedStack.push(removedString);
        }
        else
        {
            current = current->next;

        }
        stringAfter = stringAfter->next;
    }

    cout << removedStack;

    return NULL;
}
