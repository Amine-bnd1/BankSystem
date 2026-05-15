#pragma once
#include <string>
#include <vector>
#include <cctype>

class clsString {
private:
    std::string _Value;

    static char _ToLowerChar(char c) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    static char _ToUpperChar(char c) {
        return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

public:
    clsString() : _Value("") {}
    clsString(const std::string& Value) : _Value(Value) {}

    void SetValue(const std::string& Value) {
        _Value = Value;
    }

    std::string GetValue() const {
        return _Value;
    }

    static short CountString(std::string S1) {
        const std::string Delim = " ";
        if (Delim.empty()) return static_cast<short>(S1.empty() ? 0 : 1);

        size_t pos = 0;
        std::string sword;
        short Counter = 0;

        while ((pos = S1.find(Delim)) != std::string::npos) {
            sword = S1.substr(0, pos);
            if (!sword.empty()) {
                Counter++;
            }
            S1.erase(0, pos + Delim.length());
        }

        if (!S1.empty()) {
            Counter++;
        }
        return Counter;
    }

    short CountString() {
        return CountString(_Value);
    }

    static std::vector<std::string> SplitString(std::string S1, const std::string& Delim) {
        std::vector<std::string> VstStrings;
        if (Delim.empty()) {
            if (!S1.empty()) VstStrings.push_back(S1);
            return VstStrings;
        }

        std::string sword;
        size_t pos = 0;

        while ((pos = S1.find(Delim)) != std::string::npos) {
            sword = S1.substr(0, pos);
            if (!sword.empty()) {
                VstStrings.push_back(sword);
            }
            S1.erase(0, pos + Delim.length());
        }

        if (!S1.empty()) {
            VstStrings.push_back(S1);
        }
        return VstStrings;
    }

    std::vector<std::string> SplitString(const std::string& Delim) {
        return SplitString(_Value, Delim);
    }

    static std::string UpperFirstLetterOfEachWord(std::string S1) {
        bool newWord = true;
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isspace(static_cast<unsigned char>(S1[i]))) {
                newWord = true;
            } else if (newWord && std::isalpha(static_cast<unsigned char>(S1[i]))) {
                S1[i] = _ToUpperChar(S1[i]);
                newWord = false;
            } else {
                newWord = false;
            }
        }
        return S1;
    }

    std::string UpperFirstLetterOfEachWord() {
        return UpperFirstLetterOfEachWord(_Value);
    }

    static std::string LowerFirstLetterOfEachWord(std::string S1) {
        bool newWord = true;
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isspace(static_cast<unsigned char>(S1[i]))) {
                newWord = true;
            } else if (newWord && std::isalpha(static_cast<unsigned char>(S1[i]))) {
                S1[i] = _ToLowerChar(S1[i]);
                newWord = false;
            } else {
                newWord = false;
            }
        }
        return S1;
    }

    std::string LowerFirstLetterOfEachWord() {
        return LowerFirstLetterOfEachWord(_Value);
    }

    static std::string UpperAllString(std::string S1) {
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isalpha(static_cast<unsigned char>(S1[i]))) {
                S1[i] = _ToUpperChar(S1[i]);
            }
        }
        return S1;
    }

    std::string UpperAllString() {
        return UpperAllString(_Value);
    }

    static std::string LowerAllString(std::string S1) {
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isalpha(static_cast<unsigned char>(S1[i]))) {
                S1[i] = _ToLowerChar(S1[i]);
            }
        }
        return S1;
    }

    std::string LowerAllString() {
        return LowerAllString(_Value);
    }

    static std::string InvertLetterCase(std::string S1) {
        // Invert first letter of each word
        bool newWord = true;
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isspace(static_cast<unsigned char>(S1[i]))) {
                newWord = true;
            } else if (newWord && std::isalpha(static_cast<unsigned char>(S1[i]))) {
                if (std::isupper(static_cast<unsigned char>(S1[i]))) {
                    S1[i] = _ToLowerChar(S1[i]);
                } else if (std::islower(static_cast<unsigned char>(S1[i]))) {
                    S1[i] = _ToUpperChar(S1[i]);
                }
                newWord = false;
            } else {
                newWord = false;
            }
        }
        return S1;
    }

    std::string InvertLetterCase() {
        return InvertLetterCase(_Value);
    }

    static std::string InvertAllLetterCase(std::string S1) {
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isupper(static_cast<unsigned char>(S1[i]))) {
                S1[i] = _ToLowerChar(S1[i]);
            } else if (std::islower(static_cast<unsigned char>(S1[i]))) {
                S1[i] = _ToUpperChar(S1[i]);
            }
        }
        return S1;
    }

    std::string InvertAllLetterCase() {
        return InvertAllLetterCase(_Value);
    }

    static short CountLetters(const std::string& S1) {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isalpha(static_cast<unsigned char>(S1[i]))) {
                Counter++;
            }
        }
        return Counter;
    }

    short CountLetters() {
        return CountLetters(_Value);
    }

    static short CountCapitalLetter(const std::string& S1) {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isalpha(static_cast<unsigned char>(S1[i])) &&
                std::isupper(static_cast<unsigned char>(S1[i]))) {
                Counter++;
            }
        }
        return Counter;
    }

    short CountCapitalLetter() {
        return CountCapitalLetter(_Value);
    }

    static short CountSmallLetter(const std::string& S1) {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isalpha(static_cast<unsigned char>(S1[i])) &&
                std::islower(static_cast<unsigned char>(S1[i]))) {
                Counter++;
            }
        }
        return Counter;
    }

    short CountSmallLetter() {
        return CountSmallLetter(_Value);
    }

    static short CountSpecificLetter(const std::string& S1, char Target, bool MatchCase = true) {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); i++) {
            if (MatchCase) {
                if (S1[i] == Target) {
                    Counter++;
                }
            } else {
                if (_ToLowerChar(S1[i]) == _ToLowerChar(Target)) {
                    Counter++;
                }
            }
        }
        return Counter;
    }

    short CountSpecificLetter(char Target, bool MatchCase = true) {
        return CountSpecificLetter(_Value, Target, MatchCase);
    }

    static bool IsVowel(char C) {
        C = _ToLowerChar(C);
        return (C == 'a' || C == 'e' || C == 'i' || C == 'o' || C == 'u');
    }

    static bool HasVowel(const std::string& S1) {
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isalpha(static_cast<unsigned char>(S1[i])) && IsVowel(S1[i])) {
                return true;
            }
        }
        return false;
    }

    bool HasVowel() {
        return HasVowel(_Value);
    }

    static short CountVowels(const std::string& S1) {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); i++) {
            if (std::isalpha(static_cast<unsigned char>(S1[i])) && IsVowel(S1[i])) {
                Counter++;
            }
        }
        return Counter;
    }

    short CountVowels() {
        return CountVowels(_Value);
    }

    static std::string TrimLeft(const std::string& S1) {
        size_t i = 0;
        while (i < S1.length() && std::isspace(static_cast<unsigned char>(S1[i]))) {
            i++;
        }
        return S1.substr(i);
    }

    std::string TrimLeft() {
        return TrimLeft(_Value);
    }

    static std::string TrimRight(const std::string& S1) {
        size_t i = S1.length();
        while (i > 0 && std::isspace(static_cast<unsigned char>(S1[i - 1]))) {
            i--;
        }
        return S1.substr(0, i);
    }

    std::string TrimRight() {
        return TrimRight(_Value);
    }

    static std::string Trim(const std::string& S1) {
        return TrimRight(TrimLeft(S1));
    }

    std::string Trim() {
        return Trim(_Value);
    }

    static std::string JoinString(const std::vector<std::string>& VstStrings, const std::string& Delim) {
        std::string S1;
        for (size_t i = 0; i < VstStrings.size(); i++) {
            S1 += VstStrings[i];
            if (i != VstStrings.size() - 1) {
                S1 += Delim;
            }
        }
        return S1;
    }

    std::string JoinStringFromVector(const std::vector<std::string>& VstStrings, const std::string& Delim) {
        return clsString::JoinString(VstStrings, Delim);
    }

    static std::string ReverseWordsInStrings(const std::string& S1) {
        std::vector<std::string> Vstrings = SplitString(S1, " ");
        std::vector<std::string> Reversed;

        for (size_t i = Vstrings.size(); i > 0; i--) {
            Reversed.push_back(Vstrings[i - 1]);
        }
        return JoinString(Reversed, " ");
    }

    std::string ReverseWordsInStrings() {
        return ReverseWordsInStrings(_Value);
    }

    static std::string ReplaceWord(const std::string& S1, const std::string& WordToReplace, const std::string& ReplaceTo, bool MatchCase = true) {
        if (WordToReplace.empty()) {
            return S1;
        }

        std::vector<std::string> VstStrings = SplitString(S1, " ");

        for (size_t i = 0; i < VstStrings.size(); i++) {
            if (MatchCase) {
                if (VstStrings[i] == WordToReplace) {
                    VstStrings[i] = ReplaceTo;
                }
            } else {
                if (LowerAllString(VstStrings[i]) == LowerAllString(WordToReplace)) {
                    VstStrings[i] = ReplaceTo;
                }
            }
        }
        return JoinString(VstStrings, " ");
    }

    std::string ReplaceWord(const std::string& WordToReplace, const std::string& ReplaceTo, bool MatchCase = true) {
        return clsString::ReplaceWord(_Value, WordToReplace, ReplaceTo, MatchCase);
    }

    static std::string RemovePunctuations(const std::string& S1) {
        std::string Result;
        for (size_t i = 0; i < S1.length(); i++) {
            if (!std::ispunct(static_cast<unsigned char>(S1[i]))) {
                Result += S1[i];
            }
        }
        return Result;
    }

    std::string RemovePunctuations() {
        return RemovePunctuations(_Value);
    }
};
