#pragma once
#include <iostream>
#include <string>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUsersInputHelper.h"
#include "clsUserUIHelper.h"

using namespace std;


class clsAddNewUser : protected clsScreen {
private :
    static void _ReadUserInfo(clsUsers& User){
        clsUsersInputHelper::ReadUsersInfo(User);
    }

    static void _PrintUserCard(clsUsers& User){
        clsUserUIHelper::PrintUserCard(User);
    }


    
public :
    static void ShowAddNewUserScreen(){

        _DrawScreenHeader("Add New User Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName : ";
        UserName = clsInputValidate::ReadString();

        while (clsUsers::IsUserExist(UserName)){
            cout << "\nUser With UserName (" << UserName << ") already exists. ";
            cout << "\nPlease Enter Another One : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUsers NewUser = clsUsers::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);

        
        clsUsers::enSaveResults SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case clsUsers::enSaveResults::svSucceed:
            cout << "\nUser Added Successfully. ";
            _PrintUserCard(NewUser);
            break;

        case clsUsers::enSaveResults::svFailedEmptyObject:
            cout << "\nError. User Was Not Added : Empty Object. ";
            break;

        case clsUsers::enSaveResults::svFailedUserNameExist:
            cout << "\nError. User Was Not Added : UserName Already Exists. ";
            break;
        }
    }
};