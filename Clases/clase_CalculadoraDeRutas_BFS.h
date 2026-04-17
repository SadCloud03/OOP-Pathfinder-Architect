#ifndef CLASE_CALCULADORA_RUTAS_BFS_H
#define CLASE_CALCULADORA_RUTAS_BFS_H

#include <vector>
#include <queue>

class CalculadoraDeRutas_BFS {
private:
	int filas = 11;
	int columnas = 11;
		
public:
    CalculadoraDeRutas_BFS(int filas, int columnas);

    struct Node {
        int fila;
        int columna;
        int g;
        int h;
        int f;
        Node* padre;
    };
    
    struct compararNodes {bool operator()(const Node* a , const Node* b) const;};
    Node* crearNode(int fila, int columna, int g, int h, int f);
    int heuristica_manhattan(int fila_inicio, int columna_inicio, int fila_fin, int columna_fin);
void resolver_A(int** matriz, int fila_inicio, int columna_inicio, int fila_fin, int columna_fin);
};

#endif