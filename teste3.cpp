#include <iostream>
using namespace std;

#define MOD 100000000

struct Matrix {
    long long int m[2][2];
};

struct Node {
    Matrix val;
    int lazy;
};

Matrix multiply(Matrix a, Matrix b) {
    Matrix result;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                result.m[i][j] += (a.m[i][k] * b.m[k][j]) % MOD;
                result.m[i][j] %= MOD;
            }
        }
    }
    return result;
}

void build(Node *tree, Matrix *arr, int start, int end, int current) {
    if (start == end) {
        tree[current].val = arr[start];
        tree[current].lazy = 0;
        return;
    }

    int mid = (start + end) / 2;
    build(tree, arr, start, mid, 2 * current + 1);
    build(tree, arr, mid + 1, end, 2 * current + 2);

    tree[current].val = multiply(tree[2 * current + 1].val, tree[2 * current + 2].val);
    tree[current].lazy = 0;
}

void update(Node *tree, int start, int end, int left, int right, int current, Matrix matrix) {
    if (left > end || right < start) {
        return;
    }

    if (start == end) {
        tree[current].val = matrix;
        return;
    }

    int mid = (start + end) / 2;
    int left_node = 2 * current + 1;
    int right_node = 2 * current + 2;

    update(tree, start, mid, left, right, left_node, matrix);
    update(tree, mid + 1, end, left, right, right_node, matrix);

    tree[current].val = multiply(tree[left_node].val, tree[right_node].val);
}

Matrix query(Node *tree, int start, int end, int query_start, int query_end, int current) {
    Matrix nullMatrix;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            nullMatrix.m[i][j] = 0;
        }
    }

    if (query_start > end || query_end < start) {
        return nullMatrix;
    }

    if (start >= query_start && end <= query_end) {
        return tree[current].val;
    }

    int mid = (start + end) / 2;
    int left_node = 2 * current + 1;
    int right_node = 2 * current + 2;

    Matrix left_result = query(tree, start, mid, query_start, query_end, left_node);
    Matrix right_result = query(tree, mid + 1, end, query_start, query_end, right_node);

    if (left_result.m[0][0] == -1 || right_result.m[0][0] == -1) {
        return nullMatrix;
    }

    return multiply(left_result, right_result);
}

int main() {
    int n, q;
    cin >> n >> q;

    Matrix *matrices = new Matrix[n];
    Node *tree = new Node[4 * n]; // Assuming a complete binary tree

    for (int i = 0; i < n; ++i) {
        matrices[i].m[0][0] = 1;
        matrices[i].m[0][1] = 0;
        matrices[i].m[1][0] = 0;
        matrices[i].m[1][1] = 1;
    }

    build(tree, matrices, 0, n - 1, 0);

    for (int i = 0; i < q; ++i) {
        char operation;
        cin >> operation;

        if (operation == 'u') {
            int time;
            cin >> time;

            Matrix newMatrix;
            cin >> newMatrix.m[0][0] >> newMatrix.m[0][1] >> newMatrix.m[1][0] >> newMatrix.m[1][1];

            update(tree, 0, n - 1, time - 1, time - 1, 0, newMatrix);
        } else if (operation == 'q') {
            int t0, td, x, y;
            cin >> t0 >> td >> x >> y;

            Matrix result = query(tree, 0, n - 1, t0 - 1, td - 1, 0);
            long long int newX = (result.m[0][0] * x + result.m[0][1] * y) % MOD;
            long long int newY = (result.m[1][0] * x + result.m[1][1] * y) % MOD;

            cout << newX << " " << newY << endl;
        }
    }

    delete[] matrices;
    delete[] tree;

    return 0;
}
