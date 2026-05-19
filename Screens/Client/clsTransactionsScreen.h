#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include "../../Core/clsBankClient.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include "clsShowDepositScreen.h"
#include "clsShowWithdrawScreen.h"
#include "clsShowTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsShowTransferLog.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenueScreen
    {
        eDeposit = 1,
        eWithdraw = 2,
        eShowTotalBalances = 3,
        eTransfer = 4,
        eTransferLog = 5,
        eShowMainMenue = 6
    };

    static short _ReadTransactionsMenuOptions()
    {
        short tchoice = 0;
        cout << "\n" <<  setw(37) << "" << left << "Please Enter what do you want to choose [1-6]? ";
        tchoice = clsInputValidate::ReadDblNumberBetween(1, 6, "Number is not within range, Enter again: ");
        return tchoice;
    }

    static void _ShowDepositScreen()
    {
        clsShowDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawtScreen()
    {
        clsShowWithdrawScreen::ShowWitdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsShowTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _ShowTransferScreen(){
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen(){
        clsTransferLog::ShowTransferLogScreen();
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress Enter to go back to Transactions Menue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    static bool _PerformTransactionsMenueOptions(enTransactionsMenueScreen TransactionsOptions)
    {
        switch (TransactionsOptions)
        {
        case enTransactionsMenueScreen::eDeposit:
            system("clear");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            return true;

        case enTransactionsMenueScreen::eWithdraw:
            system("clear");
            _ShowWithdrawtScreen();
            _GoBackToTransactionsMenue();
            return true;

        case enTransactionsMenueScreen::eShowTotalBalances:
            system("clear");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            return true;

        case enTransactionsMenueScreen::eTransfer:
            system("clear");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            return true;

        case enTransactionsMenueScreen::eTransferLog:
            system("clear");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            return true;

        case enTransactionsMenueScreen::eShowMainMenue:
            system("clear");
            return false;
        }

        return false;
    }

public:
    static void ShowTransationsMenue()
    {

        if (!CheckAccessRight(clsUsers::enPermissions::pTransactions))
        {
            return;
        }
        
        bool BackToTransactionsMenu = true;

        while (BackToTransactionsMenu)
        {
            system("clear");
            _DrawScreenHeader("\t   Transactions Screen");

            cout << setw(37) << left << "" << "====================================\n";
            cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
            cout << setw(37) << left << "" << "====================================\n";
            cout << setw(37) << left << "" << "\t[1] Deposit. \n";
            cout << setw(37) << left << "" << "\t[2] Withdraw. \n";
            cout << setw(37) << left << "" << "\t[3] Total Balances. \n";
            cout << setw(37) << left << "" << "\t[4] Transfer. \n";
            cout << setw(37) << left << "" << "\t[5] Transfer Log. \n";
            cout << setw(37) << left << "" << "\t[6] Main Menue. \n";
            cout << setw(37) << left << "" << "====================================\n";

            BackToTransactionsMenu =
                _PerformTransactionsMenueOptions((enTransactionsMenueScreen)_ReadTransactionsMenuOptions());
        }
    }
};