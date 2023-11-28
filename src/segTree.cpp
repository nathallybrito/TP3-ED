//------------------------------------------------------------------------------------------------------
// Arquivo	: segTree.cpp
// Conteudo	: Implementação  da árvore de segmentação e dos métodos de manipulação da matriz linear
// Autor	: Náthally Fernandes. (nathallyfernandes@ufmg.br)
//------------------------------------------------------------------------------------------------------
#include "../include/segTree.hpp"

segTree :: segTree(int n){
    maxNodes = 4 * n; //Inicializa o número máximo de nós na árvore 
    Tree = new Matrix[maxNodes]; // Aloca memória para a árvore e para as transformações 
    transforms = new Matrix[n];
     Matrix identity;// Cria uma matriz identidade para as transformações 
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
             // Cálculo do produto e módulo para cada elemento da matriz resultante
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
        // Multiplica as transformações dos filhos para construir o nó atual
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
        // Atualiza o nó atual multiplicando os valores dos filhos
        Tree[node] = multiply(Tree[2 * node], Tree[2 * node + 1]);
    }
 }
Matrix segTree :: query(int node, int start, int end, int left, int right) {
    if (right < start || left > end || left > right) {
    // Se o intervalo estiver fora da consulta, retorna a matriz identidade
        Matrix res;
        res.mat[0][0] = res.mat[1][1] = 1;
        res.mat[0][1] = res.mat[1][0] = 0;
        return res;
    }
    if (left <= start && right >= end) {
        return Tree[node];
    }
    int mid = (start + end) / 2;
    // Realiza a consulta nos filhos e multiplica os resultados
    Matrix leftChild = query(2 * node, start, mid, left, right);
    Matrix rightChild = query(2 * node + 1, mid + 1, end, left, right);
    return multiply(leftChild, rightChild);
}