#ifndef _AVLinAVL_
#define _AVLinAVL_

#define fi first
#define se second

#define pb push_back
#define mp make_pair

#include "AvlTree.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class avl2Node{
    int val, height;
    AvlTree dp;
    avl2Node* left,* right;
public:
    avl2Node(){
        left = right = nullptr;
    }
    avl2Node(int x, int id){
        val = x;
        height = 1;
        dp.insertData(id);
        left = right = nullptr;
    };
friend class AAvlTree;
};

class AAvlTree{
    avl2Node* root = nullptr;
public:
    AAvlTree(){
        root = nullptr;
    }
    avl2Node* leftRot(avl2Node* root);
    avl2Node* rightRot(avl2Node* root);
    avl2Node* insertNode(avl2Node* root, int x, int id);
    void printToFileInOrder(avl2Node* root, ofstream& fo);
    int getHeight(avl2Node* root);
    int getBalance(avl2Node* root);
    void insertData(int u, int id);
    vector<pair<int,int> > getList(int L, int R);
    vector<pair<int,int> > mergeRes(vector<pair<int,int> > u, vector<pair<int,int> > v);
    void getLR(avl2Node* root, int L, int R, vector<pair<int,int> >& res);
};

#endif // _AVLinAVL_
