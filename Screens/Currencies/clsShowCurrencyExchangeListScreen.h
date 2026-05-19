#pragma once 
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>
#include <iomanip>
#include "../../Core/clsCurrency.h"
#include "../clsScreen.h"

using namespace std;


class clsShowCurrencyExchangeList : protected clsScreen {
private:
    static void _PrintCurrencyRecord(clsCurrency& Currency){
        cout << "| " << setw(25) << left << Currency.Country();
        cout << "| " << setw(10) << left << Currency.Code();
        cout << "| " << setw(25) << left << Currency.Name();
        cout << "| " << setw(15) << left << Currency.Rate() << "|\n";
    }

public:
    static void ShowCurrencyExchangeListScreen(){
        vector<clsCurrency> VstCurrency = clsCurrency::GetCurrencyList();

        string Title = "Currency List Screen";
        string Subtitle = "(" + to_string(VstCurrency.size()) + ") Currency. ";
        _DrawScreenHeader(Title, Subtitle);

        _PrintLine();
        cout << "| " << left << setw(25) << "Country";
        cout << "| " << left << setw(10) << "Code";
        cout << "| " << left << setw(25) << "Name";
        cout << "| " << left << setw(15) << "Rate/(1$)" << "|\n";
        _PrintLine();

        if(VstCurrency.empty()){
            cout << "\n\t\t\tNo Currency Available In The System. ";
        }
        else {
            for(clsCurrency& Currency: VstCurrency){
                _PrintCurrencyRecord(Currency);
                cout << endl;
            }
        }
        _PrintLine();
    }
};
