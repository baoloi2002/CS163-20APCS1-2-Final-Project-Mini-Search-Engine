/*
CS163
*/
#include <iostream>
#include "dataQuery.h"
#include "readQuery.h"
#include "Header.h"

using namespace std;

dataQuery dtQuery;
WTWSuggest wtwSuggest;

int main()
{
    string s = "";
    gotoXY(0, 7);
    cout << "Result: " << ".......";
    do{
        s = readQuery(s);
        gotoXY(8, 7);
        cout << "                                                ";
        gotoXY(8, 7);
        cout << s << endl;
    }while(true);

    return 0;
}
