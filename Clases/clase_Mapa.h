#ifndef CLASE_MAPA_H
#define CLASE_MAPA_H

//clase que es para mapa:
class Mapa {
private:
    int filas;
    int columnas;
    int **matriz;
        
    
public:
    Mapa(int cant_filas, int cant_columnas);
    
    bool revisar_casilla_disponible(int fila, int columna, int modo);
    void agregar_obstaculos_al_azar(int cantidad_obstaculos);
    void agregar_obstaculo_manual(int fila, int columna);
    void quitar_obstaculo(int fila, int columna);
    void mostrar_valores();
    int** sacar_matriz();
};

#endif