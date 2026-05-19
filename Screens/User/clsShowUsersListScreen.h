#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsUser.h"


using namespace std;

class clsShowUsersListScreen : protected clsScreen
{
private:
    static string _CutText(string Text, short Length)
    {
        if (Text.length() <= Length)
            return Text;

        return Text.substr(0, Length - 3) + "...";
    }

    static void _PrintLine()
    {
        cout << "-----------------------------------------------------------------------------------------------------------\n";
    }

    static void _PrintUserRecord(clsUsers& User)
    {
        cout << "| " << left << setw(15) << _CutText(User.UserName(), 15);
        cout << "| " << left << setw(25) << _CutText(User.FullName(), 25);
        cout << "| " << left << setw(15) << _CutText(User.Phone(), 15);
        cout << "| " << left << setw(30) << _CutText(User.Email(), 30);
        cout << "| " << right << setw(10) << User.Permissions() << " |\n";
    }

public:
    static void ShowUsersListScreen()
    {
        vector<clsUsers> vUsers = clsUsers::GetUsersList();
        string SubTitle = "(" + to_string(vUsers.size()) + ") User(s)";
        _DrawScreenHeader("Users List Screen", SubTitle);

        _PrintLine();
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(30) << "Email";
        cout << "| " << right << setw(10) << "Permissions" << "|\n";
        _PrintLine();

        if (vUsers.empty())
        {
            cout << "| " << left << setw(116) << "No users available in the system." << " |\n";
        }
        else
        {
            for (clsUsers& User : vUsers)
            {
                _PrintUserRecord(User);
            }
        }

        _PrintLine();
    }
};