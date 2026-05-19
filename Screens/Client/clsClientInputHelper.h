#pragma once
#include <iostream>
#include <string>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsClientInputHelper
{
public:
    static void ReadClientInfo(clsBankClient &Client)
    {

        cout << "\nPlease Enter First Name : ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nPlease Enter Last Name : ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nPlease Enter Email : ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nPlease Enter Phone : ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nPlease Enter PinCode : ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nPlease Enter Balance: ";
        Client.SetBalance(clsInputValidate::ReadDblNumber());
    }
};
