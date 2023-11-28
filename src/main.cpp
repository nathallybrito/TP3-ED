//------------------------------------------------------------------------------------------------------
// Arquivo	: main.cppp
// Conteudo	: Imolementação do programa principal.
// Autor	: Náthally Fernandes. (nathallyfernandes@ufmg.br)
//------------------------------------------------------------------------------------------------------
#include "../include/segTree.hpp"
#include <chrono>

int main() {
    int n, q;
    cin >> n >> q;

    // if (n <= 0 || q <= 0) {
    //     cout << "Erro: Número de elementos ou consultas deve ser maior que zero." << endl;
    //     return 1; // Sai do programa com código de erro
    // }

    segTree tree(n);
    auto start = std::chrono::steady_clock::now(); // Marca o início da contagem de tempo
    tree.build(1, 0, n - 1); // Constrói a árvore de segmentação com base nos 'n' elementos
     auto end = std::chrono::steady_clock::now(); // Marca o fim da contagem de tempo

    // Cálculo do tempo decorrido
    auto diff = end - start;
    std::cout << "Tempo de execução do método build: "
              << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;


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
            auto start_update = std::chrono::steady_clock::now();

            tree.update(1, 0, n - 1, a, tree.transforms[a]);

            auto end_update = std::chrono::steady_clock::now();

             // Calcular a diferença de tempo e imprimir
            auto diff_update = end_update - start_update;

            std::cout << "Tempo de execução do método update: "

            << std::chrono::duration<double, std::milli>(diff_update).count() << " ms" << std::endl;

        } else if (op == 'q') {
            int t0, td;
            cin >> t0 >> td;
            if (t0 < 0 || td >= n || t0 > td) {
                cout << "Erro: Intervalo de consulta inválido." << endl;
                return 1; // Sai do programa com código de erro
            }
            cin >> x >> y;

            // Marcar o início da contagem de tempo antes de chamar o método query
            auto start_query = std::chrono::steady_clock::now();

            Matrix res = tree.query(1, 0, n - 1, t0, td);// Realiza a consulta na árvore

            // Marcar o fim da contagem de tempo após a chamada do método query
            auto end_query = std::chrono::steady_clock::now();

            // Calcular a diferença de tempo e imprimir
            auto diff_query = end_query - start_query;  
            std::cout << "Tempo de execução do método query: "
          << std::chrono::duration<double, std::milli>(diff_query).count() << " ms" << std::endl;

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
