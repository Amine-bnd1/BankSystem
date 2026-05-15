#pragma once
#include <iostream>
#include <cctype>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientUIHelper.h"

using namespace std;

class clsShowWithdrawScreen : protected clsScreen
{

private:
    static void _PrintClientCard(clsBankClient &Client)
    {
        clsClientUIHelper::PrintClientCard(Client);
    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public:
    static void ShowWitdrawScreen()
    {

        _DrawScreenHeader("Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient With Account Number (" << AccountNumber << ") does not exist. ";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::FindClient(AccountNumber);
        _PrintClientCard(Client);

        double Amount = 0;
        cout << "\nPlease Enter Withraw Amount : ";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = 'n';
        cout << "\n\nAre You Sure Do You Want To Perform This Transaction? [Y/N]? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nTransaction Done Successfully. ";
                cout << "\nNew Balance is : " << Client.Balance();
            }
            else
            {
                cout << "\nYou Cannot Withdraw : Insufficient Balance! ";
                cout << fixed << setprecision(0);
                cout << "\nAmount To Withdraw is : " << Amount;
                cout << "\nYou Balance is : " << Client.Balance();
            }
        }
        else {
            cout << "\nTransaction Cancelled. ";
        }
    }
};