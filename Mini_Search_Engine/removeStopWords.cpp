#include "removeStopWords.h"

StopWords::StopWords(){     

    root = new swNode();

    ifstream fi;
    fi.open("stopWord/stopword.txt");
    string s = "";

    while(fi >> s && s!=""){    //read all stop words in file
        insertData(s);
    }

    fi.close();
}

void StopWords::insertData(string u){   //insert nhu bth 
    swNode* cur = root;
    int v;
    for (int i=0, ii=u.size(); i<ii; ++i){
        v = int(u[i]);
        if (cur->pNext[v] == nullptr){
            cur->pNext[v] = new swNode();
        }
        cur = cur->pNext[v];
    }
    cur->isEndOfWord = true;    //la stop word nen true
}

string StopWords::removeStopWords(string u){
    string res = "";
    string s = "";
    for (int i=0, ii=u.size(); i<ii; ++i){
        if (isSplitChar(u[i])){
            if (int(s.size()) > 0 && !isStopWord(s)){
                if (res == "")
                    res = s;
                else
                    res += " " + s;

            }
            s = "";
        }else
            s.pb(u[i]);
    }
    if (int(s.size()) > 0 && !isStopWord(s)){
        if (res == "")
            res = s;
        else
            res += " " + s;
    }
    return res;
}

bool StopWords::isStopWord(string u){
    swNode* cur = root;
    int v;
    for (int i=0, ii=u.size(); i<ii; ++i){
        v = int(u[i]);
        if (cur->pNext[v] == nullptr){
            return false;
        }
        cur = cur->pNext[v];
    }
    return cur->isEndOfWord;
}

bool StopWords::isSplitChar(char u){
    vector<char> a = {' ', ',', '.', ';', '?', '!'};
    for (int i=0, ii=a.size(); i<ii; ++i)
        if (a[i] == u)
        return true;
    return false;
}

