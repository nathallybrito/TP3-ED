#include <iostream>

#define MOD 100000000

using namespace std;

//const int MAX_N = 100005; // Tamanho máximo da árvore de segmentação e dos pontos

struct Matrix {
    int mat[2][2]; // Matriz 2x2
};

class segTree {
private:
Matrix* Tree; // Árvore de segmentação
Matrix* transforms; // Matrizes das transformações (alocação dinâmica)
int maxNodes;
public:
segTree(int n);

~segTree();

// Função para multiplicar duas matrizes
Matrix multiply(const Matrix &a, const Matrix &b);

// Função para construir a árvore de segmentação
void build(int node, int start, int end);

// Função para atualizar uma transformação
void update(int node, int start, int end, int idx, const Matrix &newValue);
    

// Função para realizar uma consulta
Matrix query(int node, int start, int end, int left, int right);

};

