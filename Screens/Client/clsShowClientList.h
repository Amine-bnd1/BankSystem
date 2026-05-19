#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <vector>
#include "../../Core/clsBankClient.h"
#include "../clsScreen.h"

using namespace std;

class clsShowClientList : protected clsScreen
{
private:
    static void PrintClientRecord(clsBankClient &Client)
    {
        cout << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(25) << left << Client.FullName();
        cout << "| " << setw(25) << left << Client.Email();
        cout << "| " << setw(15) << left << Client.Phone();
        cout << "| " << setw(12) << left << Client.Balance();
    }

public:
    static void ShowClientListScreen()
    {

        if (!CheckAccessRight(clsUsers::enPermissions::pListClient))
        {
            return;
        }

        vector<clsBankClient> VstClients = clsBankClient::GetClientsList();

        _DrawScreenHeader("\tShow Client List");

        cout << "\n\t\t\t\tClient List (" << VstClients.size() << ") Client(s).\n\n";

        _PrintLine();
        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(12) << "Balance" << endl;
        _PrintLine();

        if (VstClients.empty())
        {
            cout << "\nNo Data Available In The System.\n";
        }
        else
        {
            for (clsBankClient &Client : VstClients)
            {
                PrintClientRecord(Client);
                cout << endl;
            }
        }

        _PrintLine();
    }
};