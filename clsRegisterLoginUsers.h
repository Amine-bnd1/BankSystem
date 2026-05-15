#pragma once 
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsUser.h"
#include "clsDate.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;


class clsRegisterLoginUsers : protected clsScreen{
private :
    static void _PrintUserRecord(clsUsers::stRegisterLoginUser& Record){
        cout << "| " << setw(30) << left << Record.DateTime;
        cout << "| " << setw(20) << left << Record.UserName;
        cout << "| " << setw(20) << left << Record.PassWord;
        cout << "| " << setw(20) << left << Record.Permissions << "|\n";
    }

public :
    static void ShowRegisterLoginUsers(){
        vector<clsUsers::stRegisterLoginUser> VstRecords = clsUsers::GetRegisterLoginUserList();

        string Title = "Login Register List Screen";
        string Subtitle = "(" + to_string(VstRecords.size()) + ") Record(s).";
        _DrawScreenHeader(Title, Subtitle);

        _PrintLine();
        cout << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "PassWord";
        cout << "| " << left << setw(20) << "Permissions" << "|\n";
        _PrintLine();

        if(VstRecords.empty()){
            cout << "\n\t\t\tNo Records Available In The System. ";
        }

        else {
            for(clsUsers::stRegisterLoginUser& Record : VstRecords){
                _PrintUserRecord(Record);
                cout << endl;
            }
        }
        _PrintLine();
    }
};