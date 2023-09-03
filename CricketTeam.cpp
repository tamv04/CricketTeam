//
//  CricketTeam.cpp
//  Project 2 cs 32
//
//  Created by tam vo on 7/6/23.
//

#include "CricketTeam.h"
#include <iostream>
#include <string>
using namespace std;

CricketTeam:: CricketTeam() // look into this
{
    head = nullptr;
}

CricketTeam:: ~CricketTeam() // destructor
{
    Node *p = head;
        while (p != nullptr)
        {
            Node *q = p->next;
            delete p;
            p = q;
        }
    
}
// copy constructor
CricketTeam::CricketTeam(const CricketTeam& src)
{
    // empty list case
    if (src.head == nullptr)
    {
        head = nullptr;
        return;
    }
    
    head = new Node; // making a new list to copy stuff over
    Node *k = src.head; // using this to access the old list
    Node *p = head; // p is the new list
    p->lastName = k -> lastName; // copying values over for the first node aka head pointer
    p->firstName = k -> firstName;
    p->value = k -> value;
    
    
    p -> prev = nullptr; // because P is the head and there's no previous to it always do this if it's not circular
  
    while ( k->next != nullptr) // k is our old list and we want to copy at k is what we use to know when to stop
    {
        
     p->next = new Node; // were at element 2 right now  we're making a new node for the new p list
    
        p->next->prev = p; // p->next->prev is pointing to 1 because p is 1 (left hand side is what changes and right is what it changes too) this is for the prev pointer part
        
        k = k->next; // moves to next node of old list
        
        p->next->lastName = k -> lastName; // copying values over
        p->next->firstName = k -> firstName;
        p->next->value = k -> value;
        
        p = p->next; // this just keeps making on within the new list to keep copying over value
        
    }
    
    p-> next = nullptr; // when this reaches the end. k already ended and now p needs to end to
    
}

const CricketTeam& CricketTeam::operator=(const CricketTeam& rhs) // rhs is target because it's getting passed in example we would want to change cricket team A to RHS (because it's getting passed in)
{
    if( this != &rhs) // if already the same list then don't need to swap anything but if it isn't
    {
        CricketTeam temp(rhs); // we're storing rhs in a temp varible
        this->tradeCricketTeams(temp); // putting temp aka (RHS) into cricketeam A (reason it's temp because temp is getting passed in) whatever is in parameter is what you want to change it to
        // "this" is getting swapped with temp we're calling the swapping function on it
    }
    return *this;
}

bool CricketTeam::noTeam() const
{
    return (head == nullptr);} // return true if there's no team otherwise return false 

int CricketTeam::cricketerCount() const
{
    int i = 0;
    Node *p = head;
    while( p != nullptr)
    {
        i++;
        p = p -> next;
    }
    return i;
}

