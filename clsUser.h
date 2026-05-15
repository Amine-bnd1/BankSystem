#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsUtil.h"
#include "clsDate.h"

using namespace std;

class clsUsers : public clsPerson
{
public:
    struct stRegisterLoginUser
    {
        string DateTime;
        string UserName;
        string PassWord;
        int Permissions = 0;
    };

private:
    enum enMode
    {
        EmptyMode = 1,
        AddMode = 2,
        UpdateMode = 3
    };

    enMode _Mode;
    string _UserName;
    string _PassWord;
    int _Permissions;
    bool _MarkForDelete = false;

    static clsUsers _ConvertDataLineToUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> VstUsers = clsString::SplitString(Line, Seperator);

        return clsUsers(
            UpdateMode,
            VstUsers[0],
            VstUsers[1],
            VstUsers[2],
            VstUsers[3],
            VstUsers[4],
            clsUtil::DecryptText(VstUsers[5]),
            stoi(VstUsers[6]));
    }

    static string _ConvertUserObjectToDataLine(clsUsers User, string Seperator = "#//#")
    {
        string Record = "";

        Record += User.FirstName() + Seperator;
        Record += User.LastName() + Seperator;
        Record += User.Email() + Seperator;
        Record += User.Phone() + Seperator;
        Record += User.UserName() + Seperator;
        Record += clsUtil::EncryptText(User.PassWord(), 2) + Seperator;
        Record += to_string(User.Permissions());

        return Record;
    }

    static stRegisterLoginUser _ConvertRegisterLoginDataLineToObject(string Line, string Seperator = "#//#")
    {
        stRegisterLoginUser Record;

        vector<string> VstData = clsString::SplitString(Line, Seperator);

        Record.DateTime = VstData[0];
        Record.UserName = VstData[1];
        Record.PassWord = clsUtil::DecryptText(VstData[2], 2);
        Record.Permissions = stoi(VstData[3]);

        return Record;
    }

    string _PrepareRegisterLoginUser(string Seperator = "#//#")
    {
        string Record = "";

        Record += clsDate::GetSystemDateTimeString() + Seperator;
        Record += _UserName + Seperator;
        Record += clsUtil::EncryptText(_PassWord, 2) + Seperator;
        Record += to_string(_Permissions);

        return Record;
    }

    void _RegisterLoginUserToFile()
    {
        fstream MyFile;
        MyFile.open("RegisterLoginUsers.Txt", ios::out | ios::app);

        string stDataLine = _PrepareRegisterLoginUser();

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    static vector<clsUsers> _LoadUsersDataFromFile()
    {
        vector<clsUsers> VstUsers;

        fstream MyFile;
        MyFile.open("Users.Txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsUsers User = _ConvertDataLineToUserObject(Line);
                VstUsers.push_back(User);
            }
            MyFile.close();
        }
        return VstUsers;
    }

    static void _SaveUserDataToFile(vector<clsUsers> VstUsers)
    {
        fstream MyFile;
        MyFile.open("Users.Txt", ios::out);
        string Line;

        if (MyFile.is_open())
        {
            for (clsUsers &User : VstUsers)
            {
                if (User._MarkForDelete == false)
                {
                    Line = _ConvertUserObjectToDataLine(User);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }

    static clsUsers _GetEmptyObject()
    {
        return clsUsers(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.Txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    void _AddNewUser()
    {
        _AddDataLineToFile(_ConvertUserObjectToDataLine(*this));
    }

    void _Update()
    {
        vector<clsUsers> VstUsers = clsUsers::_LoadUsersDataFromFile();

        for (clsUsers &User : VstUsers)
        {
            if (User.UserName() == _UserName)
            {
                User = *this;
                break;
            }
        }
        _SaveUserDataToFile(VstUsers);
    }

public:
    enum enPermissions
    {
        pAll = -1,
        pListClient = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClient = 8,
        pFindClient = 16,
        pTransactions = 32,
        pManageUsers = 64,
        pLoginRegister = 128
    };

    clsUsers(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string PassWord, int Permissions)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _PassWord = PassWord;
        _Permissions = Permissions;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    string UserName()
    {
        return _UserName;
    }

    void SetPassWord(string PassWord)
    {
        _PassWord = PassWord;
    }

    string PassWord()
    {
        return _PassWord;
    }

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int Permissions()
    {
        return _Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static clsUsers FindUser(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.Txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsUsers User = _ConvertDataLineToUserObject(Line);
                if (User.UserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObject();
    }

    static bool IsUserExist(string UserName)
    {
        return !FindUser(UserName).IsEmpty();
    }

    static clsUsers FindUserByUserNameAndPassWord(string UserName, string PassWord)
    {
        fstream MyFile;
        MyFile.open("Users.Txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsUsers User = _ConvertDataLineToUserObject(Line);
                if (User.UserName() == UserName && User.PassWord() == PassWord)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObject();
    }

    enum enSaveResults
    {
        svSucceed = 1,
        svFailedEmptyObject = 2,
        svFailedUserNameExist = 3
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResults::svFailedEmptyObject;

        case enMode::AddMode:
            if (clsUsers::IsUserExist(_UserName))
                return enSaveResults::svFailedUserNameExist;

            _AddNewUser();
            _Mode = enMode::UpdateMode;
            return enSaveResults::svSucceed;

        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceed;
        }
        return enSaveResults::svFailedEmptyObject;
    }

    bool Delete()
    {
        vector<clsUsers> VstUsers = _LoadUsersDataFromFile();
        bool IsDeleted = false;

        for (clsUsers &User : VstUsers)
        {
            if (User.UserName() == _UserName)
            {
                User._MarkForDelete = true;
                IsDeleted = true;
                break;
            }
        }
        if (IsDeleted)
        {
            _SaveUserDataToFile(VstUsers);
            *this = _GetEmptyObject();
        }
        return IsDeleted;
    }

    static vector<clsUsers> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    static clsUsers GetAddNewUserObject(string UserName)
    {
        return clsUsers(enMode::AddMode, "", "", "", "", UserName, "", 0);
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (_Permissions == enPermissions::pAll)
            return true;

        return ((Permission & _Permissions) == Permission);
    }

    void RegisterLoginUser()
    {
        _RegisterLoginUserToFile();
    }

    static vector<stRegisterLoginUser> GetRegisterLoginUserList()
    {
        vector<stRegisterLoginUser> VstRecords;

        fstream MyFile;
        MyFile.open("RegisterLoginUsers.Txt", ios::in);

        string Line;
        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                VstRecords.push_back(_ConvertRegisterLoginDataLineToObject(Line));
            }
            MyFile.close();
        }
        return VstRecords;
    }

   
};