/*
Name: Tran Bao Loi
Class: 20ctt1
Sid: 20125010
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstdio>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

void getListOFVaildFile(vector<string>& validFile);
bool isValidChar(char u);
bool isValidFile(string address);
bool isValidString(string u);
void removeFile(vector<string>& goodFile);

/// number of Word, sum len of all word, sum of all hash key, sum of all hash key with len
const int Mod = 1e9 + 801;
const int baseW = 130;
const int baseL = 39;
typedef pair<int, pair<int, pair<int, int> > > DATA;

int main(){
    /*
    /// Get valid file to "validfile.txt"
    vector<string> validFile;
    getListOFVaildFile(validFile);

    ofstream fo;
    fo.open("validFile.txt");
    fo << int(validFile.size()) << endl;
    for (string u: validFile)
        fo << u << endl;
    fo.close();
    */


    /// Clear file that have same content
    ifstream fi;
    fi.open("validFile.txt");
    vector<string> a;
    int n;
    fi >> n;
    a.resize(n);
    fi.ignore();
    for (int i=0; i<n; ++i){
        getline(fi, a[i]);
    }
    fi.close();


    set<DATA> isCopy;
    vector<string> b;/// good file;
    for (int i=0; i<n; ++i){
        string address = "Search Engine-Data/" + a[i];
        fi.open(address);
        int len = 0;
        int sumLen = 0;
        int hashKey = 0;
        int sumHKey = 0;
        int sumHKeyLen = 0;

        string s = "";
        while(fi >> s && s!=""){
            ++len;

            sumLen = (1LL*sumLen*baseL + int(s.size())) % Mod;

            hashKey = 0;
            for (char u: s)
                hashKey = (1LL*hashKey*baseW + int(u)) % Mod;

            sumHKey = (1LL*sumHKey*baseL + hashKey) % Mod;

            hashKey = (1LL*hashKey*baseL + int(s.size())) % Mod;

            sumHKeyLen = (1LL*sumHKeyLen*baseW + hashKey) % Mod;

            s = "";
        }


        fi.close();

        DATA tmp = mp(len, mp(sumLen, mp(sumHKey, sumHKeyLen)));
        if (isCopy.count(tmp))
            continue;
        isCopy.insert(tmp);
        b.pb(a[i]);
    }

    ofstream fo;
    fo.open("GoodFile.txt");
    for (string u: b){
        fo << u << endl;
    }
    fo.close();

    removeFile(b);


    return 0;
}


void removeFile(vector<string>& goodFile){
    set<string> d;
    for (string u:goodFile)
        d.insert(u);


    string address = "Search Engine-Data/___index.txt";
    ifstream fi;
    string s = "";
    fi.open(address);
    while(getline(fi, s)){
        cerr << s << "  ";
        if (d.count(s) == 0){
            string tmp = "Search Engine-Data/" + s;
            if (remove(tmp.c_str()) == 0)
                cerr << "is removed !" << endl;
            else
                cerr << "ERROR !!!!!!!!!" << endl;

        } else cerr << "GOOD *****" << endl;
        s = "";
    }
    fi.close();

}

void getListOFVaildFile(vector<string>& validFile){
    string address = "Search Engine-Data/___index.txt";
    ifstream fi;
    string s = "";
    fi.open(address);
    while(getline(fi, s)){
        if (isValidString(s) && isValidFile(s)){
            validFile.pb(s);
        }
        s = "";
    }
    fi.close();
}

bool isValidFile(string address){
    address = "Search Engine-Data/" + address;
    ifstream fi;
    fi.open(address);
    string u = "";
    bool ok = true;
    while(fi >> u){
        if (!isValidString(u)){
            ok = false;
            break;
        }
        u = "";
    }
    fi.close();
    return ok;
}

bool isValidString(string u){
    for (int i=0, ii=u.size(); i<ii; ++i)
        if (!isValidChar(u[i])) return false;
    return true;
}

bool isValidChar(char u){
    return 0 <= int(u) && int(u) <= 126;
}