// If the full name (both the first and last name) is not equal
// to any full name currently in the list then add it and return
// true. Elements should be added according to their last name.
// Elements with the same last name should be added according to
// their first names. Otherwise, make no change to the list and
// return false (indicating that the name is already in the
// list).
bool CricketTeam::addCricketer(const string& firstName, const string& lastName, const CricketType& value)
{
    Node *p = head; // node means nothing unless it's connected to head because head is the only way to access your list
    head = p;
    // for an empty list case
    if ( head == nullptr)
    {
        Node *p = new Node; // making a new node
        p-> value = value; // setting the value from header file to the value in this parameter
        p->next = nullptr; // because also an empty list so only one element it's the end of the list
        p->prev = nullptr; // because empty list
        p-> firstName = firstName; // setting firstname from struct to parameter
        p-> lastName = lastName; // same thing here ^
        head = p;
        return true;
    }
    
    while ( p != nullptr)
    {
        if (p->lastName < lastName && p->next == nullptr) // Insert at the end
        {
            Node* lastNode = new Node;
                lastNode->value = value;
                lastNode->next = nullptr;
                lastNode->prev = p;
                lastNode->firstName = firstName;
                lastNode->lastName = lastName;
                p->next = lastNode;
                return true;
        }
        // checking if p is in the right spot to add things in p->next -> lastName is the lastName in the struct second node because "next" and -> lastName means you're getting the lastName from struct
        else if ( p-> lastName < lastName && p->next->lastName > lastName) // whoever is at head at P in the beginning but p changes
        {
            Node* ToBeAdded = new Node;
                        ToBeAdded->value = value;
                        ToBeAdded->next = p->next;
                        ToBeAdded->prev = p;
                        ToBeAdded->firstName = firstName;
                        ToBeAdded->lastName = lastName;
                        
                        p->next->prev = ToBeAdded;
                        p->next = ToBeAdded;
                        return true;
        }
        else if( head-> lastName > lastName) // case 2: only case when need to add to front is when the first lastName is already bigger (a=1)
        {
            Node *SpecialCase = new Node;
            SpecialCase-> value = value;
            SpecialCase->next = head; // head is me aka v because we're access it sepecial case is B and specialcase -> next is B's next, and now we're setting B's next to me
            SpecialCase->prev = nullptr; // B's prev is nothing because it's in front so is suppose to be null ptr
            SpecialCase-> firstName = firstName;
            SpecialCase-> lastName = lastName;
            head->prev = SpecialCase;
            head = SpecialCase; // head is now specialcase is new node aka B moving to the bottom because don't want to lose access too early
            return true;
        }
        
       else if( p-> lastName == lastName && p-> firstName == firstName)
        {
            return false; // the cricker already exisits
        }
        
        // to do check first name case : first name only matter if last are equal
        // somehow include this so it also covers front and end of list
        //check if last names are equal in the beginning
        // beginning middle and end cases
        // strag : conbine first and last name into one string but make sure last name is first , make sure caplization is the same
        else if (p->lastName == lastName) // Check if last names are equal
                {
                    // Compare the first names when the last names are equal
                    string fullName1 = p->firstName + " " + p->lastName;
                    string fullName2 = firstName + " " + lastName;

                    if (fullName1 == fullName2)
                    {
                        return false; // The cricketer already exists
                    }
                    else if (fullName1 > fullName2)
                    {
                        Node* K = new Node;
                        K->value = value;
                        K->next = p;
                        K->prev = p->prev;
                        K->firstName = firstName;
                        K->lastName = lastName;

                        if (p->prev != nullptr)
                        {
                            p->prev->next = K;
                        }
                        else
                        {
                            head = K;
                        }

                        p->prev = K;
                        return true;
                    }
                }

        else { p = p->next; }// Move to the next node
            }

            return false;
        }

// If the full name is equal to a full name currently in the
// list, then make that full name no longer map to the value it
// currently maps to, but instead map to the value of the third
// parameter; return true in this case. Otherwise, make no
// change to the list and return false.
bool CricketTeam::substituteCricketer(const string& firstName, const string& lastName, const CricketType &value)
{
    Node *p = head;
    while( p != nullptr)
    {
        if(p-> lastName == lastName)
            if( p-> firstName == firstName)
            {
                p->value = value;
                return true;
                
            }
        p = p->next; // going to the next node iterating.
    }
    return false;
}

// If full name is equal to a name currently in the list, then
// make that full name no longer map to the value it currently
// maps to, but instead map to the value of the third parameter;
// return true in this case. If the full name is not equal to
// any full name currently in the list then add it and return
// true. In fact, this function always returns true.
bool CricketTeam:: addOrSubstitute(const string& firstName, const string& lastName, const CricketType& value)
{
  if (substituteCricketer(firstName, lastName , value ) == true)
  {
      return true;
  }
  else
  {
      addCricketer(firstName, lastName , value);
      
  }
    return true;
    
}

// If the full name is equal to a full name currently in the
// list, remove the full name and value from the list and return
// true. Otherwise, make no change to the list and return
// false.
bool CricketTeam::releaseCricketer(const string& firstName, const string& lastName)
{
    Node *p = head;
    while ( p != nullptr)
    {
        if( p-> firstName == firstName && p-> lastName == lastName) // checks the name the following functions are excuted once it finds a match
        {
            if( p->prev != nullptr) // if the list was 123 and want to remove 2 ( because it contains the name of the cricketer) it checks that 1 is not the end of the list
            {
                p->prev->next = p->next; // removes 2 from the list example of doubly linked list because it skips over it
            }
            else
            {
                // check if p-> prev is the null pointer so head of list ( when we want to remove it)
                head = p->next; // for when p is the head of the list,this is when p->prev is null ptr indicating that there is no previous node before the current node. then we just update the head to remove the current head node from the list.
            }
            if ( p->next != nullptr) // checking if 2 is not a null ptr it isnt in this case because it isnt at the tail of list
            {
                p->next->prev = p->prev; // updating the prev pointer which is pointing at 1 to point to node 3 to update the list and remove 2
            }
            delete p;
            return true;
        }
        p= p-> next; // make sure this itterates
    }
    return false; // if none of those cases are true
}

