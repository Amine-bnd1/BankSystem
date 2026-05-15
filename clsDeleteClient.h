#pragma once 
#include <iostream>
#include <cctype>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientUIHelper.h"

using namespace std;



class clsDeleteClient : protected clsScreen {

private :

    static void _PrintClientCard(clsBankClient& Client){
        clsClientUIHelper::PrintClientCard(Client);
    }

    public :

    static void ShowDeleteClientScreen(){

        if (!CheckAccessRight(clsUsers::enPermissions::pDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("Delete Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();


        while(!clsBankClient::IsClientExist(AccountNumber)){
            cout << "\nClient With Account Number (" << AccountNumber << ") does not exist. ";
            cout << "\nPlease Enter Another One : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::FindClient(AccountNumber);
        _PrintClientCard(Client);


        char Answer = 'n';
        cout << "\nAre You Sure Do You Want To Delete This Client? [Y/N]? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if(Client.DeleteClient()){
                cout << "\nClient Deleted Successfully. ";
            }
            else {
                cout << "\nError. Account Was Not Deleted.";
            }
        }
        else {
            cout << "\nNO, Account Was Not Deleted. ";
        }
    }
};
