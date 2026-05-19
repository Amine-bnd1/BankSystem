#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../Lib/clsInputValidate.h"
#include "../Lib/clsDate.h"
#include "../Lib/clsString.h"

using namespace std;

class clsCurrency
{
private:
    enum enMode
    {
        EmptyMode = 1,
        UpdateMode = 2
    };

    enMode _Mode;
    string _Country;
    string _Code;
    string _Name;
    float _Rate = 0;
    bool _MarkForDelete = false;

    static clsCurrency _ConvertCurrencyDataLineToObject(string Line, string Seperator = "#//#")
    {
        vector<string> VstData = clsString::SplitString(Line, Seperator);

        return clsCurrency(
            enMode::UpdateMode,
            VstData[0],
            VstData[1],
            VstData[2],
            stof(VstData[3]));
    }

    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator)
    {
        string Record = "";

        Record += Currency.Country() + Seperator;
        Record += Currency.Code() + Seperator;
        Record += Currency.Name() + Seperator;
        Record += to_string(Currency.Rate());

        return Record;
    }

    static vector<clsCurrency> _LaodCurrencyFromFile()
    {
        vector<clsCurrency> VstCurrency;

        fstream MyFile;
        MyFile.open("Currencies.Txt", ios::in);

        string Line;
        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                VstCurrency.push_back(_ConvertCurrencyDataLineToObject(Line));
            }
            MyFile.close();
        }
        return VstCurrency;
    }

    static void _SaveCurrencyToFile(vector<clsCurrency> VstCurrency)
    {
        fstream MyFile;
        MyFile.open("Currencies.Txt", ios::out);

        if (MyFile.is_open())
        {
            for (clsCurrency &Currency : VstCurrency)
            {
                if (!Currency._MarkForDelete)
                {
                    MyFile << _ConvertCurrencyObjectToLine(Currency, "#//#") << endl;
                }
            }
            MyFile.close();
        }
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:
    clsCurrency(enMode Mode, string Country, string Code, string Name, float Rate)
    {
        _Country = Country;
        _Code = Code;
        _Name = Name;
        _Rate = Rate;
        _Mode = Mode;
    }

    void SetCountry(string Country)
    {
        _Country = Country;
    }

    string Country()
    {
        return _Country;
    }

    void SetCode(string Code)
    {
        _Code = Code;
    }

    void SetName(string Name)
    {
        _Name = Name;
    }

    string Name()
    {
        return _Name;
    }

    string Code()
    {
        return _Code;
    }

    void SetRate(float Rate)
    {
        _Rate = Rate;
    }

    float Rate()
    {
        return _Rate;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static clsCurrency FindCurrencyByCode(string Code)
    {
        vector<clsCurrency> VstCurrency = _LaodCurrencyFromFile();

        for (clsCurrency &Currency : VstCurrency)
        {
            if (Currency.Code() == Code)
            {
                return Currency;
            }
        }
        return _GetEmptyCurrencyObject();
    }

    static bool IsExist(string Code){
        return !FindCurrencyByCode(Code).IsEmpty();
    }

    static clsCurrency FindCurrencyByCountry(string Country){
        vector<clsCurrency> VstCurrency = _LaodCurrencyFromFile();

        for(clsCurrency& Currency : VstCurrency)
            if(Currency.Country() == Country){
                return Currency;
            }
        return _GetEmptyCurrencyObject();
    }

    static vector<clsCurrency> GetCurrencyList(){
        return _LaodCurrencyFromFile();
    }

    void Save(){
        vector<clsCurrency> VstCurrency = _LaodCurrencyFromFile();

        for(clsCurrency& Currency: VstCurrency){
            if(Currency.Code() == _Code){
                Currency = *this;
                break;
            }
        }
        _SaveCurrencyToFile(VstCurrency);
    }

    bool UpdateRate(float NewRate){
        _Rate = NewRate;
        Save();
        return true;
    }

    static float CurrencyCalculator(float Amount, clsCurrency From, clsCurrency To){
        if(From.Rate() == 0){
            return 0;
        }
        return (Amount / From.Rate()) * To.Rate();
    }
};