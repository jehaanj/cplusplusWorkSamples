//Thamer Matar and Jeehan Joseph
//Title: Linkedlist
//Project: Lab Assignment #2

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
#include <iostream>
#include "linkedlist.h"

using namespace std;

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We have A Constructor because of the two classes "Front" and "Back"
//PostCondition: The constructor has the same name as the classes and doesnt return any type
//                Here our constructor's are called Front and Back
LinkedList::LinkedList() //this is the default constructor
{
    front = NULL;
    back = NULL;         //this initializes the first and the last node
}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: The destructor is a speacial member function
//PostCondition: The destructor is called to free both the "front" and "back"
LinkedList::~LinkedList() //this is the default destructor
{
    delete front;
    delete back; //We are deleting the two classes front and back

}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are checking if the list does not have any nodes
//PostCondition: We will return true if the list is empty
//                otherwise we will return false, that means the list is not empty
bool LinkedList::empty()    //checks if the list is empty
{
    if(front == NULL)  //checks if there is not head node
    {
        return true;   //returns true if it is empty
    }
    else
        return false;
}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are inserting a node at the front or head
//PostCondition: We first check if the list is empty, if it is then we are inserting the head node
//               If it is not, then we are inserting a node at the front (position 1), while pushing back
//               the other nodes and fixing their numbers
void LinkedList::insert_beginning(int value)
{
        ListNodePtr Temp1,location;//Two variable the I used to keep track of the position
                                   //and values of the node
        //Case - empty list
        if(front == NULL)//Checks if there is no Head node
        {
            front = back = new ListNode;//Create a new node head
            front -> value = value;//Place the value of the new node at the head
            front -> position = 1;//The position of the head node is 1
            front -> next = NULL;//making the next pointer equal to null
        }
        else //The list is not empty, we are inserting a node at the front
        {
        Temp1 = new ListNode;//We are creating the new variable we want to place at the front node
        Temp1->value = value;//placeing the value of the new node in the Temp1 variable
        Temp1->position = front->position;//make the Temp1 variable postion 1
        Temp1->next = front; //point the new node to the front



    for(location = front; location != NULL; location = location->next) //adjusting the postion of the nodes accordingly
    {
        location->position++;//move onto the next position
    }

    front = Temp1;//Temp1 is now the front variable
    }
}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are inserting a node at the back of the list
//PostCondition: Add the "value" to position N+1 in the list (at the back),
//               where N is the number of nodes previously in LinkedList object.
void LinkedList::insert_end(int value)
{
        ListNodePtr Temp2;//The variable I created to hold the value and postion of the
                          // node we want to put at the back

        //Case if the list is empty
        if(front == NULL)//Checks if the list is empty
        {
            front = back = new ListNode;//Create a new node head
            front -> value = value;//Place the value of the new node at the head
            front -> position = 1;//The position of the head node is 1
            front -> next = NULL;//making the next pointer equal to null
        }
        else //The list is not empty, we are inserting a node at the back
        {
            Temp2 = new ListNode;//We are creating the new variable we want to place at the back node
            Temp2->value = value;//placeing the value of the new node in the Temp2 variable
            Temp2->position = back->position +1;//gives the last position to the temp2 variable
            back->next = Temp2;//point the new node to the back
            Temp2->next = NULL;//Making the next pointer equal to NULL
            back = Temp2;//Temp2 is now the back variable
       }
}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are removing a value the user asked to be removed
//PostCondition: We first search for the value we want to remove, once
//               we find that value, we delete it, then we update the current list
//               without the value we removed
ListNodePtr LinkedList::remove_value(int val)
{
    LinkedList updatedlist;//This will be the list we place our updated values in
    ListNodePtr location;//This is to update the location of the values

    ListNode *Temp1=front;//A pointer to keep track of the front node
    ListNode *temp2=front->next;//temp2 is going to track front node
    while(front->value==val)//We are checking the value of the first node if it is equal to the value we want
    {
        updatedlist.insert_beginning(val);//We will remove the value "val" and update our current list
        Temp1->next=NULL;//making the next pointer equal to null
        Temp1=temp2;
        temp2=temp2->next;//we are setting our next pointer to null
        front=Temp1;// the front value is the "val" we want to remove
    }
    //Here we are checking the value of our next node to make sure if it is "val"
    while(temp2->next!=NULL)//We are checking if our next value is not equal to null
    {

        if(temp2->value==val)//If our second value equals to val
        {
            //We will remove the value "val" and update our current list
            updatedlist.insert_beginning(val);
            Temp1->next=temp2->next;
            temp2=Temp1->next;
        }
        else
        {
            //We keep the list like it is and move on to check the next variables
            Temp1=Temp1->next;
            temp2=temp2->next;

        }
    }

    if(back->value=val)//If our back value equals to "val"
    {
        //We will remove the value "val" and update our current list
        updatedlist.insert_beginning(val);
        Temp1->next=NULL;

    }
    for(location==front;location==back;location=location->next)//adjusting the postion of the values accordingly
    {
       location->position++;
    }
    return updatedlist.front;//Returning the updated list
}
 ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are removing the front value
//PostCondition: We first node then we go into that node to remove the value and discard it
//               after we remove the value, we update our list
int LinkedList::removefront()
{
    int headValue = 0;//This will keep track of the head value
    ListNodePtr delHead, location;// These two pointers will delete the head value and tell me the location
    if(front ->position ==1) //Checks if it is the head node
    {
        headValue = front -> value;//Headvalue will be pointed towards the front value
        delHead= front;//The value to be deleted will be the head
        front = delHead -> next;
        delHead ->next= NULL; //making the next pointer equal to null

    }
    for(location = front; location != NULL; location = location->next)//adjusting the postion of the values accordingly
    {
        location ->position--;
    }
    cout<<headValue<<endl<<endl;
    return headValue;

}

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are sorting the list
//PostCondition: we will be using selection sorting
//               we will have a pivot value that compares if the next variable is
//               equal bigger or smaller, from there we will either switch it or
//                it will stay in the same position and it will keep doing it
//                  till all the variables are done
void LinkedList::sort_linkedlist()
{
    ListNodePtr before, after,location,sorted;//These are the pointers that I will be using in my sort
    int Temp1;
    int numElements =0;
    for(location = front; location != NULL; location = location->next)//The number iteration
    {
            numElements++;
    }
    //These go throught the list, check if the value is equal greater or smaller
    //they then switch the value and keep doing it till the list is done
    for(int i = 0; i< numElements; i++)
    {
        for(location = front; location != NULL; location = location->next)
        {
            before = location;
            after = before->next;
            while(after!= NULL)
            {
                if (before->value > after->value)
                {
                    Temp1 = before->value;
                    before->value = after->value;
                    after->value = Temp1;
                }
                before = before->next;
                after = before->next;
      }
    }
  }
}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are outputing the values
//PostCondition: we will output the position with the value in each node
ostream &operator<<(ostream &output, LinkedList &myLinklist)
{
    ListNodePtr location = myLinklist.front;
    while(location != NULL)
    {
        output<<location -> position<<". "<<location ->value<<endl;
        location = location->next;

    }
    return output;

}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//PreCondition: We are inputing the values
//PostCondition: We will input a value to each node that we want
istream &operator>>(istream &input, LinkedList &myLinklist)
{
    ListNodePtr location = new ListNode;
    myLinklist.back->next = location;
    input >> location -> value;
    location -> position = myLinklist.back -> position +1;
    location -> next = NULL;
    myLinklist.back = location;
    return input;
}
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
