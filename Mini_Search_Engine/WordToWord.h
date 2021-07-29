#ifndef _WordToWord_
#define _WordToWord_
#define mp make_pair
#define fi first
#define se second

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class WTWSuggest{
public:
    vector<string> get(string u);
    void add(string u, string v);
    bool isSplitChar(char u);
    void splitString(string u);
    void addData(string u);
};

#endif // _WordToWord_
