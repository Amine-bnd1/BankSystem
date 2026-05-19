#pragma once 
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../../Core/clsCurrency.h"
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsFindCurrency : protected clsScreen {
private:
    static void _PrintCurrencyCard(clsCurrency& Currency){
        cout << "\nCurrency Card ";
        cout << "\n____________________________";
        cout << "\nCountry   : " << Currency.Country();
        cout << "\nCode      : " << Currency.Code();
        cout << "\nName      : " << Currency.Name();
        cout << "\nRate(1$)  : " << Currency.Rate();
        cout << "\n____________________________";
    }

public: 
    static void ShowFindCurrencyScreen(){
        _DrawScreenHeader("Find Currency Screen");

        short choice = 0;

        cout << "\nFind By:\n";
        cout << "[1] Code Or [2] Country\n";
        cout << "\nYour Choice: ";
        choice = clsInputValidate::ReadIntNumberBetween(1, 2);

        if(choice == 1){
            string Code = "";
            cout << "\nPlease Enter Code? ";
            Code = clsInputValidate::ReadString();
            clsCurrency CountryCode = clsCurrency::FindCurrencyByCode(Code);

            if (CountryCode.IsEmpty()){
                cout << "\nCurrency With Code (" << Code << ") Not Found! ";
            }
            else {
                _PrintCurrencyCard(CountryCode);
            }
        }
        else {
            if (choice == 2)
            {
                string Country = "";
                cout << "\nPlease Enter Country Code? ";
                Country = clsInputValidate::ReadString();
                clsCurrency Currency = clsCurrency::FindCurrencyByCountry(Country);

                if(Currency.IsEmpty()){
                    cout << "\nCurrency With Country Code (" << Country << ") Not Found! ";
                }
                else {
                    _PrintCurrencyCard(Currency);
                }
            }
        }

        
    }
};