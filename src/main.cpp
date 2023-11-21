#include "../include/segTree.hpp"

int main() {
    int n, q;
    cin >> n >> q;

    // Allocate memory for transforms
    Matrix* transforms = new Matrix[n];

    // Create an instance of segTree
    segTree tree(n);
    tree.build(1, 0, n - 1);

    int x, y;
    // Process operations
    for (int i = 0; i < q; ++i) {
        char op;
        cin >> op;

        if (op == 'u') {
            int a;
            cin >> a;
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    cin >> transforms[a].mat[j][k];
                }
            }
            tree.update(1, 0, n - 1, a, transforms[a]);
        } else if (op == 'q') {
            int t0, td;
            cin >> t0 >> td;
            cin >> x >> y;
            Matrix res = tree.query(1, 0, n - 1, t0, td);
            Matrix point;
            point.mat[0][0] = x;
            point.mat[0][1] = 0;
            point.mat[1][0] = y;
            point.mat[1][1] = 0;
            Matrix result = tree.multiply(res, point);
            cout << result.mat[0][0] % 100000000 << " " << result.mat[1][0] % 100000000 << "\n";
        }
    }

    delete[] transforms;
    return 0;
}
