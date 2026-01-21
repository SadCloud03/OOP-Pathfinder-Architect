
 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

// ----- utilidades -----	
// --- funcion para mostrar mapa -----
void mostrar_mapas(int** matriz, int filas, int columnas) {
	cout<<"\n\n";
	
	cout<<"  ";
	for (int z=0; z<columnas; z++) {
		if (z<10) {
			cout<<"  "<<z;
		} else {
			cout<<" "<<z;
		}
	}
	cout<<"\n";
		
	for (int i=0; i<filas; i++) {
		
		if (i < 10) {
			cout<<i<<" ";
		} else {
			cout<<i;
		}
		
		for (int j=0; j<columnas; j++) {
			
			if (matriz[i][j] == 10) {
				cout<<"  #";
			} else if (matriz[i][j] == 2) {
				cout<<"  o";
			} else if (matriz[i][j] == 1) {
				cout<<"  .";
			} else if (matriz[i][j] == 3) {
				cout<<"  ~"; //agua
			} else if (matriz[i][j] == 4) {
				cout<<" ::"; //piedras
			} else if (matriz[i][j] == 7) {
				cout<<"  *"; //obstaculo agregado
			}
		};
		cout<<"\n";
	};
};
 


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



//clase CalculadoraDeRutas:
class CalculadoraDeRutas_BFS {
	 
	 
	private:
		int filas;
		int columnas;
	
		
	public:	
		// ----- constructor de clase -----
		CalculadoraDeRutas_BFS(int filas_mapa, int columnas_mapa) {
			filas = filas_mapa;
			columnas = columnas_mapa;
		;}
		
		
		
		// --- Nodo para hacer A*
		typedef struct Node {
			int fila;
			int columna;
			int g; //coste de inicio
			int h; //heuristica (costo estimado a la meta)
			int f; //costo total estimado f=g+hw
			Node* padre;
		} Node;
		
		
		
		struct compararNodes {
			bool operator()(const Node* a , const Node* b) const {
				return a->f > b->f;
			}
		};
		
		
		// creador de nodos:
		Node* crearNode(int fila, int columna, int g, int h, int f) {
			Node* nuevoNode = new Node;
			nuevoNode->fila = fila;
			nuevoNode->columna = columna;
			nuevoNode->g = g;
			nuevoNode->h = h;
			nuevoNode->f = f;
			nuevoNode->padre = NULL;
			
			return nuevoNode;
		};
		
		
		
		// heuristica para calculos:
		int heuristica_manhattan(int fila_inicio, int columna_inicio, int fila_fin, int columna_fin) {
			return abs(fila_fin - fila_inicio) + abs(columna_fin - columna_inicio);
		};

			
		// bucle de resolucion del A estrella:
		void resolver_A(int** matriz, int fila_inicio, int columna_inicio, int fila_fin, int columna_fin){
			
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
				system("CLS");
				matriz[recorrer->fila][recorrer->columna] = 2;
				recorrer = recorrer->padre;
				mostrar_mapas(matriz, filas, columnas);
				_sleep(120);
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
