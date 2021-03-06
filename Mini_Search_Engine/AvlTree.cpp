#include "AvlTree.h"

avlNode* AvlTree::leftRot(avlNode* root) {
    avlNode* a = root,* b = root->right;
    avlNode* tmp = b->left;
    b->left = a;
    a->right = tmp;
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;
    return b;
}

avlNode* AvlTree::rightRot(avlNode* root) {
    avlNode* a = root,* b = root->left;
    avlNode* tmp = b->right;
    b->right = a;
    a->left = tmp;
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;
    return b;
}

avlNode* AvlTree::insertNode(avlNode* root, int key) {
    if (root == nullptr){
        root = new avlNode(key);
        return root;
    } if (key == root->val){
        ++root->cnt;
        return root;
    } else if (key > root->val)
        root->right = insertNode(root->right, key);
    else if (key < root->val)
        root->left = insertNode(root->left, key);
    else
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    
    //check if the tree is balanced
    int balanceFactor = getBalance(root); 
    if (balanceFactor > 1){     //LL case or LR case
        if (key < root->left->val)    //LL
            root = rightRot(root);
        else {
            root->left = leftRot(root->left);       //LR
            root = rightRot(root);
        }
    } else if (balanceFactor < -1){    //RR case or RL case
        if (key > root->right->val)
            root = leftRot(root);   //RR
        else {
            root->right = rightRot(root->right);    //RL
            root = leftRot(root);
        }
    }

    return root;
}

void AvlTree::printToFileInOrder(avlNode* root, ofstream& fo) {  //L->node->R
    if (root == nullptr) return;
    printToFileInOrder(root->left, fo);
    fo << root->val << ' ';
    printToFileInOrder(root->right, fo);
}

int AvlTree::getHeight(avlNode* root) { 
    if (root == nullptr) return 0;
    return root->height;
}

int AvlTree::getBalance(avlNode* root) {
    return getHeight(root->left) - getHeight(root->right);
}


void AvlTree::insertData(int u){
    root = insertNode(root, u);
}

vector<pair<int,int> > AvlTree::getList() {
    vector<pair<int, int> > res;
    loadAllTree(root, res);
    return res;
}

void AvlTree::loadAllTree(avlNode* root, vector<pair<int, int> > &res) {
    if (root == nullptr) return;
    loadAllTree(root->left, res);
    res.pb(mp(root->val, root->cnt));
    loadAllTree(root->right, res);
}
