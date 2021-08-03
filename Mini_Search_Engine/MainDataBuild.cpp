#include "MainDataBuild.h"
#include "Header.h"

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

string Trie::optimizeStr(string u){
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
    display(res);
}

vector<string> MainDataBuild::splitString(string u){
    vector<string> res;
    string s = "";
    for (int i=0, ii=u.size(); i<ii; ++i){
        if (u[i] == ' '){
            if (s != "")
                res.pb(s);
            s = "";
        }else
            s.pb(u[i]);
    }
    if (s != "")
        res.pb(s);
    return res;
}

void MainDataBuild::display(vector<int> file){
    for (int i=0, ii=file.size(); i<ii; ++i){
        cout << validFile[file[i]] << endl;
    }
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

