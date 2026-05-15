#pragma once 
#include <iostream>
#include "clsUser.h"

using namespace std;


class clsUserUIHelper {
public :
    static void PrintUserCard(clsUsers& User){
        cout << "\nUser Card ";
        cout << "\n----------------------------------------------------";
        cout << "\nFirst Name           : " << User.FirstName();
        cout << "\nLast Name            : " << User.LastName();
        cout << "\nFull Name            : " << User.FullName();
        cout << "\nEmail                : " << User.Email();
        cout << "\nPhone                : " << User.Phone();
        cout << "\nUser Name            : " << User.UserName();
        cout << "\nPassWord             : " << User.PassWord();
        cout << "\nPermissions          : " << User.Permissions();
        cout << "\n----------------------------------------------------";
    }
};