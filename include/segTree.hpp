//------------------------------------------------------------------------------------------------------
// Arquivo	: segTree.hpp
// Conteudo	: Definições da árvore de segmentação e dos métodos de manipulação da matriz linear
// Autor	: Náthally Fernandes. (nathallyfernandes@ufmg.br)
//------------------------------------------------------------------------------------------------------
#include <iostream>

#define MOD 100000000

using namespace std;

//Srtruct que inicia a matrix 2 x 2
struct Matrix {
    int mat[2][2]; 
};

class segTree {
private:
Matrix* Tree; // Árvore de segmentação

int maxNodes; // Número máximo de nós na árvore

public:
Matrix* transforms; // Matriz de transformação, alocada dinamicamente

// Definição: Construtor da classe segTree
// Entrada: n (número de elementos)
// Saída: Inicializa a árvore de segmentação e aloca memória para as transformações
segTree(int n);


// Definição: Destrutor da classe segTree.
// Entrada: Não tem entrada definida.
// Saída: Libera a memória alocada para a árvore e as transformações.
~segTree();

// Definição: Função para multiplicar duas matrizes
// Entrada: Duas matrizes 'a' e 'b' a serem multiplicadas
// Saída: Retorna o produto das duas matrizes
Matrix multiply(const Matrix &a, const Matrix &b);


// Definição: Função para construir a árvore de segmentação
// Entrada: Nó atual, início e fim do intervalo a ser processado
// Saída: Constroi a árvore de segmentação com as transformações aplicadas
void build(int node, int start, int end);


// Definição: Função para atualizar uma transformação na árvore
// Entrada: Nó atual, início e fim do intervalo, índice da transformação e novo valor
// Saída: Atualiza uma transformação na árvore com um novo valor
void update(int node, int start, int end, int idx, const Matrix &newValue);
    

 // Definição: Função para realizar uma consulta na árvore de segmentação
// Entrada: Nó atual, início e fim do intervalo de consulta
// Saída: Retorna a matriz resultante da consulta no intervalo especificado
Matrix query(int node, int start, int end, int left, int right);

};

