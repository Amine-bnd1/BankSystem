#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
    static bool _Login()
    {

        string UserName, PassWord;
        bool LoginFailed = false;
        short Trials = 0;

        do
        {
            system("clear");
            _DrawScreenHeader("Login Screen");

            if (LoginFailed)
            {
                Trials++;
                
                if (Trials == 3)
                {
                    cout << "\nInvalid UserName/PassWord! \n";
                    cout << "\nYou Are Locked After 3 Failed Trails. \n";
                    return false;
                }
                cout << "\nInvalid UserName/PassWord! \n";
                cout << "\nYou Have " << (3 - Trials) << " Trial(s) Left To Login. \n";
            }

            cout << "\nPlease Enter UserName  : ";
            UserName = clsInputValidate::ReadString();

            cout << "\nPlease Enter PassWord  : ";
            PassWord = clsInputValidate::ReadString();

            CurrentUser = clsUsers::FindUserByUserNameAndPassWord(UserName, PassWord);
            LoginFailed = CurrentUser.IsEmpty();
        } while (LoginFailed);

        CurrentUser.RegisterLoginUser();
        clsMainScreen::_ShowMainMenue();
        return true;
    }

public :
    static bool ShowLoginScreen(){
        return _Login();
    }
};