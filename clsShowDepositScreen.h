#pragma once 
#include <iostream>
#include <cctype>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsClientUIHelper.h"
#include "clsInputValidate.h"

using namespace std;


class clsShowDepositScreen : protected clsScreen {

private :
    static void _PrintClientCard(clsBankClient& Client){
        clsClientUIHelper::PrintClientCard(Client);
    }

    static string _ReadAccountNumber(){
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public :
    static void ShowDepositScreen(){

        _DrawScreenHeader("Deposit Screen");

        string AccountNumber = _ReadAccountNumber();
        while(!clsBankClient::IsClientExist(AccountNumber)){
            cout << "\nClient With Account Number (" << AccountNumber << ") does not exist. ";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::FindClient(AccountNumber);
        _PrintClientCard(Client);

        double Amount = 0;
        cout << "\nPlease Enter The Amount You Want To Deposit : ";
        Amount = clsInputValidate::ReadDblNumber();


        if(Amount <= 0){
            cout << "\nInvalid Amount. Transaction Cancelled. ";
            return;
        }

        char Answer = 'n';
        cout << "\n\nAre You Sure Do You Want To Perform This Transaction ? [Y/N]? ";
        cin >> Answer;

        if(toupper(Answer) == 'Y'){
            Client.Deposit(Amount);
            cout << "\nTransaction Done Successfully. ";
            cout << "\nNew Balance is : " << Client.Balance();
        }

        else {
            cout << "\nTransaction Cancelled.";
        }
    }
};