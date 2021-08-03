#include "MainDataBuild.h"
#include "Header.h"
#include <windows.h>

string optimizeStr(string u){
    string v;
    for (int i=0,ii = u.size(); i<ii; ++i){
        if ('0' <= u[i] && u[i] <= '9')
            v.pb(u[i]);
        else
        if ('a' <= u[i] && u[i] <= 'z')
            v.pb(u[i]);
        else
        if ('A' <= u[i] && u[i] <= 'Z')
            v.pb(char(u[i] - 'A' + 'a'));
    }
    return v;
}

void ChangeTextColor(int u){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, u);
}

/// Class Trie


void Trie::insert(string u, int id){
    u = optimizeStr(u);
    if (stWords.isStopWord(u))
        return;
    int v;
    Node* cur = root;
    for (int i=0, ii=u.size(); i<ii; ++i){
        v = int(u[i]);
        if (cur->pNext[v] == nullptr){
            cur->pNext[v] = new Node;
        }
        cur = cur->pNext[v];
    }
    cur->isEndOfWord = true;
    cur->mapId.insertData(id);
}

vector<pair<int, int> > Trie::find(string u){
    vector<pair<int, int> > res;
    u = optimizeStr(u);
    if (stWords.isStopWord(u))
        return res;
    int v;
    Node* cur = root;
    for (int i=0, ii=u.size(); i<ii; ++i){
        v = int(u[i]);
        if (cur->pNext[v] == nullptr){
            return res;
        }
        cur = cur->pNext[v];
    }
    res = cur->mapId.getList();
    return res;
}

/// Class Main Data Build

MainDataBuild::MainDataBuild(){
    validFile.clear();
    getListOFVaildFile();
    for (int i=0, ii = validFile.size(); i<ii; ++i){
        addDataFromFile(validFile[i], i);
    }
}


void MainDataBuild::addDataFromFile(string address, int id){
    address = "Search Engine-Data/" + address;
    ifstream fi;
    fi.open(address);
    string u = "";
    while(fi >> u && u!=""){
        trieMainData.insert(u, id);
        u = "";
    }
    fi.close();
}

void MainDataBuild::getListOFVaildFile(){
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

bool MainDataBuild::isValidFile(string address){
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

bool MainDataBuild::isValidString(string u){
    for (int i=0, ii=u.size(); i<ii; ++i)
        if (!isValidChar(u[i])) return false;
    return true;
}

bool MainDataBuild::isValidChar(char u){
    return 0 <= int(u) && int(u) <= 126;
}

///Normal find

void MainDataBuild::NormalFind(string query){
    vector<string> listStr = splitString(query);
    vector<pair<int, int> > tmp;
    for (int i=0, ii=listStr.size(); i<ii; ++i)
        tmp = mergeRes(tmp, trieMainData.find(listStr[i]));

    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    for (int i=0, ii = tmp.size(); i<ii; ++i){
        q.push(mp(tmp[i].se, tmp[i].fi));
        if (q.size() > 5)
            q.pop();
    }

    vector<int> res;
    while(!q.empty()){
        res.pb(q.top().se);
        q.pop();
    }
    display(res, listStr);
}

vector<string> MainDataBuild::splitString(string u){
    vector<string> res;
    string s = "";
    for (int i=0, ii=u.size(); i<ii; ++i){
        if (u[i] == ' '){
            if (s != ""){
                res.pb(s);
            }
            s = "";
        }else
            s.pb(u[i]);
    }
    if (s != ""){
        res.pb(s);
    }
    return res;
}

void MainDataBuild::display(vector<int> file, vector<string> query){
    int m = query.size();
    vector<int> hQuery;
    for (int i=0, ii=query.size(); i<ii; ++i){
        query[i] = optimizeStr(query[i]);
        hQuery.pb(hashingStr(query[i]));
    }

    for (int i=0, ii=file.size(); i<ii; ++i){
        /// File name
        cout << "*****   " << validFile[file[i]]  << "   *****"  << endl;
        vector<string> a,c;/// store the data of file;
        vector<int> b; /// store hash key of data of file;
        string address, u;

        ifstream fi;
        address = "Search Engine-Data/" + validFile[file[i]];
        fi.open(address);
        u = "";
        while (fi >> u && u!=""){
            a.pb(u);
            c.pb(optimizeStr(u));
            b.pb(hashingStr(c.back()));
            u="";
        }
        fi.close();

        int n = a.size();

        vector<bool> isHighlight(n, false);

        for (int j=0; j<n; ++j){
            for (int k=0; k<m; ++k){
                if (b[j] == hQuery[k]){
                    if (c[j] == query[k]){
                        isHighlight[j] = true;
                        break;
                    }
                }
            }
        }

        int id = -1, best = -1, s=0;
        for (int j=0; j<n; ++j){
            if (isHighlight[j]) ++s;
            if (j>=40 && isHighlight[j-40])
                --s;
            if (s > best){
                best = s;
                id = j;
            }
        }

        for (int j= max(0, id-40); j<=id; ++j){
            if (isHighlight[j]){
                ChangeTextColor(240);
            }else{
                ChangeTextColor(15);
            }
            cout << a[j] << ' ';
        }
        ChangeTextColor(15);
        cout << endl << endl;
    }
}

int MainDataBuild::hashingStr(string u){
    int res = 0;
    for (int i=0, ii = u.size(); i<ii; ++i)
        res = (1LL*res*hashBase + int(u[i])) % Mod;
    return res;
}

vector<pair<int,int> > MainDataBuild::mergeRes(vector<pair<int,int> > u, vector<pair<int,int> > v){
    sort(u.begin(), u.end());
    sort(v.begin(), v.end());
    int i=0, j=0, n = u.size(), m = v.size();
    vector<pair<int,int> > res;
    while(i<n || j<m){
        if (i == n){
            res.pb(v[j]);
            ++j;
        }else
        if (j == m){
            res.pb(u[i]);
            ++i;
        }else
        if (u[i].fi < v[j].fi){
            res.pb(u[i]);
            ++i;
        }else
        if (u[i].fi > v[j].fi){
            res.pb(v[j]);
            ++j;
        }else{
            res.pb(mp(u[i].fi, u[i].se + v[j].se));
            ++i, ++j;
        }
    }
    return res;
}

