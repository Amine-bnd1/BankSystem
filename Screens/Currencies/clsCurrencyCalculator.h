#pragma once
#include <iostream>
#include <cctype>
#include "../../Core/clsCurrency.h"
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsCurrencyCalculator : protected clsScreen
{
private:
    static void _PrintCurrencyCard(clsCurrency &Currency)
    {
        cout << "\n____________________________";
        cout << "\nCountry   : " << Currency.Country();
        cout << "\nCode      : " << Currency.Code();
        cout << "\nName      : " << Currency.Name();
        cout << "\nRate(1$)  : " << Currency.Rate();
        cout << "\n____________________________";
    }

public:
    static void ShowCurrencyCalculatorScreen()
    {
        _DrawScreenHeader("Currency Calculator Screen");

        char Answer = 'n';
        
        do 
        {

            string Code1 = "";
            cout << "\nPlease Enter Currency1 Code : ";
            Code1 = clsInputValidate::ReadString();

            while (!clsCurrency::IsExist(Code1))
            {
                cout << "\nCurrency [" << Code1 << "] Not Found!";
                cout << "\nPlease Enter Another Currency1 Code : ";
                Code1 = clsInputValidate::ReadString();
            }

            clsCurrency CurrencyCode1 = clsCurrency::FindCurrencyByCode(Code1);

            string Code2 = "";
            cout << "\nPlease Enter Currency2 Code : ";
            Code2 = clsInputValidate::ReadString();

            while(!clsCurrency::IsExist(Code2))
            {
                cout << "\nCurrency [" << Code2 << "] Not Found!";
                cout << "\nPlease Enter Another Currency2 Code : ";
                Code2 = clsInputValidate::ReadString();
            }

            clsCurrency CurrencyCode2 = clsCurrency::FindCurrencyByCode(Code2);

            double Amount = 0;
            cout << "\nPlease Enter Amount To Exchange  : ";
            Amount = clsInputValidate::ReadDblNumber();

            cout << "\nConvert From : ";
            _PrintCurrencyCard(CurrencyCode1);
            cout << "\nTo : ";
            _PrintCurrencyCard(CurrencyCode2);

            cout << "\n\n"
                 << Amount << " " << Code1 << " = "
                 << clsCurrency::CurrencyCalculator(Amount, CurrencyCode1, CurrencyCode2)
                 << " " << Code2 << endl;

            cout << "\n\nDo You Want To Perform Another Calculation? y/n? ";
            cin >> Answer;
        } while (toupper(Answer) == 'Y');
    }
};