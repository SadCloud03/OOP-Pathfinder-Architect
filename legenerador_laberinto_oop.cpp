#include "Clases/clase_CalculadoraDeRutas_BFS.h"
#include "functions/extra_functions.h"
 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

using namespace std;



//clase que es para mapa:
class Mapa {
	// ----- atrubutos de instancia ----
	private:
		int filas;
		int columnas;
		int **matriz;
		 
		
	public:
		//---- constructor de clase -----
		Mapa(int cant_filas, int cant_columnas) {
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
		
		
	
		// ----- metodo para revisar si la casilla de la matriz esta disponible o si la casilla forma parte de la matriz ----- 
		bool revisar_casilla_disponible(int fila, int columna, int modo) {
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
		
		
		
		// ----- metodo para agregar obstaculos extra de forma aleatoria -----
		void agregar_obstaculos_al_azar(int cantidad_obstaculos) {
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
		
		
		
		// ----- metodo para agregar obstaculos de manera manual -----
		void agregar_obstaculo_manual(int fila, int columna) {
			if (!revisar_casilla_disponible(fila, columna, 1)) {
				return;
			};
			matriz[fila][columna] = 7; //obstaculo puesto;
		};
		
		
		
		// ---- metodo para quitar obstaculos del mapa -----
		void quitar_obstaculo(int fila, int columna) {
			if (!revisar_casilla_disponible(fila, columna, 2)) {
				return;
			};
			matriz[fila][columna] = 1;
			cout<<"\n\n"<<fila<<" fila : "<<columna<<" columna [obstaculo quitado]\n\n";
		};

		
		
		// ---- mostrar los valores de las casillas del mapa ----
		void mostrar_valores() {
			for (int i=0; i<filas; i++) {
				for (int j=0; j<columnas; j++) {
					cout<<matriz[i][j]<<" ";
				}
				cout<<"\n";
			};
		};
		
		
		
		// getter para sacar matriz
		int** sacar_matriz() {
			return matriz;
		};
};



int main() {
	srand(time(NULL));
	
	char desicion;
	int filas_usuario, columnas_usuario, cantidad_obstaculos, fila_obstaculo, columna_obstaculo, fila_inicio, columna_inicio, fila_fin, columna_fin;
	
	
	//preguntar al usuario por el tamanio del mapa
	cout<<"\nCalculador de rutas:\n\n";
	cout<<"Cuantas filas tendra el mapa: ";
	cin>>filas_usuario;
	
	cout<<"\nCuantas columnas tendra el mapa: ";
	cin>>columnas_usuario;
	
	
	//crear objeto calculador de rutas:
	CalculadoraDeRutas_BFS calculador = CalculadoraDeRutas_BFS(filas_usuario, columnas_usuario);
	
	system("CLS");
	cout<<"\nMapa creado";
	Mapa mapa = Mapa(filas_usuario, columnas_usuario);
	mostrar_mapas( mapa.sacar_matriz(), filas_usuario, columnas_usuario);
	
	
	cout<<"\nCuantos obstaculos extra tendra el mapa: ";
	cin>>cantidad_obstaculos;
	
	system("CLS");
	cout<<"\nMapa creado";
	mapa.agregar_obstaculos_al_azar(cantidad_obstaculos);
	mostrar_mapas(mapa.sacar_matriz(), filas_usuario, columnas_usuario);
	
	
	cout<<"\nDesea agregar obstaculos de forma manual?: (s/n) ";
	cin>>desicion;
	
	while (desicion == 's') {	
		cout<<"\n\nEn que fila: ";
		cin>>fila_obstaculo;
		cout<<"\nEn que columna: ";
		cin>>columna_obstaculo;
		
		mapa.agregar_obstaculo_manual(fila_obstaculo, columna_obstaculo);
		
		system("CLS");
		mostrar_mapas(mapa.sacar_matriz(), filas_usuario, columnas_usuario);
		cout<<"\nDesea agregar otro obstaculo?: (s/n) ";
		cin>>desicion;
	};
	
	
	
	cout<<"\nDesea quitar obstaculos de forma manual?: (s/n) ";
	cin>>desicion;
	while (desicion == 's') {
		
		cout<<"\n\nEn que fila: ";
		cin>>fila_obstaculo;
		cout<<"\nEn que columna: ";
		cin>>columna_obstaculo;
		
		mapa.quitar_obstaculo(fila_obstaculo, columna_obstaculo);
		
		system("CLS");
		mostrar_mapas(mapa.sacar_matriz(), filas_usuario, columnas_usuario);
		cout<<"\nDesea quitar otro obstaculo?: (s/n) ";
		cin>>desicion;
	};
	
	
	cout<<"\nQuieres calcular el camino mas corto entre dos direcciones?: (s/n) ";
	cin>>desicion;
	
	while (desicion == 's') {
		
		int** matriz_extra = mapa.sacar_matriz();
		
		cout<<"\nDe que fila: ";
		cin>>fila_inicio;
		
		cout<<"\nDe que columna: ";
		cin>>columna_inicio;
		
		cout<<"\nA que fila: ";
		cin>>fila_fin;
		
		cout<<"\nA que columna: ";
		cin>>columna_fin;
		
		calculador.resolver_A(matriz_extra, fila_fin, columna_fin, fila_inicio, columna_inicio);
		cout<<"\nDesea calcular otra ruta?: (s/n) ";
		cin>>desicion;
	}
	


	return 0;
};
