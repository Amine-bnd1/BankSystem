#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class clsUtil{
    public :

    enum enChars
    {
        CapitalLetter = 1, SmallLetter = 2, Digit = 3, SpecialCharacter = 4, MixChars = 5
    };


    static int RandomNumber(int From, int To)
    {
        int RandNum = rand() % (To - From + 1) + From;
        return RandNum;
    }

    static char GetRandomCharacter(enChars Chars){
        switch (Chars)
        {
        case enChars::CapitalLetter:
            return char(RandomNumber(65, 90));
            break;
        
        
        case enChars::SmallLetter:
            return char(RandomNumber(97, 122));
            break;
        case enChars::Digit:
            return char(RandomNumber(48, 57));
            break;
        
        case enChars::SpecialCharacter:
            return char(RandomNumber(33, 47));
            break;

        case enChars::MixChars:
            return char(RandomNumber(33, 122));
            break;
        default:
            return '?';
        }
    }

    static string GenerateWord(enChars Chars, int WordLength){
        string Results = "";
        for (int i = 0; i < WordLength; i++){
            Results += GetRandomCharacter(Chars);
        }
        return Results;
    }

    static string GenerateKey(enChars Chars){
        string Results = "";
        for (int i = 0; i < 4; i++){
            Results += GenerateWord(Chars, 4);
            if(i < 3){
                Results += "-";
            }
        }

        return Results;
    }

    static string GenerateKeys(enChars Chars, int KeyLength){
        string Word = "";
        for (int i = 0; i < KeyLength; i++){
            Word += "Key [ " + to_string(i + 1) + "] : ";
            Word += GenerateKey(Chars);
            if( i < KeyLength - 1){
                Word += "\n";
            }
        }
        return Word;
    }

    static void FillArrayWithRandomNumbers(int arr[], int arrLength, int From, int To){
        for (int i = 0; i < arrLength; i++){
            arr[i] = RandomNumber(From, To);
        }
    }

    static void PrintNumbers(int arr[], int arrLength){
        for (int i = 0; i < arrLength; i++){
            cout << "Key [" << i << "] : " << arr[i] << endl;

        }
        cout << endl;
    }

    static void FillArrayWithRandomWords(string arr[], int arrLength, int WordLength, enChars Chars){
        for (int i = 0; i < arrLength; i++){
            arr[i] = GenerateWord(Chars, WordLength);
        }
    }

    static void PrintWords(string arr[], int arrLength){
        for (int i = 0; i < arrLength; i++){
            cout << "Key [" << i << "] : " << arr[i] << endl;
        }
        cout << endl;
    }

    static void FillArrayWithRandomKeys(string arr[], int arrLength, int KeyLength, enChars Chars){
        for (int i = 0; i < arrLength; i++){
            arr[i] = GenerateKey(Chars);
        }
    }

    static void PrintKeys(string arr[], int arrLength, int KeyLength){
        for (int i = 0; i < arrLength; i++){
            cout << "Key [" << i << "] : " << arr[i] << endl;
        }
        cout << endl;
    }

    static void Swap(int &a, int &b){
        int Temp = a;
        a = b;
        b = Temp;
    }

    static void ShuffleArray(int arr[], int arrLength){
        for (int i = arrLength - 1; i > 0; i--){
            int j = RandomNumber(0, i);
            Swap(arr[i], arr[j]);
        }
    }

    static void ShufflestringArray(string arr[], int arrLength){
         for (int i = arrLength - 1; i > 0; i--){
            int j = RandomNumber(0, i);
            string Temp = arr[i];
            arr[i] = arr[j];
            arr[j] = Temp;
         }
    }

    static string EncryptText(string Text, int EncryptionKey = 2){
        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text;
    }

    static string DecryptText(string Text, int DecryptionKey = 2){
        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - DecryptionKey);
        }
        return Text;
    }

    static string NumberToText(int Number)
    {
        if (Number == 0)
            return "Zero";

        return _NumberToText((long long)Number);
    }

private:
    static string _NumberToText(long long Number)
    {
        if (Number == 0)
            return "";

        if (Number < 0)
            return "Minus " + _NumberToText(-Number);

        string Arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                         "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
                         "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

        string Tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty",
                          "Sixty", "Seventy", "Eighty", "Ninety" };

        if (Number < 20)
            return Arr[Number];

        if (Number < 100)
            return Tens[Number / 10] + (Number % 10 != 0 ? " " + _NumberToText(Number % 10) : "");

        if (Number < 200)
            return "One Hundred" + (Number % 100 != 0 ? " " + _NumberToText(Number % 100) : "");

        if (Number < 1000)
            return _NumberToText(Number / 100) + " Hundreds" + (Number % 100 != 0 ? " " + _NumberToText(Number % 100) : "");

        if (Number < 2000)
            return "One Thousand" + (Number % 1000 != 0 ? " " + _NumberToText(Number % 1000) : "");

        if (Number < 1000000)
            return _NumberToText(Number / 1000) + " Thousands" + (Number % 1000 != 0 ? " " + _NumberToText(Number % 1000) : "");

        if (Number < 2000000)
            return "One Million" + (Number % 1000000 != 0 ? " " + _NumberToText(Number % 1000000) : "");

        if (Number < 1000000000)
            return _NumberToText(Number / 1000000) + " Millions" + (Number % 1000000 != 0 ? " " + _NumberToText(Number % 1000000) : "");

        if (Number < 2000000000)
            return "One Billion" + (Number % 1000000000 != 0 ? " " + _NumberToText(Number % 1000000000) : "");

        return _NumberToText(Number / 1000000000) + " Billions" + (Number % 1000000000 != 0 ? " " + _NumberToText(Number % 1000000000) : "");
    }
};