#include <iostream>

#define MOD 100000000

using namespace std;

struct Matrix {
    long long int m[2][2];
    bool isEmpty; // Novo campo para verificar se a matriz está vazia ou não

    Matrix() : isEmpty(true) {} // Construtor padrão inicializa a matriz como vazia
};

class SegTree {
private:
    Matrix *tree;
    Matrix *lazy;

    Matrix merge(Matrix matrix_a, Matrix matrix_b) {
        // Implementar a multiplicação de matrizes 2x2 para aplicar as transformações
        // Essa função deve retornar a matriz resultante da multiplicação
        Matrix result;
        // Implementação da multiplicação de matrizes
        return result;
    }

   void propagate(int node, int start, int end) {
    if (lazy[node].m[0][0] == 1 && lazy[node].m[0][1] == 0 &&
        lazy[node].m[1][0] == 0 && lazy[node].m[1][1] == 1) {
        return;
    }

    if (start != end) {
        lazy[2 * node + 1] = merge(lazy[2 * node + 1], lazy[node]);
        lazy[2 * node + 2] = merge(lazy[2 * node + 2], lazy[node]);
    }

    tree[node] = merge(tree[node], lazy[node]);

    // Reset lazy node flag after applying updates
    lazy[node].m[0][0] = 1;
    lazy[node].m[0][1] = 0;
    lazy[node].m[1][0] = 0;
    lazy[node].m[1][1] = 1;

    // Set flag indicating the node is not empty anymore
    tree[node].isEmpty = false;
}


public:
    SegTree(int n) {
        tree = new Matrix[4 * n];  // Usando arrays para representar a árvore de segmentação
        lazy = new Matrix[4 * n];  // Array para operações preguiçosas
    }

  void update(int node, int start, int end, int idx, Matrix matrix) {
    if (idx < start || idx > end || start > end) {
        return;
    }

    if (start == end) {
        tree[node] = matrix;
        return;
    }

    int mid = (start + end) / 2;
    int left_node = 2 * node + 1;
    int right_node = 2 * node + 2;

    update(left_node, start, mid, idx, matrix);
    update(right_node, mid + 1, end, idx, matrix);

    tree[node] = merge(tree[left_node], tree[right_node]);
}
Matrix query(int node, int start, int end, int query_start, int query_end) {
    if (start > end || start > query_end || end < query_start) {
        Matrix nullMatrix;
        nullMatrix.isEmpty = true;
        return nullMatrix;
    }

    if (lazy[node].m[0][0] != 1 || lazy[node].m[0][1] != 0 ||
        lazy[node].m[1][0] != 0 || lazy[node].m[1][1] != 1) {
        propagate(node, start, end);
    }

    if (start >= query_start && end <= query_end) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    int left_node = 2 * node + 1;
    int right_node = 2 * node + 2;

    Matrix left_result = query(left_node, start, mid, query_start, query_end);
    Matrix right_result = query(right_node, mid + 1, end, query_start, query_end);

    if (left_result.isEmpty) {
        return right_result;
    } else if (right_result.isEmpty) {
        return left_result;
    } else {
        return merge(left_result, right_result);
    }
}

 ~SegTree() {
        delete[] tree;
        delete[] lazy;
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    SegTree segTree(n);

    for (int i = 0; i < q; ++i) {
        char operation;
        cin >> operation;

        if (operation == 'u') {
            int idx;
            Matrix newMatrix;
            cin >> idx >> newMatrix.m[0][0] >> newMatrix.m[0][1] >> newMatrix.m[1][0] >> newMatrix.m[1][1];
            newMatrix.isEmpty = false;
            segTree.update(0, 0, n - 1, idx - 1, newMatrix); // -1 para adequar à indexação base 0
        } else if (operation == 'q') {
            int leftStart, leftEnd, rightStart, rightEnd;
            cin >> leftStart >> leftEnd >> rightStart >> rightEnd;
            Matrix result = segTree.query(0, 0, n - 1, leftStart - 1, rightStart - 1); // -1 para adequar à indexação base 0

            if (result.isEmpty) {
                cout << "Empty matrix" << endl;
            } else {
                // Imprima os valores da matriz resultante conforme necessário
                cout << result.m[0][0] << " " << result.m[0][1] << endl;
                cout << result.m[1][0] << " " << result.m[1][1] << endl;
            }
        }
    }

    return 0;
}
