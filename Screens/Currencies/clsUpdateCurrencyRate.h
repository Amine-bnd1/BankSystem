#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "../../Core/clsCurrency.h"
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsUpdateCurrency : protected clsScreen
{
private:
    static void _PrintCurrencyCard(clsCurrency &Currency)
    {
        cout << "\nCurrency Card ";
        cout << "\n____________________________";
        cout << "\nCountry   : " << Currency.Country();
        cout << "\nCode      : " << Currency.Code();
        cout << "\nName      : " << Currency.Name();
        cout << "\nRate(1$)  : " << Currency.Rate();
        cout << "\n____________________________";
    }

public:
    static void ShowUpdateCurrencyScreen()
    {
        _DrawScreenHeader("Update Currency Screen");

        string Code = "";
        cout << "\nPlease Enter Currency Code : ";
        Code = clsInputValidate::ReadString();

        while (!clsCurrency::IsExist(Code))
        {
            cout << "\nCurrency With Code (" << Code << ") Does Not Exist. ";
            cout << "\nPlease Enter Another Code : ";
            Code = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindCurrencyByCode(Code);
        _PrintCurrencyCard(Currency);

        char Answer = 'n';
        cout << "\n\nAre You Sure Do You Want To Update The Rate Of This Currency? y/n? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            float NewRate = 0;
            cout << "\nUpdate Currency Rate: ";
            cout << "\n____________________________\n";

            cout << "\nPlease Enter New Rate : ";
            NewRate = clsInputValidate::ReadDblNumber();

            if(Currency.UpdateRate(NewRate)){
                cout << "\nCurrency Rate Updated Successfully. \n";
                _PrintCurrencyCard(Currency);
            }
            else
                cout << "\nUpdate Cancelled. ";
        }
    }
};