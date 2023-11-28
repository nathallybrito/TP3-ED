//------------------------------------------------------------------------------------------------------
// Arquivo	: main.cppp
// Conteudo	: Imolementação do programa principal.
// Autor	: Náthally Fernandes. (nathallyfernandes@ufmg.br)
//------------------------------------------------------------------------------------------------------
#include "../include/segTree.hpp"

int main() {
    int n, q;
    cin >> n >> q;

    if (n <= 0 || q <= 0) {
        cout << "Erro: Número de elementos ou consultas deve ser maior que zero." << endl;
        return 1; // Sai do programa com código de erro
    }

    segTree tree(n);
    tree.build(1, 0, n - 1); // Constrói a árvore de segmentação com base nos 'n' elementos

    int x = 0, y = 0;

    // Processa as operações 
    for (int i = 0; i < q; ++i) {
        char op;
        cin >> op;

        if (op == 'u') {
            int a;
            cin >> a;
            if (a < 0 || a >= n) {
                cout << "Erro: Índice de atualização inválido." << endl;
                return 1; // Sai do programa com código de erro
            }
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    cin >> tree.transforms[a].mat[j][k];
                }
            }
            tree.update(1, 0, n - 1, a, tree.transforms[a]);
        } else if (op == 'q') {
            int t0, td;
            cin >> t0 >> td;
            if (t0 < 0 || td >= n || t0 > td) {
                cout << "Erro: Intervalo de consulta inválido." << endl;
                return 1; // Sai do programa com código de erro
            }
            cin >> x >> y;
            Matrix res = tree.query(1, 0, n - 1, t0, td);// Realiza a consulta na árvore
            Matrix point;
            point.mat[0][0] = x;
            point.mat[0][1] = 0;
            point.mat[1][0] = y;
            point.mat[1][1] = 1;
            Matrix result = tree.multiply(res, point); // Realiza a consulta na árvore
            cout << result.mat[0][0] % MOD << " " << result.mat[1][0] % MOD << "\n";
        }   else {
            cout << "Erro: Operação inválida." << endl;
            return 1; // Sai do programa com código de erro
        }
    }

    return 0;
}
