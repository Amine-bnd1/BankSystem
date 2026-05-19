#pragma once 
#include <iostream>
#include <iomanip>
#include <limits>
#include "../../Core/clsUser.h"
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "clsShowUsersListScreen.h"
#include "clsAddNewUser.h"
#include "clsDeleteUser.h"
#include "clsUpdateUser.h"
#include "clsFindUser.h"

using namespace std;


class clsShowManageUsersScreen : protected clsScreen {

private :
    enum enUsers
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5, 
        eMainMenu = 6
    };

    static void _ShowListUsersScreen()
    {
        clsShowUsersListScreen::ShowUsersListScreen();
    }

    static void _ShowAddNewUserScreen(){
        clsAddNewUser::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen(){
        clsDeleteUser::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen(){
        clsUpdateUser::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen(){
        clsFindUser::ShowFindUserScreen();
    }

    static void _GoBackToManageUsersScreen(){
        cout << "\n\nPress Enter to go back to Manage Users Menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    static short _ReadManageUsersMenuOptions(){
        short Choice = 0;
        cout << "\n" << setw(37) << "" << left << "Please Enter what do you want to choose [1-6]? ";
        Choice = clsInputValidate::ReadDblNumberBetween(1, 6, "Number is not within range, Enter again: ");
        return Choice;
    }

    static bool _PerformManageUsersMenu(enUsers UsersOptions){
        switch (UsersOptions)
        {
        case enUsers::eListUsers:
            system("clear");
            _ShowListUsersScreen();
            _GoBackToManageUsersScreen();
            return true;

        case enUsers::eAddNewUser:
            system("clear");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersScreen();
            return true;

        case enUsers::eDeleteUser:
            system("clear");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersScreen();
            return true;

        case enUsers::eUpdateUser:
            system("clear");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersScreen();
            return true;

        case enUsers::eFindUser:
            system("clear");
            _ShowFindUserScreen();
            _GoBackToManageUsersScreen();
            return true;

        case enUsers::eMainMenu:
            system("clear");
            return false;
        }
        return false;
    }


public :
    static void ShowManageUsersScreen(){

        if (!CheckAccessRight(clsUsers::enPermissions::pManageUsers))
        {
            return;
        }

        bool GobackToMainMenu = true;

        while (GobackToMainMenu){
            system("clear");
            _DrawScreenHeader("\t\tManage Users Screen");

            cout << setw(37) << left << "" << "=======================================\n";
            cout << setw(37) << left << "" << "          Manage Users Menu \n";
            cout << setw(37) << left << "" << "=======================================\n";
            cout << setw(37) << left << "" << "[1] List Users. \n";
            cout << setw(37) << left << "" << "[2] Add New User. \n";
            cout << setw(37) << left << "" << "[3] Delete User. \n";
            cout << setw(37) << left << "" << "[4] Update User. \n";
            cout << setw(37) << left << "" << "[5] Find User. \n";
            cout << setw(37) << left << "" << "[6] Main Menu. \n";
            cout << setw(37) << left << "" << "=======================================\n";

            GobackToMainMenu =  _PerformManageUsersMenu((enUsers)_ReadManageUsersMenuOptions());
        }
    }
};