// Return true if the full name is equal to a full name
// currently in the list, otherwise false.
bool CricketTeam::rosteredOnCricketTeam(const string& firstName, const string& lastName) const
{
    Node *p = head;
    
    while(p != nullptr)
    {
        if (p->lastName == lastName)
        {
                if (p->firstName == firstName)
                {
                    return true;
                }
        }
                p = p->next;
    }
            return false;
    
}


// If the full name is equal to a full name currently in the
// list, set value to the value in the list that that full name
// maps to, and return true. Otherwise, make no change to the
// value parameter of this function and return false.
bool CricketTeam::searchForCricketer(const string& firstName, const string& lastName, CricketType& value) const
{
    Node *p;
    p = head;
    while ( p != nullptr)
    {
        if ( p -> lastName == lastName)
            if( p-> firstName == firstName)
            {
                value = p->value;
                return true;
            }
        p = p->next;
    }
    return false;
}

// If 0 <= i < size(), copy into firstName, lastName and value
// parameters the corresponding information of the element at
// position i in the list and return true. Otherwise, leave the
// parameters unchanged and return false. (See below for details
// about this function.)
bool CricketTeam::checkTeamForCricketer(int i, string& firstName, string& lastName, CricketType & value) const
{
    if ( 0 <= i && i < cricketerCount()) // setting the given boundaries
    {
        Node *p; // if given information of i is value when we point p to the head of the list
        p = head;
        for( int j = 0; j < i; j++) // going through the list until it reaches i
        {
            if ( p == nullptr) // checks if p has reached the end of the list if it has then exit the loop
                break;
            p = p-> next; // moving to the next node (list)
        }
        
        if (p != nullptr) // if p hasnt reached the end of the list it means it found the target of i and now is copying over the information into it
        {
            firstName = p->firstName; // copying over the information
            lastName = p-> lastName;
            value = p->value;
            return true;
        }
    }
    return false; // if doesnt mean any of these conditions
}


// Exchange the contents of this list with the other one.
void CricketTeam::tradeCricketTeams(CricketTeam& other)
{
    Node *tempPtr = this->head;
    this->head = other.head; // want to acess the head of other
    other.head = tempPtr;
}



// NON MEMEBER FUNCTIONS GOES HERE need to check on these

bool mergeCricketers(const CricketTeam & odOne, const CricketTeam & odTwo,CricketTeam & odJoined)
{
    odJoined = odOne;
    string firstName;
    string lastName;
    CricketType value;
    
    bool results = true;
    
    int i = 0;
    while (odTwo.checkTeamForCricketer(i, firstName, lastName, value)) // looping through here to check for cricketers
    {
        if (odJoined.addOrSubstitute(firstName, lastName, value)){}
        else
        {
            CricketType CheckingValue;
            odOne.searchForCricketer(firstName, lastName, CheckingValue);
            
            if (CheckingValue == value) {}
            else
            {
                odJoined.releaseCricketer(firstName, lastName);
                results = false;
            }
        }
        
        i++;
    }
    
    return results;
}


void checkCricketers (const std::string& fsearch,const std::string& lsearch,const CricketTeam& odOne, CricketTeam& odResult)
{
    odResult = odOne;
    string firstName;
    string lastName;
    CricketType value;
    bool ignoreFirst = (fsearch == "*");
    bool ignoreLast = (lsearch == "*");
    
    
    int i = 0;
    while (odOne.checkTeamForCricketer(i, firstName, lastName, value)) {
        if (ignoreFirst) {
            if (ignoreLast)
                return; // Same list so don't need to change odResult
            
            else if (lastName != lsearch)
                odResult.releaseCricketer(firstName, lastName); // this will remove when checking for the lastname within the cricket list
            else { } // will do nothing here
        }
        else
        {
            if (firstName != fsearch)
                odResult.releaseCricketer(firstName, lastName); // checking first name if they are different will remove
            else {
                if (ignoreLast) { } // Same first name ignore last name don't remove
                else {
                    if (lastName != lsearch)
                        odResult.releaseCricketer(firstName, lastName); // going to remove if they are different
                    else { } // does nothing here
                }
            }
        }
        i++;
    }
}
