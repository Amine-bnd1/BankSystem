#pragma once 
#include <iostream>
#include <iomanip>
#include<cctype>
#include "../../Core/clsBankClient.h"
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Global.h"

using namespace std;


class clsTransferScreen : protected clsScreen {
private:
    static void _PrintClientRecord(clsBankClient& Client){
        cout << "\nClient Card ";
        cout << "\n__________________________";
        cout << "\nFull Name    : " << Client.FullName();
        cout << "\nAcc Number   : " << Client.AccountNumber();
        cout << "\nBalance      : " << Client.Balance();
        cout << "\n__________________________";
    }

public:
    static void ShowTransferScreen(){
        _DrawScreenHeader("Transfer Screen");

        string SourceAccountNumber = "";
        string DestinationAccountNumber = "";

        cout << "\nPlease Enter Source Account Number : ";
        SourceAccountNumber = clsInputValidate::ReadString();

        while(!clsBankClient::IsClientExist(SourceAccountNumber)){
            cout << "\nClient With Account Number (" << SourceAccountNumber << ") Does Not Exist. ";
            cout << "\nPlease Enter Another Source Account Number  : ";
            SourceAccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient SourceClient = clsBankClient::FindClient(SourceAccountNumber);
        _PrintClientRecord(SourceClient);


        cout << "\n\nPlease Enter Destination Account Number : ";
        DestinationAccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(DestinationAccountNumber) || DestinationAccountNumber == SourceAccountNumber){
            if(DestinationAccountNumber == SourceAccountNumber){
                cout << "\nSource Account Number And Destination Account Number Cannot Be The Same! ";
            }
            else {
                cout << "\nClient With Account Number (" << DestinationAccountNumber << ") Does Not Exist. ";
            }

            cout << "\nPlease Enter Another Destination Account Number  : ";
            DestinationAccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient DestinationClient = clsBankClient::FindClient(DestinationAccountNumber);
        _PrintClientRecord(DestinationClient);

        double Amount = 0;
        cout << "\nPlease Enter The Transfer Amount : ";
        Amount = clsInputValidate::ReadDblNumber();

        while (Amount <= 0 || Amount > SourceClient.Balance()){
            if (Amount <= 0){
                cout << "\nAmount Must Be Greater Than Zero. Please Enter Another Amount : ";
            }
            else {
                cout << "\nAmount Exceeds The Available Balance. Please Enter Another Amount : ";
            }

            Amount = clsInputValidate::ReadDblNumber();
        }

        char Answer = 'n';
        cout << "\n\nAre You Sure Do You Want To Perform This Operation? y/n? ";
        cin >> Answer;

        if(toupper(Answer) == 'Y'){
            if(SourceClient.Transfer(DestinationClient, Amount,CurrentUser.UserName())){
                cout << "\nTransfer Done Successfully. ";
                _PrintClientRecord(SourceClient);
                _PrintClientRecord(DestinationClient);
            }
            else {
                cout << "\nTransfer Failed. ";
            }
        }
    }
};
