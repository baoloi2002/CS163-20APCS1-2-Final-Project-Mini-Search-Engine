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
    gotoXY(0, 23);
    cout << "Result: " << ".......";
    do{
        s = readQuery(s);
        gotoXY(8, 23);
        for (int i=0; i<50; ++i)
            cout << "                                                                                                                                                ";
        gotoXY(8, 23);
        cout << endl;
        int context = typeOfQuestion(s);
        if (context == 1){
            mainData.AndFind(s);
        }else
        if (context == 2){
            mainData.OrFind(s);
        }else
        if (context == 3){
            mainData.MinusFind(s);
        }else
        if (context == 4){
            mainData.IntitleFind(s);
        }else
        if (context == 5){
            mainData.PlusFind(s);
        }else
        if (context == 6){
            mainData.FileTypeFind(s);
        }else
        if (context == 7){
            mainData.PriceFind(s);
        }else
        if (context == 8){
            mainData.HashTagFind(s);
        }else
        if (context == 9 || context == 10){
            mainData.WildcardFind(s);
        }else
        if (context == 11){
            mainData.RangPriceFind(s);
        }else
        if (context == 12){
            mainData.SynonymFind(s);
        }else
        if (context == 13){
            mainData.NormalFind(s);
        }
    }while(true);



    return 0;
}
