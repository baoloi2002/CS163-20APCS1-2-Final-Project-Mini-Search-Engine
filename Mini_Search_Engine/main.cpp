/*
CS163
*/
#include <iostream>
#include "Header.h" /// Header
#include "dataQuery.h" ///  Trie + hashTable
#include "readQuery.h" /// dataQuery + WordToWord + SetConsoleCursorPosition
#include "SetConsoleCursorPosition.h" /// ...
#include "WordToWord.h" /// file
#include "removeStopWords.h" /// Trie
#include "typeOfQuestion.h" /// ???
#include "Synonym.h" /// ???

using namespace std;

dataQuery dtQuery;
WTWSuggest wtwSuggest;
StopWords stWords;
Synonym synData;


int main(){

    /// MAIN

    string s = "";
    string query;
    gotoXY(0, 7);
    cout << "Result: " << ".......";
    do{
        s = readQuery(s);
        gotoXY(8, 7);
        cout << "                                                                                                ";
        gotoXY(8, 7);
        query = stWords.removeStopWords(s);
        cout << query << endl;
    }while(true);

    return 0;
}
