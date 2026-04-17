#include "Clases/clase_CalculadoraDeRutas_BFS.h"
#include "Clases/clase_Mapa.h"
#include "functions/extra_functions.h"
 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

using namespace std;


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
	
	system("clear");
	cout<<"\nMapa creado";
	Mapa mapa = Mapa(filas_usuario, columnas_usuario);
	mostrar_mapas( mapa.sacar_matriz(), filas_usuario, columnas_usuario);
	
	
	cout<<"\nCuantos obstaculos extra tendra el mapa: ";
	cin>>cantidad_obstaculos;
	
	system("clear");
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
		
		system("clear");
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
		
		system("clear");
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
