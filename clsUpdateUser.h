#pragma once
#include <iostream>
#include <cctype>
#include <iomanip>
#include "clsUser.h"
#include "clsUsersInputHelper.h"
#include "clsUserUIHelper.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateUser : protected clsScreen {
private :
    static void _ReadUserInfo(clsUsers& User){
        clsUsersInputHelper::ReadUsersInfo(User);
    }

    static void _PrintUserCard(clsUsers User){
        clsUserUIHelper::PrintUserCard(User);
    }

public : 
    static void ShowUpdateUserScreen(){
        _DrawScreenHeader("Update User Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName : ";
        UserName = clsInputValidate::ReadString();

        while(!clsUsers::IsUserExist(UserName)){
            cout << "\nUser With UserName (" << UserName << ") Does Not Exist. ";
            cout << "\nPlease Enter Another One : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUsers User = clsUsers::FindUser(UserName);
        _PrintUserCard(User);

        _ReadUserInfo(User);

        clsUsers::enSaveResults SaveResult = User.Save();

        switch (SaveResult)
        {
        case clsUsers::enSaveResults::svSucceed:
            cout << "\nUser Updated Successfully. ";
            _PrintUserCard(User);
            break;

        case clsUsers::enSaveResults::svFailedEmptyObject:
            cout << "\nError. User Was Not Updated : Empty Object. ";
            break;

        case clsUsers::enSaveResults::svFailedUserNameExist:
            cout << "\nUpdate Cancelled. ";
            break;
        }
    }
};