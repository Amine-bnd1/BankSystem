#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "clsClientUIHelper.h"
#include "../clsScreen.h"

using namespace std;

class clsFindClient : protected clsScreen
{

private:
    static void _PrintClientCard(clsBankClient &Client)
    {
        clsClientUIHelper::PrintClientCard(Client);
    }

public:
    static void ShowFindClientScreen()
    {
        if(!CheckAccessRight(clsUsers::enPermissions::pFindClient)){
            return;
        }

        _DrawScreenHeader("Find Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient With Account Number (" << AccountNumber << ") does not exist. ";
            cout << "\nPlease Enter Another One : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::FindClient(AccountNumber);
        _PrintClientCard(Client);
    }
};