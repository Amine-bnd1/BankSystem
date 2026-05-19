#pragma once 
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "../../Core/clsBankClient.h"
#include "../clsScreen.h"
#include "../../Lib/clsDate.h"

using namespace std;


class clsTransferLog : protected clsScreen {
private:
    static void _PrintClientRecord(clsBankClient::stTransferLog& Record){
        cout << "| " << setw(25) << left << Record.DateTime;
        cout << "| " << setw(10) << left << Record.SourceAccountNumber;
        cout << "| " << setw(10) << left << Record.DestinationAccountNumber;
        cout << "| " << setw(10) << left << Record.Amount;
        cout << "| " << setw(15) << left << Record.SourceBalance;
        cout << "| " << setw(15) << left << Record.DestinationBalance;
        cout << "| " << setw(10) << left << Record.UserName << "|\n";
    }

public :
    static void ShowTransferLogScreen(){
        vector<clsBankClient::stTransferLog> VstRecords = clsBankClient::GetTransferLogList();

        string Title = "Transfer Log Screen";
        string Subtitle = "(" + to_string(VstRecords.size()) + ") Record(s). ";
        _DrawScreenHeader(Title, Subtitle);

        _PrintLine();
        cout << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acc";
        cout << "| " << left << setw(10) << "d.Acc";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(15) << "s.Balance";
        cout << "| " << left << setw(15) << "d.Balance";
        cout << "| " << left << setw(10) << "User" << "|\n";
        _PrintLine();

        if(VstRecords.empty()){
            cout << "\n\t\t\tNo Transfer Log Records Available In The System. ";
        }
        else {
            for(clsBankClient::stTransferLog& Record : VstRecords){
                _PrintClientRecord(Record);
                cout << endl;
            }
        }
        _PrintLine();
    }
};
