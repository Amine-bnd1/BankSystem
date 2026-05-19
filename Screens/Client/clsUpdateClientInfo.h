#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "clsClientUIHelper.h"
#include "../clsScreen.h"
#include "clsClientInputHelper.h"

using namespace std;

class clsUpdateClientInfo : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        clsClientInputHelper::ReadClientInfo(Client);
    }

    static void _PrintClientCard(clsBankClient& Client)
    {
        clsClientUIHelper::PrintClientCard(Client);
    }

public:
    static void ShowUpdateClientScreen()
    {
        if(!CheckAccessRight(clsUsers::enPermissions::pUpdateClient)){
            return;
        }

        
        _DrawScreenHeader("Update Client Info Screen");

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

        _ReadClientInfo(Client);

        clsBankClient::enSaveResults SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nClient Updated Successfully. ";
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError. Account Was Not Updated : Empty Object. ";
            break;

        case clsBankClient::enSaveResults::svFaildAccountNumberExist:
            cout << "\nError. Account Was Not Updated : Account Number Already Exists. ";
            break;
        }
    }
};