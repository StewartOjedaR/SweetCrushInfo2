#include <iostream>
#include "funciones.h"
char basura;
unsigned char *tablero=nullptr;
bool continuarJuego=true;
int accion, puntaje;
int numColumnas = 7, numFilas = 7;

using namespace std;
int main() {

  cout << "-----------Bienvenido a juego Sweet Crush!-----------" << endl << endl;
  cout << "    Por favor, ingresa el ancho del tablero: ";
  while (numColumnas < 1) {
    cout << "El ancho debe ser mayor a 1. Por favor, intenta de nuevo: ";
    cin >> numColumnas;
  }

  cout << "    Ahora, ingresa el alto del tablero: ";
  while (numFilas < 1) {
    cout << "El alto debe ser mayor a 1. Por favor, intenta de nuevo: ";
    cin >> numFilas;
  }

  cout << endl << "Configurando tablero..." << endl;
  crearTablero(numFilas, numColumnas, tablero);
  rellenarTablero(numFilas, numColumnas, tablero);
  cout << "Tablero configurado." << endl << "¡Listo para comenzar el juego!" << endl << " ¿Deseas jugar? (Si=s, No=n): ";
  
  char play = 's';
  //cin>>play;
  cout<<endl;
  while (play != 's' && play != 'n') {
    cout << endl << "Por favor, ingresa 's' para jugar o 'n' para salir: ";
    cin >> play;
  }

  while (play == 's' && continuarJuego == true) {
    imprimirTablero(numFilas, numColumnas, tablero);
    cout<<"PUNTAJE: "<<puntaje<<endl;
    while (hayCoincidencias(numFilas, numColumnas, tablero, puntaje)) {
      cout << "Match!!!" << endl << "Ingrese cualquier tecla para continuar: ";
      cin >> basura;
      borrarCoincidencias(numFilas, numColumnas, tablero);
      imprimirTablero(numFilas, numColumnas, tablero);
      cout << "Ingrese cualquier tecla para continuar: ";
      cin >> basura;
      llenarHuecos(tablero, numFilas, numColumnas);
      imprimirTablero(numFilas, numColumnas, tablero);
      cout<<"PUNTAJE: "<<puntaje<<endl;
    }

    do {
      cout << "Acciones: 1: Eliminar Ficha"
           << endl << "          2: Borrar Fila"
           << endl << "          3: Borrar Columna"
           << endl << "          4: Agregar Fila"
           << endl << "          5: Agregar Columna "
           << endl << "          6: Salir del juego" << endl << "ingresar opcion: ";
      cin >> accion;
      if (accion < 1 || accion > 6) {
        cout << "Ingrese una accion valida" << endl;
      }
    } while (accion < 1 || accion > 6);

      int tempFila = 0, tempColumna = 0;
      bool confirmar = false;
    switch (accion) {

      case 1: {
        
        while (!confirmar) {
          cout << "Ingrese las coordenadas de la ficha" << endl << "Fila: ";
          cin >> tempFila;
          cout << "Colunma: ";
          cin >> tempColumna;
          cout << "Eliminar la ficha " << '(' << tempFila << ',' << tempColumna << ')' << " : ";
          ImprimirFicha(tempFila, tempColumna, numColumnas, tablero);
          cout << endl << "Confirmar s/n: ";
          cin >> basura;
          while (basura != 's' && basura != 'n') {
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            borrarFicha(tablero, tempFila, tempColumna, numColumnas);
            imprimirTablero(numFilas, numColumnas, tablero);
            aplicarGravedad(tablero,numFilas,numColumnas);
            cout << "ingresa cualquier letra para continuar: ";
            cin >> basura;
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            imprimirTablero(numFilas, numColumnas, tablero);
            continue;
          }
        }
        break;
      }

      case 2: { // borrar Fila
        while (!confirmar) {
          cout << "Ingrese la fila" << endl << "Fila: ";
          cin >> tempFila;
          while (tempFila > numFilas || tempFila < 0) {
            cout << "Ingrese una fila valida. " << endl << "Fila: ";
            cin >> tempFila;
          }
          cout << "Eliminar la fila: " << tempFila;
          cout << endl << "Confirmar s/n: ";
          cin >> basura;
          while (basura != 's' && basura != 'n') {
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            eliminarFila(tempFila, numFilas, numColumnas, tablero);
            imprimirTablero(numFilas, numColumnas, tablero);
            cout << "ingresa cualquier letra para continuar: ";
            cin >> basura;
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            imprimirTablero(numFilas, numColumnas, tablero);
            continue;
          }
        }
        break;
      }

      case 3: { // borrar columna
        while (!confirmar) {
          cout << "Ingrese la columna" << endl << "Columna: ";
          cin >> tempColumna;
          while (tempColumna > numColumnas || tempColumna < 0) {
            cout << "Ingrese una columna valida. " << endl << "Columna: ";
            cin >> tempColumna;
          }
          cout << "Eliminar la columna: " << tempColumna;
          cout << endl << "Confirmar s/n: ";
          cin >> basura;
          while (basura != 's' && basura != 'n') {
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            eliminarColumna(tempColumna, numFilas, numColumnas, tablero);
            imprimirTablero(numFilas, numColumnas, tablero);
            cout << "ingresa cualquier letra para continuar: ";
            cin >> basura;
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            imprimirTablero(numFilas, numColumnas, tablero);
            continue;
          }
        }
        break;
      }

      case 4: { // agregar Fila
        while (!confirmar) {
          cout << "Ingrese la fila" << endl << "Fila: ";
          cin >> tempFila;
          while (tempFila > numFilas || tempFila < 0) {
            cout << "Ingrese una fila valida. " << endl << "Fila: ";
            cin >> tempFila;
          }
          cout << "Agregar una fila en la posicion: " << tempFila;
          cout << endl << "Confirmar s/n: ";
          cin >> basura;
          while (basura != 's' && basura != 'n') {
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            agregarFila(tempFila, numFilas, numColumnas, tablero);
            imprimirTablero(numFilas, numColumnas, tablero);
            cout << "ingresa cualquier letra para continuar: ";
            cin >> basura;
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            imprimirTablero(numFilas, numColumnas, tablero);
          }
        }
        break;
      }

      case 5: { // agregar columna
        while (!confirmar) {
          cout << "Ingrese la columna" << endl << "Columna: ";
          cin >> tempColumna;
          while (tempColumna > numColumnas || tempColumna < 0) {
            cout << "Ingrese una columna valida. " << endl << "Columna: ";
            cin >> tempColumna;
          }
          cout << "Agregar la columna en la posicion: " << tempColumna;
          cout << endl << "Confirmar s/n: ";
          cin >> basura;
          while (basura != 's' && basura != 'n') {
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            agregarColumna(tempColumna, numFilas, numColumnas, tablero);
            imprimirTablero(numFilas, numColumnas, tablero);
            cout << "ingresa cualquier letra para continuar: ";
            cin >> basura;
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            imprimirTablero(numFilas, numColumnas, tablero);
          }
        }
        break;
      }

      case 6:
        continuarJuego = false;
        break;

      default:
        break;
    }
  }

  if (!continuarJuego) {
    cout << "¡Hasta luego! " << endl;
  }

  delete tablero;
  return 0;
}
