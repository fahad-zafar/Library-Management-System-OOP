#pragma once
#include <iostream>
#include <string>
#include <vector>
class LibItem;
class User;
using namespace std;

class LMS
{
private:
    vector <User *> all_users;
    vector <LibItem *> all_items;
    double fineCollected;
public:
    LMS ();
    double getCollectedFine ();
    vector <User *> getAllUsers ();
    vector <LibItem *> getAllItems ();
    void setFineCollected(double);
    bool searchByTitle (string);
    bool searchByAuthor (string);
    bool searchBySubject (string);
    void setItemStatus (string);
    vector <string> getItemsFromTitle (string);
    vector <string> getItemsFromAuthor (string);
    vector <string> getItemsFromSubject (string);
    User* getUserFromID (string);
    LibItem* getItemFromID (string);
    LibItem* getItem (string);
    void setBorrowerFine (string, double);
    void addItem (LibItem *);
    void addUser (User *);
    void delItem (LibItem *);
    void changeInfo (string, string, string, string, string);
    void changeUserInfo (string, string);
    void putItemOnHold (User*, LibItem *);
};

