#include "Synonym.h"


void Synonym::inputSynonymWords(synNode* &root) {
    synNode *chk1, *chk2;
    for (int i = 1; i < cnt; ++i) {
        root->Search(root, arr[i].key, chk1);
        if (chk1 == nullptr) {
            root->Insert(root, arr[i].key, arr[i].txt);
        }
        for (int j = i + 1; j <= cnt; ++j) {
            root->Search(root, arr[j].key, chk2);
            if (!chk2) {
                root->Insert(root, arr[j].key, arr[j].txt);
            }
            root->Update(root, arr[j].key, arr[i].key);
            root->Update(root, arr[i].key, arr[j].key);
        }
    }
}

void Synonym::inputDataOfSynonymWs(synNode* &root) {
    ifstream fsy;
    fsy.open("synonym/synonym.txt");

    int pre = 0, cur;
    while (!fsy.eof()) {
        string str; getline(fsy, str);
        if (str[0] == '=') {
            continue;
        } else if (str[0] == 'K') {
            cur = 1;
        } else if (str[0] == 'S') {
            cur = 2;
        } else if (str[0] == 'A') {
            cur = 3;
        }

        if (pre == 3 || cur == 3 || (cur == 1 && pre == 2)) {
            inputSynonymWords(root);
            cnt = 0, pre = cur;
        }
        int len = (int) str.length();
        for (int i = 5; i < len && cnt < 50; ++i) {
            cnt++;
            arr[cnt].txt = "";
            arr[cnt].key = 0;
            while (i < len && str[i] != ' ') {
                if ('A' <= str[i] && str[i] <= 'Z') {
                    str[i] = str[i] - 'A' + 'a';
                }
                arr[cnt].txt = arr[cnt].txt + str[i];
                arr[cnt].key = (1LL*arr[cnt].key * Base + (int) str[i++]) % oo;
            }
        }
    }

    fsy.close();
}

vector<string> Synonym::getSynonym(string str) {
    vector<string> res;
    lld hashKey = 0;
    for (int i = 0; i < (int) str.length(); ++i) {
        if ('A' <= str[i] && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
        hashKey = (1LL*hashKey * Base + str[i]) % oo;
    }
    synNode* ans;
    root->Search(root, hashKey, ans);
    if (ans) {
        for (int i = 1; i < ans->synonym; ++i) {
            synNode* syn;
            root->Search(root, ans->val[i], syn);
            res.push_back(syn->wrd);
        }
    }
    return res;
}

