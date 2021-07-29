#include "WordToWord.h"

vector<string> WTWSuggest::get(string u){
    ifstream fi;
    string address = "dataQuery/WordToWordData/" + u + ".txt";
    vector<string> res;
    fi.open(address.c_str());
    if (fi.is_open()){
        int n;
        fi >> n;
        int tmp;
        string v;
        for (int i=0, ii = min(n, 5); i<ii; ++i){
            fi >> tmp >> v;
            res.push_back(v);
        }
    }
    fi.close();
    return res;
}

void WTWSuggest::add(string u, string v){
    string address = "dataQuery/WordToWordData/" + u + ".txt";
    int n;
    vector<pair<int, string> > a;
    ifstream fi;
    fi.open(address.c_str());
    if (fi.is_open()){
        fi >> n;
        int tmp;
        string s;
        for (int i=0; i<n; ++i){
            fi >> tmp >> s;
            a.push_back(mp(tmp, s));
        }
    }else{
        n = 0;
    }
    fi.close();

    bool isOk = true;
    for (int i=0; i<n; ++i){
        if (a[i].se == v){
            ++a[i].fi;
            for (int j = i-1; j>=0; --j)
                if (a[j].fi < a[j+1].fi)
                    swap(a[j], a[j+1]);
                else
                    break;
            isOk = false;
        }
    }
    if (isOk){
        a.push_back(mp(1, v));
        ++n;
    }

    ofstream fo;
    fo.open(address.c_str());
    fo << n << endl;
    for (int i=0; i<n; ++i){
        fo << a[i].fi << ' ' << a[i].se << endl;
    }
    fo.close();
}

bool WTWSuggest::isSplitChar(char u){
    vector<char> a = {' ', ',', '.', ';', ':', '?', '!'};
    for (int i=0, ii=a.size(); i<ii; ++i)
        if (a[i] == u)
        return true;
    return false;
}

void WTWSuggest::splitString(string u){
    string a = "", b = "";
    for (int i=0, ii=u.size(); i<ii; ++i){
        if (isSplitChar(u[i])){
            if (int(b.size()) > 0){
                if (a != "")
                    add(a, b);
            }
            a = b;
            b.clear();
        }else
            b.push_back(u[i]);
    }
    if (int(b.size()) > 0){
        if (a != "")
            add(a, b);
    }
}
void WTWSuggest::addData(string u){
    splitString(u);
}

