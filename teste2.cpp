#include <iostream>

using namespace std;

const int MAX_N = 100005; // Tamanho máximo da árvore de segmentação e dos pontos

struct Matrix {
    int mat[2][2]; // Matriz 2x2
    //Matrix point = { {{x, 0}, {y, 0}} }; // Exemplo de inicialização de uma matriz 2x2
};

Matrix segTree[MAX_N * 4]; // Árvore de segmentação
Matrix* transforms; // Matrizes das transformações (alocação dinâmica)

// Função para multiplicar duas matrizes
Matrix multiply(const Matrix &a, const Matrix &b) {
    Matrix res;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            res.mat[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                res.mat[i][j] += (a.mat[i][k] * b.mat[k][j]) % 100000000;
                res.mat[i][j] %= 100000000;
            }
        }
    }
    return res;
}

// Função para construir a árvore de segmentação
void build(int node, int start, int end) {
    if (start == end) {
        segTree[node] = transforms[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        segTree[node] = multiply(segTree[2 * node], segTree[2 * node + 1]);
    }
}

// Função para atualizar uma transformação
void update(int node, int start, int end, int idx, const Matrix &newValue) {
    if (start == end) {
        segTree[node] = newValue;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, newValue);
        } else {
            update(2 * node + 1, mid + 1, end, idx, newValue);
        }
        segTree[node] = multiply(segTree[2 * node], segTree[2 * node + 1]);
    }
}

// Função para realizar uma consulta
Matrix query(int node, int start, int end, int left, int right) {
    if (right < start || left > end || left > right) {
        Matrix res;
        res.mat[0][0] = res.mat[1][1] = 1;
        res.mat[0][1] = res.mat[1][0] = 0;
        return res;
    }
    if (left <= start && right >= end) {
        return segTree[node];
    }
    int mid = (start + end) / 2;
    Matrix leftChild = query(2 * node, start, mid, left, right);
    Matrix rightChild = query(2 * node + 1, mid + 1, end, left, right);
    return multiply(leftChild, rightChild);
}


int main() {
    int n, q; // n = quantos instantes de tempo, q = quantas operações
    cin >> n >> q;

    // Alocação dinâmica de memória para armazenar as matrizes
    transforms = new Matrix[n];

    int x,y;
    // Processar as operações
    for (int i = 0; i < q; ++i) {
        char op;
        cin >> op;

        if (op == 'u') { // Operação de atualização
            int a;
            cin >> a;
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    cin >> transforms[a].mat[j][k];
                }
            }
            update(1, 0, n - 1, a, transforms[a]); // Atualizar na árvore de segmentação
        } else if (op == 'q') { // Operação de consulta
            int t0, td;
            cin >> t0 >> td ;
            cin >> x >> y;
            Matrix res = query(1, 0, n - 1, t0, td); // Consultar na árvore de segmentação
            Matrix point;
            point.mat[0][0] = x;
            point.mat[0][1] = 0;
            point.mat[1][0] = y;
            point.mat[1][1] = 0;
            Matrix result = multiply(res, point);
            cout << result.mat[0][0] % 100000000 << " " << result.mat[1][0] % 100000000 << "\n";
        }
    }

    // Liberar a memória alocada dinamicamente
    delete[] transforms;

    return 0;
}