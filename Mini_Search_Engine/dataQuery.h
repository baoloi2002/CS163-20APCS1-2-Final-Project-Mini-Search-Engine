#ifndef _dataQuery_
#define _dataQuery_
#define pb push_back
#define fi first
#define se second
#define mp make_pair

#include "SetConsoleCursorPosition.h"
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class dataQueryNode{
    vector<pair<int,int> > best;
    dataQueryNode* pNext[256];
    dataQueryNode(){
        for (int i=0; i<256; ++i)
            pNext[i] = nullptr;
    }
    void buildBest();
friend class dataQuery;
};

class hashTableNode{
    const int Nmax = 1000003;
    const int base = 259;
    string* val;
    int* cnt;
    hashTableNode(){
        val = new string[Nmax];
        cnt = new int[Nmax];
        for (int i=0; i<Nmax; ++i)
            val[i] = "";
        ifstream fi;
        fi.open("dataQuery/CountWord.dat", ios::binary);
        fi.read((char*)cnt, sizeof(cnt[0])*Nmax);
        fi.close();
    }
    void save(int pos);
    int getKey(string u);
    void saveDataToFile();
friend class dataQuery;
};

class dataQuery{
    dataQueryNode* root;
    hashTableNode hTable;
public:
    void splitString(string u);
    void insert(const string &u, int pos, dataQueryNode* root);
    void saveData(string u);
    void addData(string u);
    bool isSplitChar(char u);
    vector<string> getBestResult(string u);
    vector<string> convertVKeyToVStr(const vector<pair<int,int> >& a);
    void build(const string &u, int pos, dataQueryNode* root);
    dataQuery();
};

#endif // _dataQuery_
