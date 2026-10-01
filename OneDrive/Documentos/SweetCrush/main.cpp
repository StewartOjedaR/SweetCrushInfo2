#include <iostream>
#include "funciones.h"
using namespace std;
int main() {
    int filas = 5;
    int columnas = 7;
    unsigned char *tablero = nullptr;
    crearTablero(filas, columnas, tablero);
    imprimirTablero(filas, columnas, tablero);
    rellenarTablero(filas, columnas, tablero);
    imprimirTablero(filas, columnas, tablero);
    borrarFicha(tablero, 2, 3, columnas);
    borrarFicha(tablero, 1, 3, columnas);

    imprimirTablero(filas, columnas, tablero);
aplicarGraverdad(tablero, filas, columnas);
    imprimirTablero(filas, columnas, tablero);

    delete[] tablero;

    return 0;
}
