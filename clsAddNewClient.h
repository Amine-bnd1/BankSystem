#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsClientInputHelper.h"
#include "clsScreen.h"
#include "clsClientUIHelper.h"

using namespace std;

class clsAddNewClient : protected clsScreen
{

private:
    static void _ReadClientInfo(clsBankClient &Client)
    {
        clsClientInputHelper::ReadClientInfo(Client);
    }

    static void _PrintClientCard(clsBankClient& Client){
        clsClientUIHelper::PrintClientCard(Client);
    }

public:
    static void ShowAddNewClientScreen()
    {

        if (!CheckAccessRight(clsUsers::enPermissions::pAddNewClient))
        {
            return;
        }


        _DrawScreenHeader("Add New Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter AccountNumber : ";
        AccountNumber = clsInputValidate::ReadString();

        while(clsBankClient::IsClientExist(AccountNumber)){
            cout << "\nClient with AccountNumber (" << AccountNumber << ") does already exist. ";
            cout << "\nPlease Enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\n\nClient Added Successfully. \n";
            _PrintClientCard(NewClient);
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError. Account Was Not Added : Empty Object.";
            break;

        case clsBankClient::enSaveResults::svFaildAccountNumberExist:
            cout << "\nError. Account Was Not Added : Account Already Exists.";
            break;
        }
    }
};