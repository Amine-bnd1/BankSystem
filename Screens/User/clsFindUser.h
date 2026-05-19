#pragma once 
#include <iostream>
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "clsUserUIHelper.h"
#include "../clsScreen.h"

using namespace std;


class clsFindUser : protected clsScreen {
private :
    static void _PrintUserCard(clsUsers& User){
        clsUserUIHelper::PrintUserCard(User);
    }

public :
    static void ShowFindUserScreen(){

        _DrawScreenHeader("Find User Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName : ";
        UserName = clsInputValidate::ReadString();

        while(!clsUsers::IsUserExist(UserName)){
            cout << "\nUser With UserName (" << UserName << ") Does Not Exist. ";
            cout << "\nPlease Enter Another UserName : ";
            UserName = clsInputValidate::ReadString();
        }

        
        clsUsers User = clsUsers::FindUser(UserName);

        if(!User.IsEmpty()){
            cout << "\nUser Found!";
        }
        else {
            cout << "\nUser Was Not Found!";
        }
        _PrintUserCard(User);
    }
};
