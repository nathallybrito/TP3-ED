#include "../include/segTree.hpp"

segTree :: segTree(int n){
    maxNodes = 4 * n;
    Tree = new Matrix[maxNodes];
    transforms = new Matrix[n];
     Matrix identity;
    identity.mat[0][0] = identity.mat[1][1] = 1;
    identity.mat[0][1] = identity.mat[1][0] = 0;

    for (int i = 0; i < n; ++i) {
    transforms[i] = identity;
    }

}
segTree::~segTree(){
    delete[] Tree;
    delete[] transforms;
}

 Matrix segTree :: multiply(const Matrix &a, const Matrix &b){
    Matrix res;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            res.mat[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                res.mat[i][j] += (static_cast<long long>(a.mat[i][k]) * b.mat[k][j]) % MOD;
                res.mat[i][j] %= MOD;
            }
        }
    }
    return res;
}
 void segTree :: build(int node, int start, int end) {
    if (start == end) {
        Tree[node] = transforms[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        Tree[node] = multiply(Tree[2 * node], Tree[2 * node + 1]);
    }
}
 void segTree :: update(int node, int start, int end, int idx, const Matrix &newValue){
    if (start == end) {
        Tree[node] = newValue;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, newValue);
        } else {
            update(2 * node + 1, mid + 1, end, idx, newValue);
        }
        Tree[node] = multiply(Tree[2 * node], Tree[2 * node + 1]);
    }
 }
Matrix segTree :: query(int node, int start, int end, int left, int right) {
    if (right < start || left > end || left > right) {
        Matrix res;
        res.mat[0][0] = res.mat[1][1] = 1;
        res.mat[0][1] = res.mat[1][0] = 0;
        return res;
    }
    if (left <= start && right >= end) {
        return Tree[node];
    }
    int mid = (start + end) / 2;
    Matrix leftChild = query(2 * node, start, mid, left, right);
    Matrix rightChild = query(2 * node + 1, mid + 1, end, left, right);
    return multiply(leftChild, rightChild);
}