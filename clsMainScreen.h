#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsShowClientList.h"
#include "clsAddNewClient.h"
#include "clsUpdateClientInfo.h"
#include "clsDeleteClient.h"
#include "clsFindClient.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsRegisterLoginUsers.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    enum enMainScreenOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eRegisterLogin = 8,
        eExit = 9
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "\nChoose what do you want to do? [1 To 9]? ";
        return (short)clsInputValidate::ReadDblNumberBetween(1, 9, "Enter a Number between 1 and 8 : ");
    }

    static void _GoBackToMainMenue()
    {
        cout << "\n\nPress Enter to go back to Main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        _ShowMainMenue();
    }

    static void _ShowAllClientScreen()
    {
        clsShowClientList::ShowClientListScreen();
    }

    static void _ShowAddNewClientScreen()
    {
        clsAddNewClient::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClient::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientInfo::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClient::ShowFindClientScreen();
    }

    static void _ShowTransactionsScreen()
    {
        clsTransactionsScreen::ShowTransationsMenue();
    }

    static void _ShowManageUsersScreen()
    {
        clsShowManageUsersScreen::ShowManageUsersScreen();
    }

    static void _LoginRegisterUsersScreen(){
        clsRegisterLoginUsers::ShowRegisterLoginUsers();
    }

    static void _Logout()
    {
        CurrentUser = clsUsers::FindUserByUserNameAndPassWord("", "");
    }

    static void _PerfromMainMenueOption(enMainScreenOptions MainMenueOptions)
    {
        switch (MainMenueOptions)
        {
        case enMainScreenOptions::eListClients:
            system("clear");
            _ShowAllClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainScreenOptions::eAddNewClient:
            system("clear");
            _ShowAddNewClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainScreenOptions::eDeleteClient:
            system("clear");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainScreenOptions::eUpdateClient:
            system("clear");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainScreenOptions::eFindClient:
            system("clear");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainScreenOptions::eShowTransactionsMenue:
            system("clear");
            _ShowTransactionsScreen();
            _GoBackToMainMenue();
            break;

        case enMainScreenOptions::eManageUsers:
            system("clear");
            _ShowManageUsersScreen();
            _GoBackToMainMenue();
            break;

        case enMainScreenOptions::eRegisterLogin:
            system("clear");
            _LoginRegisterUsersScreen();
            _GoBackToMainMenue();
            break;

        case enMainScreenOptions::eExit:
            system("clear");
            _Logout();
            break;
        }
    }

    static void _PrintMenuLine(int Width = 55, int LeftPadding = 30)
    {
        cout << string(LeftPadding, ' ') << string(Width, '=') << endl;
    }

public:
    static void PrintLine(int Width = 113)
    {
        cout << string(Width, '=') << endl;
    }

    static void _ShowMainMenue()
    {
        system("clear");
        _DrawScreenHeader("\t\tMain Screen");

        _PrintMenuLine();
        cout << string(30, ' ') << "\t\tMain Menu\n";
        _PrintMenuLine();

        cout << string(30, ' ') << "\t\t[1] Show Client List.\n";
        cout << string(30, ' ') << "\t\t[2] Add New Client.\n";
        cout << string(30, ' ') << "\t\t[3] Delete Client.\n";
        cout << string(30, ' ') << "\t\t[4] Update Client Info.\n";
        cout << string(30, ' ') << "\t\t[5] Find Client.\n";
        cout << string(30, ' ') << "\t\t[6] Transactions Menu.\n";
        cout << string(30, ' ') << "\t\t[7] Manage Users.\n";
        cout << string(30, ' ') << "\t\t[8] Login Register.\n";
        cout << string(30, ' ') << "\t\t[9] Logout.\n";

        _PrintMenuLine();

        _PerfromMainMenueOption((enMainScreenOptions)_ReadMainMenueOption());
    }
};
