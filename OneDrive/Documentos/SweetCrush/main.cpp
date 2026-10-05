#include <iostream>
#include "funciones.h"
char basura;
unsigned char *tablero=nullptr;
bool continuarJuego=true;
int accion, puntaje;


using namespace std;
int main() {
  int numColumnas, numFilas;
  cout << "-----------Bienvenido a juego Sweet Crush!-----------" << endl << endl;
  cout << "    Por favor, ingresa el ancho del tablero: ";
  cin >> numColumnas;
 
  while (numColumnas < 1) {
    if (cin.fail()){
      cin.clear();
      cout << "Error: Debes ingresar un numero." << endl;
      while (cin.get() != '\n') { 
      }
    }
    cout << "El ancho debe ser un numero mayor a 1. Por favor, intenta de nuevo: ";
    cin >> numColumnas;
  }
  cout << "    Ahora, ingresa el alto del tablero: ";
  cin >> numFilas;
  while (numFilas < 1) {
      if (cin.fail()){
          cin.clear();
            cout << "Error: Debes ingresar un numero." << endl;
          while (cin.get() != '\n') {
          }
      }
    cout << "El alto debe ser mayor a 1. Por favor, intenta de nuevo: ";
    cin >> numFilas;
  }

  cout << endl << "Configurando tablero..." << endl;
  crearTablero(numFilas, numColumnas, tablero);
  rellenarTablero(numFilas, numColumnas, tablero);
  cout << "Tablero configurado." << endl;
  cout << "Listo para comenzar el juego!" << endl << "Deseas jugar? (Si=s, No=n): ";
  
  char play = 's';
  cin>>play;
  cout<<endl;
  while (play != 's' && play != 'n') {
    cout << endl << "Por favor, ingresa 's' para jugar o 'n' para salir: ";
    cin >> play;
  }

  while (play == 's' && continuarJuego == true) {
    system("clear");
    imprimirTablero(numFilas, numColumnas, tablero);
    cout<<"PUNTAJE: "<<puntaje<<endl;
    while (hayCoincidencias(numFilas, numColumnas, tablero, puntaje)) {
      cout << "Match!!!" << endl;
//     cout << "Ingrese cualquier tecla para continuar: ";
   //  cin >> basura;
      esperarSegundos(2);
      borrarCoincidencias(numFilas, numColumnas, tablero);
      system("clear");
      imprimirTablero(numFilas, numColumnas, tablero);
   //   cout << "Ingrese cualquier tecla para continuar: ";
    //  cin >> basura;
      esperarSegundos(2);
      llenarHuecos(tablero, numFilas, numColumnas);
      system("clear");
      imprimirTablero(numFilas, numColumnas, tablero);
      cout<<"PUNTAJE: "<<puntaje<<endl;
      esperarSegundos(2);
    }
    esperarSegundos(3);
    do {
      cout << "Acciones: 1: Eliminar Ficha"
           << endl << "          2: Borrar Fila"
           << endl << "          3: Borrar Columna"
           << endl << "          4: Agregar Fila"
           << endl << "          5: Agregar Columna "
           << endl << "          6: Salir del juego" << endl << "ingresar opcion: ";
      cin >> accion;
      if (cin.fail()){
          cin.clear();
          cout << "Error: Debes ingresar un numero." << endl;
          while (cin.get() != '\n') {

          }
      }
      if (accion < 1 || accion > 6) {
        cout << "Ingrese una accion valida" << endl;
      }
    } while (accion < 1 || accion > 6);

      int tempFila = 0, tempColumna = 0;
      bool confirmar = false;
    switch (accion) {

      case 1: {
        
        while (!confirmar) {
            cout << "Ingrese las coordenadas de la ficha"<<endl;
            cout<<"Ingrese la fila: ";
            cin >> tempFila;
            while (cin.fail()||tempFila<0 || tempFila>numFilas) {
                if (cin.fail()){
                  cin.clear();
                  cout << "Error: Debes ingresar un numero." << endl;
                  while (cin.get() != '\n') {
                  }
                }
                if (tempFila>numFilas){
                  
                }
                cout<<"Ingresa una fila valida: ";
                cin>>tempFila;
            }
            cin.clear();
            while (cin.get() != '\n') {
                    }
            cout << "Ingrese la colunma: ";
            cin >> tempColumna;
            while (tempColumna<0 || tempColumna>numColumnas || cin.fail());{
                if (cin.fail()){
                    cin.clear();
                    cout << "Error: Debes ingresar un numero." << endl;
                    while (cin.get() != '\n') {

                    }
                cout<<"Ingresa una columna valida: ";
                cin >> tempColumna;

            }
          }
          
          cout << "Eliminar la ficha " << '(' << tempFila << ',' << tempColumna << ')' << " : ";
          ImprimirFicha(tempFila, tempColumna, numColumnas, tablero);
          cout << endl << "Confirmar s/n: ";
          cin >> basura;
          while (basura != 's' && basura != 'n') {
              if (cin.fail()){
                  cin.clear();
                  cout << "Error: Debes ingresar [s] o [n]." << endl;
                  while (cin.get() != '\n') {

                  }
              }
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            borrarFicha(tablero, tempFila, tempColumna, numColumnas);
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
            aplicarGravedad(tablero,numFilas,numColumnas);
 //           cout << "ingresa cualquier letra para continuar: ";
   //         cin >> basura;
          esperarSegundos(2);
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
            esperarSegundos(2);
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
              if (cin.fail()){
                  cin.clear();
                  cout << "Error: Debes ingresar [s] o [n]." << endl;
                  while (cin.get() != '\n') {

                  }
              }
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            eliminarFila(tempFila, numFilas, numColumnas, tablero);
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
     //       cout << "ingresa cualquier letra para continuar: ";
       //     cin >> basura;
            esperarSegundos(2);
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
            esperarSegundos(2);
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
              if (cin.fail()){
                  cin.clear();
                  cout << "Error: Debes ingresar [s] o [n]." << endl;
                  while (cin.get() != '\n') {

                  }
              }
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            eliminarColumna(tempColumna, numFilas, numColumnas, tablero);
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
    //        cout << "ingresa cualquier letra para continuar: ";
      //      cin >> basura;
           esperarSegundos(2);
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
            esperarSegundos(2);
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
              if (cin.fail()){
                  cin.clear();
                  cout << "Error: Debes ingresar [s] o [n]." << endl;
                  while (cin.get() != '\n') {

                  }
              }
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            agregarFila(tempFila, numFilas, numColumnas, tablero);
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
          //  cout << "ingresa cualquier letra para continuar: ";
            //cin >> basura;
            esperarSegundos(2);
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
            esperarSegundos(2);
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
              if (cin.fail()){
                  cin.clear();
                  cout << "Error: Debes ingresar [s] o [n]." << endl;
                  while (cin.get() != '\n') {

                  }
              }
            cout << endl << "Ingresa opcion valida Si:(s) No:(n) ";
            cin >> basura;
          }
          if (basura == 's') {
            agregarColumna(tempColumna, numFilas, numColumnas, tablero);
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
            //cout << "ingresa cualquier letra para continuar: ";
            //cin >> basura;
            esperarSegundos(2);
            confirmar = true;
            break;
          }
          if (basura == 'n') {
            system("clear");
            imprimirTablero(numFilas, numColumnas, tablero);
            esperarSegundos(2);
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
    cout<<"Su puntaje fue: "<<puntaje<<endl << "Hasta luego! " << endl;
  }

  delete tablero;
  return 0;
}
