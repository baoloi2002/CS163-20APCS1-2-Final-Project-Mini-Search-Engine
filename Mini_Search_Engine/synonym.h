#ifndef _SYNONYM_
#define _SYNONYM_
#include <list>

#include <iostream>

using namespace std;

class Synonym{
    const int Nmax = 1000003;
    const int base = 259;
    string* key;
    list<string>* syn,* ant;
    Synonym(){
        key = new string[Nmax];
        for (int i=0; i<Nmax; ++i){
            key[i] = "";
        }
        syn = new list<string>;
        ant = new list<string>;
        loadData();
    }
public:
    int getKey(string u);
    void addSyn(string u);
    void addAnt(string u);
    list<string> getSyn(string u);
    list<string> getAnt(string u);
    void loadData();
};

#endif // _SYNONYM_

