#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsDate.h"
#include <limits>

using namespace std;

class clsInputValidate{

public :



    static bool IsNumberBetween(short choice, short Min, short Max){
        if(choice >= Min && choice <= Max){
            return true;
        }
        return false;
    }

    static bool IsNumberBetween(int choice, int Min, int Max){
        if(choice >= Min && choice <= Max){
            return true;
        }
        return false;
    }

    static bool IsNumberBetween(float choice, float Min, float Max){
        if(choice >= Min && choice <= Max){
            return true;
        }
        return false;
    }

    static bool IsNumberBetween(double choice, double Min, double Max){
        if(choice >= Min && choice <= Max){
            return true;
        }
        return false;
    }

    static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo){
        if((clsDate::IsDate1AfterDate2(Date,DateFrom) || clsDate::IsDate1EqualDate2(Date,DateFrom))
          &&
          (clsDate::IsDate1BeforeDate2(Date,DateTo) || clsDate::IsDate1EqualDate2(Date,DateTo)))
          {
              return true;
          }

       if((clsDate::IsDate1AfterDate2(Date,DateTo) || clsDate::IsDate1EqualDate2(Date,DateTo))
          &&
          (clsDate::IsDate1BeforeDate2(Date,DateFrom) || clsDate::IsDate1EqualDate2(Date,DateFrom)))
          {
              return true;
          }
        return false;
    }

    static string ReadString(){
        string Value = "";
        getline(cin >> ws, Value);
        return Value;
    }

    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again : "){
        int Number = 0;
       
        while(!(cin >> Number)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return Number;
    }

    static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {

        int Number = ReadIntNumber();

        while(!(IsNumberBetween(Number,From, To))){
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }
        return Number;
    }

    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again :"){
        double Number = 0;

        while(!(cin >> Number)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static double ReadDblNumberBetween(double From , double To, string ErrorMessage = "Number is not within range, Enter again:\n"){
        double Number = ReadDblNumber();

        while(!(IsNumberBetween(Number,From,To))){
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }

    static bool IsValideDate(clsDate Date){
        return clsDate::IsValidDate(Date);
    }

    
};