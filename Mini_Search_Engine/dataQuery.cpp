#include "dataQuery.h"

bool dataQuery::isSplitChar(char u){
    vector<char> a = {' ', ',', '.', ';', ':', '?', '!'};
    for (int i=0, ii=a.size(); i<ii; ++i)
        if (a[i] == u)
        return true;
    return false;
}

void dataQuery::splitString(string u){
    string s = "";
    for (int i=0, ii=u.size(); i<ii; ++i){
        if (isSplitChar(u[i])){
            if (int(s.size()) > 0)
                saveData(s);
            s = "";
        }else
            s.pb(u[i]);
    }
    if (int(s.size()) > 0)
        saveData(s);
}

void dataQuery::insert(const string &u, int pos, dataQueryNode* cur){
    if (pos == int(u.size())){
        int key = hTable.getKey(u);
        ++hTable.cnt[key];
        hTable.save(key);
        cur->best.push_back(mp(hTable.cnt[key], key));
        cur->buildBest();
        return ;
    }
    int v = int(u[pos]);
    if (cur->pNext[v] == nullptr){
        cur->pNext[v] = new dataQueryNode();
    }
    insert(u, pos+1, cur->pNext[v]);
    for (int i=0, ii=cur->pNext[v]->best.size(); i<ii; ++i)
        cur->best.pb(cur->pNext[v]->best[i]);
    cur->buildBest();
    for (int i=0, ii=cur->best.size(); i<ii; ++i){
        for (int j=i+1; j<ii; ++j)
        if (cur->best[i].se == cur->best[j].se){
            cout<<endl;
            for (int k=0; k<ii; ++k){
                cout << "         " << cur->best[k].fi << "          "<<cur->best[k].se<<endl;
            }
        }
    }
}

void dataQuery::saveData(string u){
    if (hTable.cnt[hTable.getKey(u)] == 0){
        ofstream fo;
        fo.open("dataQuery/Words.txt", ios::app);
        fo << u << endl;
        fo.close();
    }
    /// insert to current trie
    insert(u, 0, root);
}

void dataQuery::addData(string u){
    splitString(u);
}

vector<string> dataQuery::getBestResult(string u){
    int v;
    dataQueryNode* cur = root;
    for (int i=0, ii=u.size(); i<ii; ++i){
        v = int(u[i]);
        if (cur->pNext[v] == nullptr){
            //cur->buildBest
            return convertVKeyToVStr(cur->best);
        }
        cur = cur->pNext[v];
    }
    return convertVKeyToVStr(cur->best);
}

vector<string> dataQuery::convertVKeyToVStr(const vector<pair<int,int> > &a){
    vector<string> b;
    gotoXY(0, 6);
    for (int i=0, ii=a.size(); i<ii; ++i){
        b.pb(hTable.val[a[i].se]);
    }
    return b;
}

dataQuery::dataQuery(){
    root = new dataQueryNode();
    ifstream fi;
    fi.open("dataQuery/Words.txt");
    string s="";
    while(fi>>s && s!=""){
        build(s, 0, root);
        s = "";
    }
    fi.close();
}

void dataQuery::build(const string &u, int pos, dataQueryNode* cur){
    if (pos == int(u.size())){
        int key = hTable.getKey(u);
        cur->best.push_back(mp(hTable.cnt[key],key));
        cur->buildBest();
        return ;
    }
    int v = int(u[pos]);
    if (cur->pNext[v] == nullptr){
        cur->pNext[v] = new dataQueryNode();
    }
    build(u, pos+1, cur->pNext[v]);
    for (int i=0, ii=cur->pNext[v]->best.size(); i<ii; ++i)
        cur->best.pb(cur->pNext[v]->best[i]);
    cur->buildBest();
}

void hashTableNode::save(int pos){
    ofstream fo;
    fo.open("dataQuery/CountWord.dat",ios::binary);
    fo.write((char*)cnt, sizeof(int)*Nmax);
    fo.close();
}

int hashTableNode::getKey(string u){
    int key = 0;
    for (int i=0, ii=u.size(); i<ii; ++i)
        key = (key*base + int(u[i])) % Nmax;
    while(val[key] != "" && val[key] != u)
        key = (key + 1) % Nmax;
    if (val[key] == "")
        val[key] = u;
    return key;
}

void hashTableNode::saveData(string u){
    save(getKey(u));
}

bool cmpSeFi(const pair<int,int>& u, const pair<int,int>& v){
    return u.se>v.se || (u.se==v.se && u.fi>v.fi);
}

void dataQueryNode::buildBest(){
    sort(best.begin(), best.end(), cmpSeFi);
    for (int i=1, ii=best.size(); i<ii; ++i)
        if (best[i].se == best[i-1].se){
            best[i].fi = best[i-1].fi;
        }
    sort(best.begin(), best.end(), greater<pair<int,int> >());
    best.resize(unique(best.begin(), best.end()) - best.begin());
    while(int(best.size()) > 5)
        best.pop_back();
}
