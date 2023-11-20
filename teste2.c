#include <stdio.h>

#define MOD 100000000

typedef struct {
    long long int m[2][2];
} Matrix;

typedef struct {
    Matrix val;
    int lazy;
} Node;

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
    if (tree[current].lazy != 0) {
        Matrix lazyMatrix;
        lazyMatrix.m[0][0] = 1;
        lazyMatrix.m[0][1] = 0;
        lazyMatrix.m[1][0] = 0;
        lazyMatrix.m[1][1] = 1;

        for (int i = 0; i < tree[current].lazy; ++i) {
            lazyMatrix = multiply(lazyMatrix, matrix);
        }

        tree[current].val = multiply(tree[current].val, lazyMatrix);

        if (start != end) {
            tree[2 * current + 1].lazy += tree[current].lazy;
            tree[2 * current + 2].lazy += tree[current].lazy;
        }

        tree[current].lazy = 0;
    }

    if (start > right || end < left) {
        return;
    }

    if (start >= left && end <= right) {
        tree[current].val = multiply(tree[current].val, matrix);

        if (start != end) {
            tree[2 * current + 1].lazy += 1;
            tree[2 * current + 2].lazy += 1;
        }

        return;
    }

    int mid = (start + end) / 2;
    update(tree, start, mid, left, right, 2 * current + 1, matrix);
    update(tree, mid + 1, end, left, right, 2 * current + 2, matrix);

    tree[current].val = multiply(tree[2 * current + 1].val, tree[2 * current + 2].val);
}

Matrix query(Node *tree, int start, int end, int left, int right, int current) {
    if (tree[current].lazy != 0) {
        Matrix lazyMatrix;
        lazyMatrix.m[0][0] = 1;
        lazyMatrix.m[0][1] = 0;
        lazyMatrix.m[1][0] = 0;
        lazyMatrix.m[1][1] = 1;

        for (int i = 0; i < tree[current].lazy; ++i) {
            lazyMatrix = multiply(lazyMatrix, tree[current].val);
        }

        tree[current].val = multiply(tree[current].val, lazyMatrix);

        if (start != end) {
            tree[2 * current + 1].lazy += tree[current].lazy;
            tree[2 * current + 2].lazy += tree[current].lazy;
        }

        tree[current].lazy = 0;
    }

    if (start > right || end < left) {
        Matrix identity;
        identity.m[0][0] = 1;
        identity.m[0][1] = 0;
        identity.m[1][0] = 0;
        identity.m[1][1] = 1;
        return identity;
    }

    if (start >= left && end <= right) {
        return tree[current].val;
    }

    int mid = (start + end) / 2;
    Matrix leftResult = query(tree, start, mid, left, right, 2 * current + 1);
    Matrix rightResult = query(tree, mid + 1, end, left, right, 2 * current + 2);

    return multiply(leftResult, rightResult);
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    Matrix *matrices = malloc(n * sizeof(Matrix));
    Node *tree = malloc(4 * n * sizeof(Node)); // Assuming a complete binary tree

    for (int i = 0; i < n; ++i) {
        matrices[i].m[0][0] = 1;
        matrices[i].m[0][1] = 0;
        matrices[i].m[1][0] = 0;
        matrices[i].m[1][1] = 1;
    }

    build(tree, matrices, 0, n - 1, 0);

    for (int i = 0; i < q; ++i) {
        char operation;
        scanf(" %c", &operation);

        if (operation == 'u') {
            int time;
            scanf("%d", &time);

            Matrix newMatrix;
            scanf("%lld %lld %lld %lld", &newMatrix.m[0][0], &newMatrix.m[0][1], &newMatrix.m[1][0], &newMatrix.m[1][1]);

            update(tree, 0, n - 1, time - 1, time - 1, 0, newMatrix);
        } else if (operation == 'q') {
            int t0, td, x, y;
            scanf("%d %d %d %d", &t0, &td, &x, &y);

            Matrix result = query(tree, 0, n - 1, t0 - 1, td - 1, 0);
            long long int newX = (result.m[0][0] * x + result.m[0][1] * y) % MOD;
            long long int newY = (result.m[1][0] * x + result.m[1][1] * y) % MOD;

            printf("%lld %lld\n", newX, newY);
        }
    }

    free(matrices);
    free(tree);

    return 0;
}