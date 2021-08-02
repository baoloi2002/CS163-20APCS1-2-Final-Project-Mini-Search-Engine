/*
CS163
*/
#include <iostream>
#include "dataQuery.h"
#include "readQuery.h"
#include "Header.h"
#include "removeStopWords.h"
#include "typeOfQuestion.h"

using namespace std;

dataQuery dtQuery;
WTWSuggest wtwSuggest;
StopWords stWords;

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
