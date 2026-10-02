#include <iostream>
#include "funciones.h"
using namespace std;
int main() {
    int filas = 5;
    int columnas = 7;
  //  cin >> columnas;
    unsigned char *tablero = nullptr;
    crearTablero(filas, columnas, tablero);
    imprimirTablero(filas, columnas, tablero);
    rellenarTablero(filas, columnas, tablero);
    imprimirTablero(filas, columnas, tablero);
    borrarFicha(tablero, 2, 3, columnas);
    borrarFicha(tablero, 1, 2, columnas);
    borrarFicha(tablero, 5, 6, columnas);
    borrarFicha(tablero, 0, 1, columnas);
    borrarFicha(tablero, 4, 5, columnas);
    borrarFicha(tablero, 3, 4, columnas);
    imprimirTablero(filas, columnas, tablero);
    
    aplicarGraverdad(tablero, filas, columnas);
    imprimirTablero(filas, columnas, tablero);
    delete[] tablero;

    return 0;
}
