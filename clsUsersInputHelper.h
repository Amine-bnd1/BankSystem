#pragma once
#include <iostream>
#include "clsUser.h"
#include <cctype>
#include "clsInputValidate.h"

using namespace std;

class clsUsersInputHelper
{
private:
    static int ReadPermissions()
    {

        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give all access? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            return -1;
        }

        cout << "\nDo You Want To Give Access To : \n";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUsers::enPermissions::pListClient;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUsers::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUsers::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUsers::enPermissions::pUpdateClient;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUsers::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUsers::enPermissions::pTransactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUsers::enPermissions::pManageUsers;
        }

        cout << "\nShow Login Register? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUsers::enPermissions::pLoginRegister;
        }

        return Permissions;
    }

public :
    static void ReadUsersInfo(clsUsers &User)
    {

        cout << "\nPlease Enter First Name : ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nPlease Enter Last Name : ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nPlease Enter Email : ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nPlease Enter Phone : ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nPlease Enter PassWord : ";
        User.SetPassWord(clsInputValidate::ReadString());

        cout << "\nPlease Enter Permissions ";
        User.SetPermissions(ReadPermissions());
    }
};