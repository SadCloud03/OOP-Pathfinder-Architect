#include "clase_CalculadoraDeRutas_BFS.h"
#include "../functions/extra_functions.h"

#include <cmath>
#include <iostream>


using namespace std;

CalculadoraDeRutas_BFS::CalculadoraDeRutas_BFS(int filas_mapa, int columnas_mapa) {
    filas = filas_mapa;
    columnas = columnas_mapa;
};

bool CalculadoraDeRutas_BFS::compararNodes::operator()(const Node* a, const Node* b) const {
    return a->f > b->f;
};

CalculadoraDeRutas_BFS::Node* CalculadoraDeRutas_BFS::crearNode(int fila, int columna, int g, int h, int f) {
    Node* nuevoNode = new Node{fila, columna, g, h, f, nullptr};
    return nuevoNode;
};

int CalculadoraDeRutas_BFS::heuristica_manhattan(int fila_inicio, int columna_inicio, int fila_fin, int columna_fin) {
    return abs(fila_fin - fila_inicio) + abs(columna_fin - columna_inicio);
};

void CalculadoraDeRutas_BFS::resolver_A(int** matriz, int fila_inicio, int columna_inicio, int fila_fin, int columna_fin) {
        
    //Abrir la lista Open list
    priority_queue<Node*, vector<Node*>, compararNodes> open_list;
        
    //Abrir la lista cerrada
    bool** cerrado = new bool*[filas];
    for (int i=0; i<filas; i++) {
        cerrado[i] = new bool[columnas];
        for (int j=0; j<columnas; j++) {
            cerrado[i][j] = false;
        };
    };
    
    //lista para poder comparar las g:
    int** mejor_g = new int*[filas];
    for (int i=0; i<filas; i++) {
        mejor_g[i] = new int[columnas];
        for (int j=0; j<columnas; j++) {
            mejor_g[i][j] = 999999; //numero muy grande para comenzar
        };
    };
    
    
    mejor_g[fila_inicio][columna_inicio] = 0;
    
    //direcciones para el algoritmo;
    int nueva_fila[4] = {1, -1, 0, 0};
    int nueva_columna[4] = {0, 0, 1, -1};
    int g = 0;
    int h = heuristica_manhattan(fila_inicio, columna_inicio, fila_fin, columna_fin);
    int f = g + h;
    
    Node* comienzo = crearNode(fila_inicio, columna_inicio, g, h, f);
    open_list.push(comienzo);
    Node* objetivo = NULL;
    
    while (!open_list.empty()) {
        Node* actual = open_list.top();
        open_list.pop();
        
        if (actual->fila == fila_fin && actual->columna == columna_fin) {
            objetivo = actual;
            break;
        };
        
        if (cerrado[actual->fila][actual->columna]) {
            continue;
        }
        
        cerrado[actual->fila][actual->columna] = true;
        
        for (int i=0; i<4; i++) {					
            int nf = actual->fila + nueva_fila[i];
            int nc = actual->columna + nueva_columna[i];
            if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas && !(matriz[nf][nc] == 10) && !cerrado[nf][nc])  {
                
                int g_n = actual->g + matriz[nf][nc];
                
                if (g_n < mejor_g[nf][nc]) {
                    mejor_g[nf][nc] = g_n;
                    
                    int h_n = heuristica_manhattan(nf, nc, fila_fin, columna_fin);
                    int f_n = g_n + h_n;
                    
                    Node* hijo = crearNode(nf, nc, g_n, h_n, f_n);
                    hijo->padre = actual;	
                    open_list.push(hijo);
                };
            };
        };
    };

    
    if (objetivo == NULL) {
        cout<<"\nno existe camino. \n";
        return;
    }
    
    
    Node* recorrer = objetivo;
    while (recorrer != NULL) {
        system("clear");
        matriz[recorrer->fila][recorrer->columna] = 2;
        recorrer = recorrer->padre;
        mostrar_mapas(matriz, filas, columnas);
        // _sleep(120); windows
    };
    cout<<"\nCamino encontrado. \n";
    
    
        
    //limpiar memoria de cerrado:
    for (int i = 0; i < filas; i++) {
        delete[] cerrado[i];
    };
    delete[] cerrado;
    
    
    
    //limpiar memoria de mejor_g:
    for (int i = 0; i < filas; i++) {
        delete[] mejor_g[i];
    };
    delete[] mejor_g;
};		
