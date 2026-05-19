#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"

using namespace std;

class clsClientUIHelper
{

public:
    static void PrintClientCard(clsBankClient &Client)
    {

        cout << "\nClient Card";
        cout << "\n------------------------------------";
        cout << "\nFirst Name       : " << Client.FirstName();
        cout << "\nLast Name        : " << Client.LastName();
        cout << "\nFull Name        : " << Client.FullName();
        cout << "\nEmail            : " << Client.Email();
        cout << "\nPhone            : " << Client.Phone();
        cout << "\nAccount Number   : " << Client.AccountNumber();
        cout << "\nPinCode          : " << Client.PinCode();
        cout << "\nBalance          : " << Client.Balance();
        cout << "\n------------------------------------";
    }
};
