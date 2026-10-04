#include <iostream>
#include "funciones.h"
using namespace std;

int main() {

    int filas = 10;
    int columnas = 10;
  //  cin >> columnas;
    unsigned char *tablero = nullptr;
    crearTablero(filas, columnas, tablero);
    rellenarTablero(filas, columnas, tablero);
    aplicarGraverdad(tablero, filas, columnas);
    imprimirTablero(filas, columnas, tablero);
    borrarCoincidencias(filas,columnas, tablero);
    imprimirTablero(filas, columnas, tablero);
 //   imprimirTableroConRecuadros(filas,columnas,tablero);
 aplicarGraverdad(tablero, filas, columnas);
     imprimirTablero(filas, columnas, tablero);
     eliminarFila(3,filas,columnas,tablero);
          imprimirTablero(filas, columnas, tablero);
               eliminarColumna(3,filas,columnas,tablero);
                        imprimirTablero(filas, columnas, tablero);
    delete[] tablero;

    return 0;
  }