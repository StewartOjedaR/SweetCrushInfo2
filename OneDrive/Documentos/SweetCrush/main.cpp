#include <iostream>
#include "funciones.h"
using namespace std;
int main() {
    unsigned char *tablero = nullptr;
    crearTablero(5, 6, tablero);
    imprimirTablero(5, 6, tablero);
    InsertarFicha(5,tablero,4,5,6);
    InsertarFicha(5,tablero,4,4,6);
    InsertarFicha(5,tablero,3,5,6);
    InsertarFicha(5,tablero,2,5,6);
    InsertarFicha(5,tablero,1,5,6);
        InsertarFicha(5,tablero,3,0,6);
    InsertarFicha(5,tablero,2,1,6);
    imprimirTablero(5, 6, tablero);
    ImprimirTableroEnBits(5, 6, tablero);


    delete[] tablero;

    return 0;
}
