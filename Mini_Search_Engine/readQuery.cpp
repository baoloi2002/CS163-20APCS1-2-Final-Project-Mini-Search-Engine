#include "readQuery.h"

string readQuery(string s){
    /// Top Left corner
    const int X = 0;
    const int Y = 0;

    const string whiteSpaces = "                                                                                        ";

    gotoXY(X, Y);
    cout << "Google : ";
    gotoXY(X, Y+1);
    cout << "Suggest: ";
    gotoXY(X+9, Y);
    if (s == ""){
        cout << "...........";
        gotoXY(X+9, Y);
    }else
        cout << s;
    do{
        char u = getch();
        if (isEnter(u)){
            break;
        }else
        if (isBackspace(u)){
            if (!s.empty())
                s.pop_back();
        }else{
            s.pb(u);
        }

        /// Suggest
        for (int i=0; i<5; ++i){
            gotoXY(X+9, Y+i+1);
            cout << whiteSpaces;
        }
        if (s.back() != ' ' && !s.empty()){
            vector<string> suggest = fromCharsToWord(getLastChars(s));
            for (int i=0, ii=suggest.size(); i<ii; ++i){
                gotoXY(X+9, Y+i+1);
                cout << suggest[i];
            }
        }

        gotoXY(X+9, Y);
        cout << whiteSpaces;
        gotoXY(X+9, Y);
        cout << s;
    }while(true);

    /// add to Query data
    dtQuery.addData(s);

    return s;
}

vector<string> fromCharsToWord(string u){
    vector<string> a = dtQuery.getBestResult(u);
    return a;
}

string getLastChars(string u){
    string s = "";
    while(!u.empty() && !isSplitChar(u.back())){
        s.pb(u.back());
        u.pop_back();
    }
    reverse(s.begin(), s.end());
    return s;
}

bool isSplitChar(char u){
    vector<char> a = {' ', ',', '.', ';', ':', '?', '!'};
    for (int i=0, ii=a.size(); i<ii; ++i)
        if (a[i] == u)
        return true;
    return false;
}

bool isEnter(char u){
    return int(u) == 13;
}

bool isBackspace(char u){
    return int(u) == 8;
}

