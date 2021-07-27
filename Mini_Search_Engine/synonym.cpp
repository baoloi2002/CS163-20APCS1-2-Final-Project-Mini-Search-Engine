#include "synonym.h"

int Synonym::getKey(string u){
    int res = 0;
    for (int i=0, ii=u.size(); i<ii; ++i){
        res = (res*base + int(u[i])) % Nmax;
    }
    while(key[res] != u && key[res] != ""){
        res = (res + 1) % Nmax;
    }
    if (key[res] == "")
        key[res] = u;
    return res;
}

void Synonym::addSyn(string u){

}

void Synonym::addAnt(string u){

}

list<string> Synonym::getSyn(string u){

}

list<string> Synonym::getAnt(string u){

}

void Synonym::loadData(){

}
