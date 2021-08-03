#ifndef _MainDataBuild_
#define _MainDataBuild_

#define pb push_back
#define mp make_pair
#define fi first
#define se second

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include "AvlTree.h"
#include "removeStopWords.h"
#include <queue>

using namespace std;

string optimizeStr(string u);
void ChangeTextColor(int u);

class Trie{
    const int base = 130;

    struct Node{
        const int base = 130;
        Node** pNext;
        bool isEndOfWord;
        AvlTree mapId;
        Node(){
            pNext = new Node*[base];
            for (int i=0; i<base; ++i)
                pNext[i] = nullptr;
            isEndOfWord = false;
        }
    };

    Node* root;
public:
    void insert(string u, int id);
    vector<pair<int, int> > find(string u);
    Trie(){
        root = new Node();
    }
};

class MainDataBuild{
    const int Mod = 1e9 + 7;
    const int hashBase = 131;

    vector<string> validFile;
    Trie trieMainData;
public:
    MainDataBuild();
    void getListOFVaildFile();
    void addDataFromFile(string address, int id);
    bool isValidFile(string s);
    bool isValidString(string s);
    bool isValidChar(char u);
    /// Normal find
    void NormalFind(string query);

    void SynonymFind(string query);

    void AndFind(string query);

    void OrFind(string query);

    void WildcardFind(string query);

    void MinusFind(string query);

    void IntitleFind(string query);

    void PlusFind(string query);

    void FileTypeFind(string query);

    vector<string> splitString(string u);

    vector<pair<int,int> > mergeRes(vector<pair<int,int> > u, vector<pair<int,int> > v);
    vector<pair<int,int> > andRes(vector<pair<int,int> > u, vector<pair<int,int> > v);
    vector<pair<int,int> > minusRes(vector<pair<int,int> > u, vector<pair<int,int> > v);

    void display(vector<int> file, vector<string> query);

    void displayWithTitleCheck(vector<int> file, vector<string> query);

    int hashingStr(string u);

    bool cmpSF(const pair<int,int>& u, const pair<int,int>& v);

};

#endif // _MainDataBuild_
