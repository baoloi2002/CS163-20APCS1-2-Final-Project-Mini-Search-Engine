#ifndef _AvlTree_
#define _AvlTree_

#define mp make_pair
#define pb push_back

#include <fstream>
#include <vector>

using namespace std;

class avlNode{
    int val, height, cnt;
    avlNode* left,* right;
public:
    avlNode(){
        left = right = nullptr;
    }
    avlNode(int x){
        val = x;
        height = 1;
        cnt = 1;
        left = right = nullptr;
    };
friend class AvlTree;
};

class AvlTree{
    avlNode* root = nullptr;
public:
    AvlTree(){
        root = nullptr;
    }
    avlNode* leftRot(avlNode* root);
    avlNode* rightRot(avlNode* root);
    avlNode* insertNode(avlNode* root, int x);
    void printToFileInOrder(avlNode* root, ofstream& fo);
    int getHeight(avlNode* root);
    int getBalance(avlNode* root);
    void insertData(int u);
    void loadAllTree(avlNode* root, vector<pair<int, int> >& res);
    vector<pair<int,int> > getList();

};


#endif // _AvlTree_
