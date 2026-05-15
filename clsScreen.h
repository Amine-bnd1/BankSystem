#pragma once
#include <iostream>
#include "clsUser.h"
#include <string>
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{

public:
    static void _PrintLine(short Width = 97, char Symbol = '-')
    {
        cout << string(Width, Symbol) << endl;
    }

    static void _DrawScreenHeader(const string &Title, const string &SubTitle = "")
    {
        _PrintLine();

        cout << "\n\t\t\t " << Title << endl;

        if (!SubTitle.empty())
        {
            cout << "\t\t\t " << SubTitle << endl;
        }

        _PrintLine();

        cout << "\t\t\t--------------------------------------------------------\n";
        cout << "\t\t\t User : " << CurrentUser.UserName() << "\n";
        cout << "\t\t\t Date : " << clsDate::DateToString(clsDate()) << "\n";
        cout << "\t\t\t--------------------------------------------------------\n\n";
    }

    static bool CheckAccessRight(clsUsers::enPermissions Permission){
        if (!CurrentUser.CheckAccessPermission(Permission)){
            cout << "\t\t\t--------------------------------------------------------\n";
            cout << "\n\t\t\t\t\tAccess Denied! Contact Your Admin.\n";
            cout << "\t\t\t--------------------------------------------------------\n";

            return false;
        }

        return true;
    }

};
