#include <iostream>
#include "funciones.h"
using namespace std;
int main() {
    unsigned char *tablero = nullptr;
    crearTablero(5, 7, tablero);
    imprimirTablero(5, 7, tablero);
rellenarTablero(5, 7, tablero);
    imprimirTablero(5, 7, tablero);
 /* for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 7; ++j) {
            InsertarFicha(5, tablero, i, j, 7);
        }
    }*/
        for(int i=0;i<((7*5*3)+7)/8;i++){
        byteBinario(tablero[i]);
        cout<<"byte["<<i<<"]"<<endl;

    }
    imprimirTablero(5, 7, tablero);
    ImprimirTableroEnBits(5, 7, tablero);


    delete[] tablero;

    return 0;
}
