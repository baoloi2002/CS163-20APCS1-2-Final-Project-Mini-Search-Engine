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

void MainDataBuild::NormalFind(string s){
    string query = stWords.removeStopWords(s);
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
    listStr.clear();
    listStr = splitString(s);
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
    if (file.empty()){
        cout << "NOTHING HERE !" << endl;
        return;
    }
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
            if (j>=50 && isHighlight[j-50])
                --s;
            if (s >= best){
                best = s;
                id = j;
            }
        }

        for (int j= max(0, id-50); j<=id; ++j){
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

/// Synonym find
void MainDataBuild::SynonymFind(string query){
    query = optimizeStr(query);
    vector<string> a = synData.getSynonym(query);
    for (int i=0, ii=a.size(); i<ii; ++i)
        query += " " + a[i];
    NormalFind(query);
}

/// And find

void MainDataBuild::AndFind(string s){
    vector<string> originalStr;
    vector<string> listStr = splitString(s);
    vector<vector<string> > query;
    vector<string> tmpLStr;
    for (int i=0, ii=listStr.size(); i<ii; ++i){
        string tmp = stWords.removeStopWords(optimizeStr(listStr[i]));
        if (listStr[i] == "AND"){
            if (!tmpLStr.empty()){
                query.pb(tmpLStr);
                tmpLStr.clear();
            }
        }else{
            originalStr.pb(listStr[i]);
            if (tmp != "")
                tmpLStr.pb(tmp);
        }
    }
    if (!tmpLStr.empty()){
        query.pb(tmpLStr);
        tmpLStr.clear();
    }

    vector<pair<int,int> > res, tmpRes;

    for (int i=0, ii=query.size(); i<ii; ++i){
        for (int j=0, jj=query[i].size(); j<jj; ++j)
            tmpRes = mergeRes(tmpRes, trieMainData.find(query[i][j]));
        if (i == 0)
            res = tmpRes;
        else
            res = andRes(res, tmpRes);
        tmpRes.clear();
    }

    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    for (int i=0, ii = res.size(); i<ii; ++i){
        q.push(mp(res[i].se, res[i].fi));
        if (q.size() > 5)
            q.pop();
    }

    vector<int> ans;
    while(!q.empty()){
        ans.pb(q.top().se);
        q.pop();
    }
    display(ans, originalStr);
}

vector<pair<int,int> > MainDataBuild::andRes(vector<pair<int,int> > u, vector<pair<int,int> > v){
    sort(u.begin(), u.end());
    sort(v.begin(), v.end());

    int i=0, j=0, n = u.size(), m = v.size();
    vector<pair<int,int> > res;
    while(i<n && j<m){
        if (u[i].fi < v[j].fi){
            ++i;
        }else
        if (u[i].fi > v[j].fi){
            ++j;
        }else{
            res.pb(mp(u[i].fi, u[i].se + v[j].se));
            ++i, ++j;
        }
    }
    return res;
}

/// Or find
void MainDataBuild::OrFind(string s){
    string query = stWords.removeStopWords(s);
    vector<string> listStr = splitString(query);

    for (int i=0, ii=listStr.size(); i<ii; ++i){
        if (listStr[i] == "OR"){
            swap(listStr[i], listStr.back());
            listStr.pop_back();
            --ii;
            --i;
        }
    }

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
    listStr.clear();
    listStr = splitString(s);
    for (int i=0, ii=listStr.size(); i<ii; ++i){
        if (listStr[i] == "OR"){
            swap(listStr[i], listStr.back());
            listStr.pop_back();
            --i;
            --ii;
        }
    }
    display(res, listStr);
}

/// Exact Match And Wild card find

void MainDataBuild::WildcardFind(string s){
    vector<string> originalStr;
    vector<string> listStr = splitString(s);
    vector<vector<string> > query;
    vector<string> tmpLStr;
    for (int i=0, ii=listStr.size(); i<ii; ++i){
        string tmp = stWords.removeStopWords(optimizeStr(listStr[i]));
        if (listStr[i] == "*"){
            if (!tmpLStr.empty()){
                query.pb(tmpLStr);
                tmpLStr.clear();
            }
        }else{
            originalStr.pb(listStr[i]);
            if (tmp != "")
                tmpLStr.pb(tmp);
        }
    }
    if (!tmpLStr.empty()){
        query.pb(tmpLStr);
        tmpLStr.clear();
    }

    vector<pair<int,int> > res;

    for (int i=0, ii=query.size(); i<ii; ++i){
        for (int j=0, jj=query[i].size(); j<jj; ++j){
            if (res.empty())
                res = trieMainData.find(query[i][j]);
            else
                res = mergeRes(res, trieMainData.find(query[i][j]));
        }
    }

    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    for (int i=0, ii = res.size(); i<ii; ++i){
        q.push(mp(res[i].se, res[i].fi));
        if (q.size() > 5)
            q.pop();
    }

    vector<int> ans;
    while(!q.empty()){
        ans.pb(q.top().se);
        q.pop();
    }
    display(ans, originalStr);
}

/// Minus find
void MainDataBuild::MinusFind(string query){
    vector<string> a = splitString(query);
    vector<pair<int,int> > res, minusArr;
    vector<string> listStr;
    for (int i=0, ii=a.size(); i<ii; ++i){
        if (a[i][0] == '-')
            minusArr = mergeRes(minusArr, trieMainData.find(a[i]));
        else{
            res = mergeRes(res, trieMainData.find(a[i]));
            listStr.pb(a[i]);
        }
    }
    res = minusRes(res, minusArr);

    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    for (int i=0, ii = res.size(); i<ii; ++i){
        q.push(mp(res[i].se, res[i].fi));
        if (q.size() > 5)
            q.pop();
    }

    vector<int> ans;
    while(!q.empty()){
        ans.pb(q.top().se);
        q.pop();
    }

    display(ans, listStr);
}

vector<pair<int,int> > MainDataBuild::minusRes(vector<pair<int,int> > u, vector<pair<int,int> > v){
    sort(u.begin(), u.end());
    sort(v.begin(), v.end());
    int i=0, j=0, n = u.size(), m = v.size();
    vector<pair<int,int> > res;
    while(i<n || j<m){
        if (i == n){
            break;
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
            ++j;
        }else{
            ++i, ++j;
        }
    }
    return res;
}

/// Intitle find

void MainDataBuild::IntitleFind(string s){
    string Stmp;
    for (int i=8, ii=s.size(); i<ii; ++i)
        Stmp.pb(s[i]);

    string query = stWords.removeStopWords(Stmp);
    vector<string> listStr = splitString(query);
    vector<pair<int, int> > tmp;
    for (int i=0, ii=listStr.size(); i<ii; ++i)
        tmp = mergeRes(tmp, trieMainData.find(listStr[i]));

    /// Add bonus for title
    for (int i=0, ii=listStr.size(); i<ii; ++i)
        listStr[i] = optimizeStr(listStr[i]);

    for (int i=0, ii=tmp.size(); i<ii; ++i){
        if (tmp[i].fi == -1){
            cerr << "OK" << endl;
        }
        int n = listStr.size();
        ifstream fi;
        string address = "Search Engine-Data/" + validFile[tmp[i].fi];
        n = n*3 / 2;
        fi.open(address);
        string u;
        while (fi >> u && u !="" && n>0){
            u = optimizeStr(u);
            for (int j=0, jj=listStr.size(); j<jj;++j)
            if (u == listStr[j]){
                tmp[i].se += 20;
                break;
            }
            --n;
            u="";
        }
        fi.close();
    }

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
    listStr.clear();
    listStr = splitString(Stmp);

    displayWithTitleCheck(res, listStr);
}

void MainDataBuild::displayWithTitleCheck(vector<int> file, vector<string> query){
    if (file.empty()){
        cout << "NOTHING HERE !" << endl;
        return;
    }
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

        int id = min(30, n-1), best = m, s=0;
        for (int j=0; j<n; ++j){
            if (isHighlight[j]) ++s;
            if (j>=50 && isHighlight[j-50])
                --s;
            if (s >= best){
                best = s;
                id = j;
            }
        }

        for (int j= max(0, id-50); j<=id; ++j){
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
