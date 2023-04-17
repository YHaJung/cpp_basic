#include "WordCounter.h"
// Fill in here

#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

WordCounter::WordCounter(){
}

void WordCounter::InputText(string atext){
    text = atext;
}

int WordCounter::GetWordCount(){
    stringstream stext(text);
    string word;
    vector<string> words;
    while (getline(stext, word, ' ')){
        words.push_back(word);
    }
    return words.size();
}

int WordCounter::GetCharacterCount(){
    int charCount = 0;
    for (char c : text){
        if (c!=' ' & c != '.' & c != ','){
            charCount = charCount + 1;
        }
    }
    return charCount;
}

int WordCounter::GetUniqueWordCount(){
    stringstream stext(text);
    string word;
    vector<string> words;
    while (getline(stext, word, ' ')){
        words.push_back(word);
    }

    sort(words.begin(), words.end());
    words.erase(unique(words.begin(), words.end()), words.end());

    return words.size();
}

int WordCounter::GetWordCount_OneWord(const char * key){
    stringstream stext(text);
    string word;
    vector<string> words;
    int keyCount = 0;
    while (getline(stext, word, ' ')){
        if (word.back()==',' | word.back()=='.'){
            word.pop_back();
        }
        if (word == key){
            keyCount = keyCount + 1;
        }
    }
    return keyCount;
}