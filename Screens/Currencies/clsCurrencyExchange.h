#pragma once
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <limits>
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "clsShowCurrencyExchangeListScreen.h"
#include "clsFindCurrency.h"
#include "clsUpdateCurrencyRate.h"
#include "clsCurrencyCalculator.h"

using namespace std;

class clsCurrencyExchange : protected clsScreen
{
private:
    enum enCurrencyExchange
    {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateRate = 3,
        eCurrencyCalculator = 4,
        eMainMenu = 5
    };

    static short _ReadCurrencyExchangeMenuOptions()
    {
        short choice = 0;
        do {

        cout << setw(37) << left << "" << "Choose What Do You Want To Do? [1 To 5]? ";
        choice = clsInputValidate::ReadIntNumber();
    
        } while (choice < 1 || choice > 5);
        return choice;
    }

    static void _GoBackToMainCurrencyExchange()
    {
        cout << "\n\nPress Enter to go back to Currency Exchange Menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    static void _ShowListCurrenciesScreen()
    {
        clsShowCurrencyExchangeList::ShowCurrencyExchangeListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrency::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrency::ShowUpdateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculator::ShowCurrencyCalculatorScreen();
    }

    static bool _PerformCurrencyExchangeMenuOptions(enCurrencyExchange Choice)
    {
        switch (Choice)
        {
        case enCurrencyExchange::eListCurrencies:
            system("clear");
            _ShowListCurrenciesScreen();
            _GoBackToMainCurrencyExchange();
            return true;

        case enCurrencyExchange::eFindCurrency:
            system("clear");
            _ShowFindCurrencyScreen();
            _GoBackToMainCurrencyExchange();
            return true;

        case enCurrencyExchange::eUpdateRate:
            system("clear");
            _ShowUpdateRateScreen();
            _GoBackToMainCurrencyExchange();
            return true;

        case enCurrencyExchange::eCurrencyCalculator:
            system("clear");
            _ShowCurrencyCalculatorScreen();
            _GoBackToMainCurrencyExchange();
            return true;

        case enCurrencyExchange::eMainMenu:
            system("clear");
            return false;
        }
        return false;
    }

public:
    static void ShowCurrencyExchangeMenu()
    {
        if (!CheckAccessRight(clsUsers::pCurrencyExchange))
        {
            return;
        }

        bool BackToCurrencyExchangeMenu = true;

        while (BackToCurrencyExchangeMenu)
        {
            system("clear");
            _DrawScreenHeader("Currency Exchange Main Screen");

            cout << setw(37) << left << "" << "===================================\n";
            cout << setw(37) << left << "" << "\t\tCurrency Exchange Menu\n";
            cout << setw(37) << left << "" << "===================================\n";
            cout << setw(37) << left << "" << "\t[1] List Currencies. \n";
            cout << setw(37) << left << "" << "\t[2] Find Currency. \n";
            cout << setw(37) << left << "" << "\t[3] Update Rate. \n";
            cout << setw(37) << left << "" << "\t[4] Currency Calculator. \n";
            cout << setw(37) << left << "" << "\t[5] Main Menu. \n";
            cout << setw(37) << left << "" << "===================================\n";

            BackToCurrencyExchangeMenu =
                _PerformCurrencyExchangeMenuOptions(enCurrencyExchange(_ReadCurrencyExchangeMenuOptions()));
        }
    }
};
