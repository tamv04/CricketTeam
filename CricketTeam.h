//
//  CricketTeam.h
//  Project 2 cs 32
//
//  Created by tam vo on 7/6/23.
//

#ifndef CricketTeam_h
#define CricketTeam_h
#include <iostream>
#include <string>

typedef std:: string CricketType; // This can change to other types

struct Node
{
    std::string firstName;
    std::string lastName;
    Node* next;
    Node* prev;
    CricketType value; // check on this
};


class CricketTeam
{
public:
    CricketTeam(); // Create an empty CricketTeam list
        ~CricketTeam(); // destructor
    
    CricketTeam(const CricketTeam& src);
        const CricketTeam& operator=(const CricketTeam& src);
    // added those on top

bool noTeam() const; // Return true if the CricketTeam list
// is empty, otherwise false.
    
int cricketerCount() const; // Return the number of matches
// on the CricketTeam list.
    
bool addCricketer(const std::string& firstName, const std::string&
lastName, const CricketType& value);
    // If the full name (both the first and last name) is not equal
    // to any full name currently in the list then add it and return
    // true. Elements should be added according to their last name.
    // Elements with the same last name should be added according to
    // their first names. Otherwise, make no change to the list and
    // return false (indicating that the name is already in the
    // list).
    
    bool substituteCricketer(const std::string& firstName, const
    std::string& lastName, const CricketType & value);
    // If the full name is equal to a full name currently in the
    // list, then make that full name no longer map to the value it
    // currently maps to, but instead map to the value of the third
    // parameter; return true in this case. Otherwise, make no
    // change to the list and return false.
    
    bool addOrSubstitute(const std::string& firstName, const
    std::string& lastName, const CricketType& value);
    // If full name is equal to a name currently in the list, then
    // make that full name no longer map to the value it currently
    // maps to, but instead map to the value of the third parameter;
    // return true in this case. If the full name is not equal to
    // any full name currently in the list then add it and return
    // true. In fact, this function always returns true.
    
    bool releaseCricketer(const std::string& firstName, const
    std::string& lastName);
    // If the full name is equal to a full name currently in the
    // list, remove the full name and value from the list and return
    // true. Otherwise, make no change to the list and return
    // false.
    
    bool rosteredOnCricketTeam(const std::string& firstName, const
    std::string& lastName) const;
    // Return true if the full name is equal to a full name
    // currently in the list, otherwise false.
    
    bool searchForCricketer(const std::string& firstName, const
    std::string& lastName, CricketType& value) const;
    // If the full name is equal to a full name currently in the
    // list, set value to the value in the list that that full name
    // maps to, and return true. Otherwise, make no change to the
    // value parameter of this function and return false.
    
    bool checkTeamForCricketer(int i, std::string& firstName,
    std::string& lastName, CricketType & value) const;
    // If 0 <= i < size(), copy into firstName, lastName and value
    // parameters the corresponding information of the element at
    // position i in the list and return true. Otherwise, leave the
    // parameters unchanged and return false. (See below for details
    // about this function.)
    
    void tradeCricketTeams(CricketTeam& other);
    // Exchange the contents of this list with the other one.
    
private: // added this
    Node* head = nullptr; // this is for empty lists 
    };


// non member functions goes here
bool mergeCricketers(const CricketTeam & odOne, const CricketTeam & odTwo,CricketTeam & odJoined);
void checkCricketers (const std::string& fsearch,const std::string& lsearch,const CricketTeam& odOne, CricketTeam& odResult);

#endif /* CricketTeam_h */
