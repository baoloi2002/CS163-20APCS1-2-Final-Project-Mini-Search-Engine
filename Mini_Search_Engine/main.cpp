/*
CS163
*/
#include <iostream>
#include "Intro.h" /// Intro
#include "Header.h" /// Header
#include "dataQuery.h" ///  Trie + hashTable
#include "readQuery.h" /// dataQuery + WordToWord + SetConsoleCursorPosition
#include "SetConsoleCursorPosition.h" /// ...
#include "WordToWord.h" /// file
#include "removeStopWords.h" /// Trie
#include "typeOfQuestion.h" /// ???
#include "Synonym.h" /// ???
#include "MainDataBuild.h"

using namespace std;

dataQuery dtQuery;
WTWSuggest wtwSuggest;
StopWords stWords;
Synonym synData;
MainDataBuild mainData;


int main(){

    /// MAIN

    RunIntro();
    string s = "";
    string query;
    gotoXY(0, 23);
    cout << "Result: " << ".......";
    do{
        s = readQuery(s);
        gotoXY(8, 23);
        cout << "                                                                                                ";
        gotoXY(8, 23);
        query = stWords.removeStopWords(s);
        cout << query << endl;
        int context = typeOfQuestion(query);
        if (context == 13){
            mainData.NormalFind(query);
        }
    }while(true);



    return 0;
}
