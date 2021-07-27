#ifndef _readQuery_
#define _readQuery_
#define pb push_back

#include <vector>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include "SetConsoleCursorPosition.h"
#include <cstdio>
#include <algorithm>
#include "dataQuery.h"
#include "Header.h"


using namespace std;

string readQuery(string s);
vector<string> fromCharsToWord(string u);///Suggest from chars to word
vector<string> fromWordToWord(string u);///Suggest from word to word
bool isBackspace(char u);
bool isEnter(char u);
bool isSplitChar(char u);
string getLastChars(string u);
string getLastWord(string u);


#endif // _readQuery
