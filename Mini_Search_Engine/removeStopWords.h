#ifndef _stopWords_
#define _stopWords_

#define pb push_back

#include <vector>
#include <fstream>

using namespace std;

class swNode{
    const int base = 130;
    swNode** pNext;
    bool isEndOfWord;
    swNode(){
        pNext = new swNode*[base];
        for (int i=0; i<base; ++i)
            pNext[i] = nullptr;
        isEndOfWord = false;
    }
friend class StopWords;
};

class StopWords{
    swNode* root = nullptr;
public:
    StopWords();
    void insertData(string u);
    bool isStopWord(string u);
    string removeStopWords(string u);
    bool isSplitChar(char u);
};

#endif // _stopWords_
