#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsInputValidate.h"
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include "clsDate.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsBankClient : public clsPerson
{
public :
    struct stTransferLog {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount = 0;
        double SourceBalance = 0;
        double DestinationBalance = 0;
        string UserName;
    };

private:
    enum enMode
    {
        enEmpty = 0,
        enUpdate = 1,
        enAddClient = 2
    };

    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _Balance;
    bool MarkForDelete = false;

    static clsBankClient _ConvertDataLineToObject(string Line, string Seperator = "#//#")
    {
        vector<string> VstClients = clsString::SplitString(Line, Seperator);

        return clsBankClient(
            enMode::enUpdate,
            VstClients[0],
            VstClients[1],
            VstClients[2],
            VstClients[3],
            VstClients[4],
            VstClients[5],
            stof(VstClients[6]));
    }

    
    static clsBankClient _GetEmptyObject()
    {
        return clsBankClient(enMode::enEmpty, "", "", "", "", "", "", 0);
    }

    static string _ConvertDataObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {
        string Record = "";

        Record += Client.FirstName() + Seperator;
        Record += Client.LastName() + Seperator;
        Record += Client.Email() + Seperator;
        Record += Client.Phone() + Seperator;
        Record += Client.AccountNumber() + Seperator;
        Record += Client.PinCode() + Seperator;
        Record += to_string(Client.Balance());

        return Record;
    }

    string _PrepareTransferLogRecord(clsBankClient& DestinationClient, double Amount, string UserName, string Seperator = "#//#"){
        string Record = "";

        Record += clsDate::GetSystemDateTimeString() + Seperator;
        Record += AccountNumber() + Seperator;
        Record += DestinationClient.AccountNumber() + Seperator;
        Record += to_string(Amount) + Seperator;
        Record += to_string(Balance()) + Seperator;
        Record += to_string(DestinationClient.Balance()) + Seperator;
        Record += UserName;

        return Record;
    }

    void _RegisterTransferLog(clsBankClient& DestinationClient, double Amount, string UserName){
        fstream MyFile;
        MyFile.open("TransferLog.Txt", ios::out | ios::app);

        string stDataLine = _PrepareTransferLogRecord(DestinationClient, Amount, UserName);

        if(MyFile.is_open()){
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    static stTransferLog _ConvertTransferLogDataLineToObject(string Line, string Seperator = "#//#"){
        stTransferLog TransferLog;

        vector<string> VstData = clsString::SplitString(Line, Seperator);

        TransferLog.DateTime = VstData[0];
        TransferLog.SourceAccountNumber = VstData[1];
        TransferLog.DestinationAccountNumber = VstData[2];
        TransferLog.Amount = stod(VstData[3]);
        TransferLog.SourceBalance = stod(VstData[4]);
        TransferLog.DestinationBalance = stod(VstData[5]);
        TransferLog.UserName = VstData[6];

        return TransferLog;
    }

        static vector<clsBankClient> _LoadClientDataFromFile(string FileName = "Clients.Txt")
    {
        vector<clsBankClient> VstClients;

        fstream MyFile;
        MyFile.open(FileName, ios ::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertDataLineToObject(Line);
                VstClients.push_back(Client);
            }
            MyFile.close();
        }
        return VstClients;
    }

    static void _SaveClientDataToFile(vector<clsBankClient> VstClients, string FileName = "Clients.Txt")
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out);

        if (MyFile.is_open())
        {
            for (clsBankClient C : VstClients)
            {
                if (C.MarkForDelete == false)
                {

                    MyFile << _ConvertDataObjectToLine(C) << endl;
                }
            }
            MyFile.close();
        }
    }

    static void _AddDataLineToFile(string stDataLine){
        fstream MyFile;

        MyFile.open("Clients.Txt", ios::out | ios::app);

        if(MyFile.is_open()){
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    void _Update(){
        vector<clsBankClient> VstClients = _LoadClientDataFromFile();

        for(clsBankClient& C : VstClients){
            if(C.AccountNumber() == AccountNumber()){
                C = *this;
                break;
            }
        }
        _SaveClientDataToFile(VstClients);
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertDataObjectToLine(*this));
        _Mode = enMode::enUpdate;
    }

public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float Balance)
        : clsPerson(FirstName, LastName, Email, Phone)
    {

        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _Balance = Balance;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string PinCode()
    {
        return _PinCode;
    }

    void SetBalance(float Balance)
    {
        _Balance = Balance;
    }

    float Balance()
    {
        return _Balance;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::enEmpty);
    }

    static clsBankClient GetNewClientObject(string AccountNumber){
        return clsBankClient(enMode::enAddClient, "", "", "", "", AccountNumber, "", 0);
    }


    static clsBankClient FindClient(string AccountNumber){
        fstream MyFile;
        MyFile.open("Clients.Txt", ios::in);

        if(MyFile.is_open()){
            string Line;
            while(getline(MyFile, Line)){
                clsBankClient Client = _ConvertDataLineToObject(Line);
                if(Client.AccountNumber() == AccountNumber){
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObject();
    }

    static clsBankClient FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.Txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertDataLineToObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode() == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObject();
    }

    static bool IsClientExist(string AccountNumber){
        return !FindClient(AccountNumber).IsEmpty();
    }

    enum enSaveResults
    {
        svSucceeded = 0,
        svFaildEmptyObject = 1,
        svFaildAccountNumberExist = 2
    };

    enSaveResults Save(){
        switch (_Mode)
        {
        case enMode::enEmpty:
            return enSaveResults::svFaildEmptyObject;
            

        case enMode::enUpdate:
            _Update();
            return enSaveResults::svSucceeded;
           

        case enMode::enAddClient:
            if(clsBankClient::IsClientExist(_AccountNumber)){
                return enSaveResults::svFaildAccountNumberExist;
            }
            else {
                _AddNew();
                return enSaveResults::svSucceeded;
            }
        }
        return enSaveResults::svFaildEmptyObject;
    }

    static vector <clsBankClient> GetClientsList(){
        return _LoadClientDataFromFile();
    }

    bool DeleteClient(){
        vector<clsBankClient> VstClients = _LoadClientDataFromFile();

        for(clsBankClient& C : VstClients){
            
                if(C.AccountNumber() == _AccountNumber){
                    C.MarkForDelete = true;
                    break;
                }
        }
        _SaveClientDataToFile(VstClients);
        *this = _GetEmptyObject();

        return true;
    }

    void Deposit(double Amount){
        _Balance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _Balance)
            return false;

        _Balance -= Amount;
        Save();

        return true;
    }

    static double GetTotalBalances(){
        vector<clsBankClient> VstClient = _LoadClientDataFromFile();
        double TotalBalances = 0;

        for(clsBankClient Client: VstClient){
            TotalBalances += Client.Balance();
        }
        return TotalBalances;
    }

    bool Transfer(clsBankClient& DestinationClient, double Amount, string UserName){
        if(Amount <= 0 || Amount > _Balance){
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(DestinationClient, Amount, UserName);

        return true;
    }

    static vector<stTransferLog> GetTransferLogList(){
        vector<stTransferLog> VstData;

        fstream MyFile;
        MyFile.open("TransferLog.Txt", ios::in);

        string Line;

        if(MyFile.is_open()){
            while(getline(MyFile, Line)){
                VstData.push_back(_ConvertTransferLogDataLineToObject(Line));
            }
            MyFile.close();
        }
        return VstData;
    }
};