#include "AVL_in_AVL.h"

avl2Node* AAvlTree::leftRot(avl2Node* root){
    avl2Node* a = root,* b = root->right;
    avl2Node* tmp = b->left;
    b->left = a;
    a->right = tmp;
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;
    return b;
}

avl2Node* AAvlTree::rightRot(avl2Node* root){
    avl2Node* a = root,* b = root->left;
    avl2Node* tmp = b->right;
    b->right = a;
    a->left = tmp;
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;
    return b;
}

avl2Node* AAvlTree::insertNode(avl2Node* root, int x, int id){
    if (root == nullptr){
        root = new avl2Node(x, id);
        return root;
    }
    if (x == root->val){
        root->dp.insertData(id);
        return root;
    }
    else
    if (x > root->val)
        root->right = insertNode(root->right, x, id);
    else
    if (x < root->val)
        root->left = insertNode(root->left, x, id);
    else
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int Balance = getBalance(root);
    if (Balance > 1){
        if (x < root->left->val)
            root = rightRot(root);
        else{
            root->left = leftRot(root->left);
            root = rightRot(root);
        }
    }else
    if (Balance < -1){
        if (x > root->right->val)
            root = leftRot(root);
        else{
            root->right = rightRot(root->right);
            root = leftRot(root);
        }
    }

    return root;
}

void AAvlTree::printToFileInOrder(avl2Node* root, ofstream& fo){
    if (root == nullptr) return;
    printToFileInOrder(root->left, fo);
    fo << root->val << ' ';
    printToFileInOrder(root->right, fo);
}

int AAvlTree::getHeight(avl2Node* root){
    if (root == nullptr) return 0;
    return root->height;
}

int AAvlTree::getBalance(avl2Node* root){
    return getHeight(root->left) - getHeight(root->right);
}


void AAvlTree::insertData(int u, int id){
    root = insertNode(root, u, id);
}

vector<pair<int,int> > AAvlTree::getList(int L, int R){
    vector<pair<int, int> > res;
    getLR(root, L, R, res);
    return res;
}

void AAvlTree::getLR(avl2Node* root, int L, int R, vector<pair<int,int> >& res){
    if (root == nullptr) return;
    if (root->val >= L)
        getLR(root->left, L, R, res);
    if (root->val <= R)
        getLR(root->right, L, R, res);
    if (L<= root->val && root->val <=R){
        res = mergeRes(res, root->dp.getList());
    }
}



vector<pair<int,int> > AAvlTree::mergeRes(vector<pair<int,int> > u, vector<pair<int,int> > v){
    sort(u.begin(), u.end());
    sort(v.begin(), v.end());
    int i=0, j=0, n = u.size(), m = v.size();
    vector<pair<int,int> > res;
    while(i<n || j<m){
        if (i == n){
            res.pb(v[j]);
            ++j;
        }else
        if (j == m){
            res.pb(u[i]);
            ++i;
        }else
        if (u[i].fi < v[j].fi){
            res.pb(u[i]);
            ++i;
        }else
        if (u[i].fi > v[j].fi){
            res.pb(v[j]);
            ++j;
        }else{
            res.pb(mp(u[i].fi, u[i].se + v[j].se));
            ++i, ++j;
        }
    }
    return res;
}
