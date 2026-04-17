#include "clase_Mapa.h"

#include <iostream>

using namespace std;

Mapa::Mapa(int cant_filas, int cant_columnas) {
    filas = cant_filas;
    columnas = cant_columnas;
    
    matriz = new int*[filas];
    for (int i=0; i<filas; i++) {
        matriz[i] = new int [columnas];
        for (int j=0; j<columnas; j++) {
            matriz[i][j] = 1; //esta vez voy a comenzar todo en camino
            if (i % 2 == 0 && j % 2 == 0) {
                matriz[i][j] = 10; // edificios dentro del mapa 
            };
        };
    };
};

bool Mapa::revisar_casilla_disponible(int fila, int columna, int modo) {
    switch(modo) {
        case 1:
            if (fila < 0 && fila >= filas && columna < 0 && columna >= columnas) {
                cout<<"casilla fuera de la matriz";
                return false;
            };
            if (matriz[fila][columna] != 1) {
                cout<<"la casilla no se encuentra disponible";
                return false;
            };
            return true;
        case 2:
            if (fila < 0 && fila >= filas && columna < 0 && columna >= columnas) {
                cout<<"casilla fuera de la matriz";
                return false;
            };
            return true;
    }
    return false;
};

void Mapa::agregar_obstaculos_al_azar(int cantidad_obstaculos) {
    for (int i=0; i<cantidad_obstaculos;) {
        int fila_obs = rand() % filas;
        int columna_obs = rand() % filas;
        
        if (matriz[fila_obs][columna_obs] != 1) {
            continue;
        };
        
        int opciones = rand() % 10;
        
        if (opciones > 5) {
            matriz[fila_obs][columna_obs] = 4; //piedras
        } else {
            matriz[fila_obs][columna_obs] = 3; //agua
        };
        
        i += 1;
    };
};

void Mapa::agregar_obstaculo_manual(int fila, int columna) {
    if (!revisar_casilla_disponible(fila, columna, 1)) {
        return;
    };
    matriz[fila][columna] = 7; //obstaculo puesto;
};

// ---- metodo para quitar obstaculos del mapa -----
void Mapa::quitar_obstaculo(int fila, int columna) {
    if (!revisar_casilla_disponible(fila, columna, 2)) {
        return;
    };
    matriz[fila][columna] = 1;
    cout<<"\n\n"<<fila<<" fila : "<<columna<<" columna [obstaculo quitado]\n\n";
};

void Mapa::mostrar_valores() {
    for (int i=0; i<filas; i++) {
        for (int j=0; j<columnas; j++) {
            cout<<matriz[i][j]<<" ";
        }
        cout<<"\n";
    };
};

// getter para sacar matriz
int** Mapa::sacar_matriz() {
    int** mapa = new int *[filas];

    for (int i=0; i<filas; i++) {
        mapa[i] = new int [columnas];
        for (int j=0; j<columnas; j++) {
            mapa[i][j] = matriz[i][j];
        };
    };
    return mapa;
};
