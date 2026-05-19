#pragma once 
#include <iostream>
#include <iomanip>
#include <cctype>
#include "../../Core/clsUser.h"
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "clsUserUIHelper.h"

using namespace std;


class clsDeleteUser : protected clsScreen {
private :
    static void _PrintUserCard(clsUsers& User){
        clsUserUIHelper::PrintUserCard(User);
    }

public : 
    static void ShowDeleteUserScreen(){

        _DrawScreenHeader("Delete User Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName : ";
        UserName = clsInputValidate::ReadString();

        while(!clsUsers::IsUserExist(UserName)){
            cout << "\nUser With UserName (" << UserName << ") does not exist. ";
            cout << "\nPlease Enter Another One : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUsers User = clsUsers::FindUser(UserName);
        _PrintUserCard(User);

        cout << "\n\nAre You Sure Do You Want To Delete This User? [Y/N]? ";
        char Answer = 'n';
        cin >> Answer;
        if(toupper(Answer) == 'Y'){
            if(User.Delete()){
                cout << "\nUser Deleted Successfully. ";
            }
            else {
                cout << "\nError. UserName Was Not Deleted : Empty Object. ";
            }
        }
        else {
            cout << "\nDelete Cancelled. ";
        }
    }
};