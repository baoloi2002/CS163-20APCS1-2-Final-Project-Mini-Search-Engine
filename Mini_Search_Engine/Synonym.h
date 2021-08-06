#ifndef _Synonym_
#define _Synonym_

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
typedef long long lld;
typedef pair <lld, int> pli;
typedef pair <int, int> pii;
typedef pair <pii, lld> iiL;

struct synNode {
    int height, synonym;
    lld  *val;
    char *wrd;
    synNode *lef = nullptr;
    synNode *rig = nullptr;
    synNode (const lld &hashValue, const string &str) {
        int sz = (int) str.length();
        wrd = new char[sz];
        val = new lld [51];
        val[0] = hashValue;
        height = synonym = 1;
        for (int i = 1; i < 51; ++i) {
            val[i] = 0;
        }
        for (int i = 0; i < sz; ++i) {
            wrd[i] = str[i];
        }
        wrd[sz] = '\0';
    }
    int high(synNode* root) {
        return (root == nullptr) ? 0 : root->height;
    }
    int disp(synNode* root) {
        return high(root->lef) - high(root->rig);
    }
    synNode* L_Turn(synNode* x) {
        synNode *y = x->rig, *T = y->lef;
        y->lef = x;
        x->rig = T;
        x->height = max(high(x->lef), high(x->rig)) + 1;
        y->height = max(high(y->lef), high(y->rig)) + 1;
        return y;
    }
    synNode* R_Turn(synNode* x) {
        synNode *y = x->lef, *T = y->rig;
        y->rig = x;
        x->lef = T;
        x->height = max(high(x->lef), high(x->rig)) + 1;
        y->height = max(high(y->lef), high(y->rig)) + 1;
        return y;
    }
    void Insert(synNode* &root, const lld &val, const string &str) {
        if (!root) {
            root = new synNode(val, str);
            return;
        } else if (val < root->val[0]) {
            Insert(root->lef, val, str);
        } else if (val > root->val[0]) {
            Insert(root->rig, val, str);
        }
        root->height = max(high(root->lef), high(root->rig)) + 1;
        if (disp(root) > 1) {
            if (val > root->lef->val[0]) {
                root->lef = L_Turn(root->lef);
            }
            root = R_Turn(root);
        } else if (disp(root) < -1) {
            if (val < root->rig->val[0]) {
                root->rig = R_Turn(root->rig);
            }
            root = L_Turn(root);
        }
    }
    void Update(synNode* &root, const lld &val, const lld &key) {
        if (val == root->val[0]) {
            if (root->synonym == 51) {
                return;
            }
            for (int i = 1; i < root->synonym; ++i) if (root->val[i] == key) {
                return;
            }
            root->val[root->synonym++] = key;
        } else if (val < root->val[0]) {
            Update(root->lef, val, key);
        } else if (val > root->val[0]) {
            Update(root->rig, val, key);
        }
    }
    void Search(synNode* root, const lld &val, synNode* &chk) {
        if (!root) {
            chk = nullptr;
        } else if (val < root->val[0]) {
            Search(root->lef, val, chk);
        } else if (val > root->val[0]) {
            Search(root->rig, val, chk);
        } else {
            chk = root;
        }
    }
};

struct informationSyn {
    string txt;
    lld key;
};

class Synonym{
    synNode* root = nullptr;
    vector <informationSyn> arr;
    int cnt;
    const lld oo = 1000000007;
    const lld Base = 259;
public:
    Synonym(){
        cnt = 0;
        arr.resize(51);/// why 51?
        inputDataOfSynonymWs(root);
    }
    vector<string> getSynonym(string str);
    void inputSynonymWords(synNode* &root);
    void inputDataOfSynonymWs(synNode* &root);
};


#endif //_Synonym_



