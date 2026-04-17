#include "extra_functions.h"
#include <iostream>

using namespace std;

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
 