#pragma once
// Fill in here
#include <iostream>
#include <vector>
using namespace std;


class WordCounter {
    public:
        WordCounter();

        void InputText(string);
        int GetWordCount();
        int GetCharacterCount();
        int GetUniqueWordCount();
        int GetWordCount_OneWord(const char *);

    protected:
        string text;
};