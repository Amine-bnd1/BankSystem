#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsShowTotalBalancesScreen : protected clsScreen
{
private:
    static constexpr int _AccWidth = 18;
    static constexpr int _NameWidth = 32;
    static constexpr int _BalWidth = 18;

    static string _FitText(const string& Text, size_t Width)
    {
        if (Text.length() <= Width)
            return Text;

        if (Width <= 3)
            return Text.substr(0, Width);

        return Text.substr(0, Width - 3) + "...";
    }

    static string _FormatMoney(double Value)
    {
        ostringstream Out;
        Out << fixed << setprecision(2) << Value;
        return Out.str();
    }

    static void _PrintSeparator()
    {
        cout << "+"
             << string(_AccWidth + 2, '-')
             << "+"
             << string(_NameWidth + 2, '-')
             << "+"
             << string(_BalWidth + 2, '-')
             << "+\n";
    }

    static void _PrintHeaderRow()
    {
        cout << "| " << left  << setw(_AccWidth) << "Account Number"
             << "| " << left  << setw(_NameWidth) << "Client Name"
             << "| " << right << setw(_BalWidth) << "Balance"
             << " |\n";
    }

    static void _PrintClientRecord(clsBankClient& Client)
    {
        string Name = _FitText(Client.FullName(), _NameWidth);
        string BalanceText = _FormatMoney(Client.Balance());

        cout << "| " << left  << setw(_AccWidth) << Client.AccountNumber()
             << "| " << left  << setw(_NameWidth) << Name
             << "| " << right << setw(_BalWidth) << BalanceText
             << " |\n";
    }

    static void _PrintFooterTotal(double TotalBalances)
    {
        string TotalText = _FormatMoney(TotalBalances);

        cout << "| " << left  << setw(_AccWidth) << ""
             << "| " << left  << setw(_NameWidth) << "TOTAL BALANCES"
             << "| " << right << setw(_BalWidth) << TotalText
             << " |\n";
    }

public:
    static void ShowTotalBalancesScreen()
    {
        vector<clsBankClient> VstClients = clsBankClient::GetClientsList();
        double TotalBalances = clsBankClient::GetTotalBalances();

        string SubTitle = "(" + to_string(VstClients.size()) + ") Client(s)";
        _DrawScreenHeader("Total Balances", SubTitle);

        _PrintSeparator();
        _PrintHeaderRow();
        _PrintSeparator();

        if (VstClients.empty())
        {
            cout << "| " << left
                 << setw(_AccWidth + _NameWidth + _BalWidth + 6)
                 << "No clients available in the system."
                 << " |\n";
        }
        else
        {
            for (clsBankClient& Client : VstClients)
            {
                _PrintClientRecord(Client);
            }
        }

        _PrintSeparator();
        _PrintFooterTotal(TotalBalances);
        _PrintSeparator();
    }
};