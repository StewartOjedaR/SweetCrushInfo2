#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
using namespace std;
void byteBinario(unsigned char a){
for (int i=(sizeof(a)*8)-1;i>=0;i--){
    if ((a>>i)&1==1){
       cout<<'1';
    }else{ 
      cout<<'0';
    } if (i%4==0){cout<<' ';
}}
}
void imprimirByteArreglo(int fila, int columna, int numColumnas, unsigned char *&tablero){
            for(int i=0;i<((numColumnas*fila*3)+numColumnas)/8;i++){
        byteBinario(tablero[i]);
        cout<<"byte["<<i<<"]"<<endl;

    }
}
unsigned char fichaID(unsigned char byte) {
    switch (byte) {
    case 0b00000000:
        return 'A';
    case 0b00000001:
        return 'B';
    case 0b00000010:
        return 'C';
    case 0b00000011:
        return 'D';
    case 0b00000100:
        return 'E';
    case 0b00000101:
        return 'F';
    case 0b00000110:
        return '*';
    case 0b00000111:
        return ' ';
    default:
        return ' ';
    }
}
void imprimirTresBitsInferiores(unsigned char valor) {
    // Bit 0 (el más significativo de los tres)
    cout << ((valor >> 2) & 1);
    // Bit 1 (del medio)
    cout << ((valor >> 1) & 1);
    // Bit 2 (el menos significativo, LSB)
    cout << ((valor >> 0) & 1)<<' ';

}
bool dualBytes(float decimal){
    if (decimal==0.125||decimal==0.25){
        return true;
    }
    else {
        return false;
    }
}
void indicesBytes(int bitPosicion,int*& byte_1, int*& byte_2){
    float decimales=(static_cast<float>(bitPosicion)/8)-(bitPosicion/8);
    bitPosicion=bitPosicion-3;
    if (dualBytes(decimales)){
        byte_1 = new int(bitPosicion/8);//3->0,24->
        byte_2 = new int((bitPosicion/8)+1);
    }else{

        byte_1=new int ((bitPosicion/8));
    }
}
unsigned char NumFicha(int numeroID){
    switch (numeroID) {
    case 0:
        return 0b00000000;
    case 1:
        return 0b00000001;
    case 2:
        return 0b00000010;
    case 3:
        return 0b00000011;
    case 4:
        return 0b00000100;
    case 5:
        return 0b00000101;
    case 6:
        return 0b00000110;
    case 7:
        return 0b00000111;
    default:
        return 8;
    }
}
void mascaraIdFicha(int idFicha, int bitPosicion, unsigned char *&masc_1, unsigned char *&masc_2){
    //idFicha=5->00000101
    float decimales=(static_cast<float>(bitPosicion)/8)-(bitPosicion/8);//define la forma de distribuir los bit entre 1 o 2 bytes
    auto ficha=NumFicha(idFicha);
    if (decimales==0.125||decimales==0.25){
        if (decimales==0.125){
            //    byte anterior byte[x] 000000xx y byte[x+1] x0000000
            //000 001 01->[000 000 10] [1 000 000 0]

            masc_1 = new unsigned char(ficha); // 0000 0101
            masc_2 = new unsigned char(ficha);
            *masc_1 = *masc_1 >> 1;// 10000000
            *masc_2 = *masc_2 << 7;//00000010
        }else{//byte[x]=0000000x y byte[x+1]=xx000000
            masc_1 = new unsigned char(ficha); // 0000 0xxx
            masc_2 = new unsigned char(ficha);// 0000 0xxx
            *masc_1 = *masc_1 >>2 ;//0000 0xxx->0000 000x
            *masc_2 = *masc_2 << 6;//0000 0xxx->xx00 0000
        }
    }
    else {
        int opcion=decimales*8;//0.375*8=3,0.5*8=4,0.625*8=5,0.75*8=6,0.875*8=7
        switch (opcion) {
        case 3://mascara_1 = new unsigned char(ficha);//0.375//
            masc_1 = new unsigned char(ficha);//00000xxx
            *masc_1=*masc_1 << 5;//xxx00000
            masc_2=nullptr;
            break;
        case 4://mascara_1 = new unsigned char(ficha);//0.5
            masc_1 = new unsigned char(ficha);//00000xxx
            *masc_1=*masc_1 << 4;//0xxx0000
            masc_2=nullptr;
            break;
        case 5://mascara_1 = new unsigned char(ficha);//0.625
            masc_1 = new unsigned char(ficha);//00000xxx
            *masc_1=*masc_1 << 3;//00xxx000
            masc_2=nullptr;
            break;
        case 6://mascara_1 = new unsigned char(ficha);//0.75
            masc_1 = new unsigned char(ficha);//00000xxx
            *masc_1=*masc_1 << 2;//000xxx00
            masc_2=nullptr;
            break;
        case 7://mascara_1 = new unsigned char(ficha);//0.875
            masc_1 = new unsigned char(ficha);//00000xxx
            *masc_1=*masc_1 << 1;//0000xxx0
            masc_2=nullptr;
            break;
        case 0://mascara_1 = new unsigned char(ficha);//

            masc_1 = new unsigned char(ficha);//00000xxx
            masc_2=nullptr;
         // imprimirTresBitsInferiores(*masc_1);
            break;
        default:
            break;
        }


    }
}
void InsertarFicha(int idFicha, unsigned char* tablero,int fila, int columna, int numColumnas){
    int *byte_1=nullptr, *byte_2=nullptr;//x_1=x-1
    int bitPosicion;
    unsigned char *masc_1=nullptr,*masc_2=nullptr, *mascTemp_1=nullptr,*mascTemp_2=nullptr;
    bitPosicion=(((columna+1)*3)+(fila*(numColumnas*3)));//
                 //cuantos bits por columna + 
    mascaraIdFicha(idFicha,bitPosicion,masc_1,masc_2);//
 //   mascaraIdFicha(0b111,bitPosicion,mascTemp_1,mascTemp_2);//mascTemp_1 devuelve una ficha a aplicar ,mascTemp_2

    indicesBytes(bitPosicion,byte_1,byte_2);
    if (byte_2 != nullptr) {//
     //   tablero[*byte_1]&=(~*mascTemp_1);//
    //    tablero[*byte_2]&=(~*mascTemp_2);
        tablero[*byte_1]^=*masc_1;
        tablero[*byte_2]^=*masc_2;
        delete byte_1, byte_2, masc_1, masc_2, mascTemp_1, mascTemp_2;
 
    } else {
       // tablero[*byte_1]&=(~*mascTemp_1);
        tablero[*byte_1]^=*masc_1;
    //    byteBinario((tablero[*byte_1]));
//cout<<"byte_1: "<<*byte_1<<endl;
//imprimirTresBitsInferiores(tablero[*byte_1]);
//cout <<tablero[*byte_1]<<endl;
        delete byte_1, byte_2, masc_1, masc_2, mascTemp_1, mascTemp_2;
    }


}

void crearTablero(int numFilas, int numColumnas, unsigned char *&tablero) {
    int totalBits = numFilas * numColumnas * 3;
    int numBytes = (totalBits + 7) / 8;
    tablero = new unsigned char[numBytes];

    for (int i = 0; i < numBytes; ++i) {
        tablero[i] = 0;
    }
}
void rellenarTablero(int filas, int columnas, unsigned char *&tablero) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            int idFicha = rand() % 6; // Genera un número aleatorio entre 0 y 5
            InsertarFicha(idFicha, tablero, i, j, columnas);
            
        }
    }
}
void borrarBit(int posBit, unsigned char &byte) {
    byte &= ~(1 << posBit);
}
unsigned char ByteFicha(int fila, int columna,int numColumnas, unsigned char *& tablero) {//me devuelve un unsigned char con los tres bits menos significativos
    // Justificación: Para saber qué caso aplicar según tu lógica de 3 bits por posición,
    // evaluamos el residuo de la posición del bit entre 8 (equivalente a los decimales que buscabas).
    // Posiciones de bits por ficha: 0, 3, 6, 9, 12, 15, 18, 21...
    /*      0+1         1                     0*6=0+(1*3)=3
     0,0=(fila+1), (col+1), numColum=6,->3 (fila*numColumna)+(columna+1)*3
            0+1        2                        0*6=0+(2*3)=6
     0,1=(fila+1), (col+1), numColum=6,->6(fila*numColumna*3)+(columna+1)*3
           0+ 1        3                        0*6=0+(3*3)=9
     0,2=(fila+1), (col+1), numColum=6,->9(fila*numColumna)+(columna+1)*3
...
          1+ 1         1                      1*6*3=18+((0+1)*3)=21
     1,0=(fila+1), (col+1), numColum=6,->(fila*numColumna)+(columna+1)*3
           1+1          2                       1*6*3=18+((1+1)*3)=24
     1,1=(fila+1), (col+1), numColum=6,->(fila*numColumna)+(columna+1)*3
            1+1        3                     1*6*3=18+((2+1)*3)=27
     1,2=(fila+1), (col+1), numColum=6,->(fila*numColumna)+(columna+1)*3
            2         3
     1,3=(fila+1), (col+1), numColum=6,->
...         3         1                    2*6*3=36+((0+1)*3)
     2,0=(fila+1), (col+1), numColum=6,->(fila*numColumna)+(columna+1)*3
            3         2
     2,1=(fila+1), (col+1), numColum=6,->
            3         3
    2,2 =(fila+1), (col+1), numColum=6,->

*///               (1+1)*3=6+18=24
    int bitFicha=((columna+1)*3)+(fila*(numColumnas*3));//
    bitFicha=bitFicha-3;
    unsigned char letra = '\0';
    unsigned char temp = 0;

    switch (((bitFicha+3) % 8)) {
    
    case 1: // 0.125 (bitFicha 9, 17, etc. donde 9%8 = 1) -> cruza byte [x] y [x+1]
        letra = tablero[bitFicha/8] <<1 ;// 0000 00xx->0000 0xx0
        temp = tablero[((bitFicha/8)+1)] >> 7;//x000 0000->0000 000x
        letra = letra ^ temp;//0000000x ^ 00000xx0=00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 2: // 0.25 (bitFicha 10, 18, etc. donde 10%8 = 2) -> cruza byte [x] y x+1
        letra = tablero[bitFicha/8] << 2;
        temp = tablero[((bitFicha/8)+1)] >> 6;
        letra = letra ^ temp;//000000xx ^ 00000x00=00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 3: // 0.375 (bitFicha 3, 11, 19...) -> 3 bits completos en el byte
        //                                xxx00000
        letra = tablero[bitFicha/8] >> 5;//00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 4: // 0.5 (bitFicha 12, 20...) -> cruza o empieza en offset 4
        letra = tablero[bitFicha/8] >> 4;//0xxx0000>>4->00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 5: // 0.625 (bitFicha 5, 13, 21...)
        letra = tablero[bitFicha/8] >> 3;
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 6: // 0.75 (bitFicha 6, 14, 22...)
        letra = tablero[bitFicha/8] >> 2;//0000 0000
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 7: // 0.875 (bitFicha 7, 15, 23...)
        letra = tablero[bitFicha/8] >> 1;
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 0: // 1.0 / 0.0 (bitFicha 0, 8, 16, 24...)
        letra = tablero[bitFicha/8];//00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    default:
        std::cout << "El valor ingresado no es válido.\n";
        return 1;
    }
}
void ImprimirFicha(int fila, int columna,int numColumnas, unsigned char *& tablero) {
    // Justificación: Para saber qué caso aplicar según tu lógica de 3 bits por posición,
    // evaluamos el residuo de la posición del bit entre 8 (equivalente a los decimales que buscabas).
    // Posiciones de bits por ficha: 0, 3, 6, 9, 12, 15, 18, 21...
    /*      0+1         1                     0*6=0+(1*3)=3
     0,0=(fila+1), (col+1), numColum=6,->3 (fila*numColumna)+(columna+1)*3
            0+1        2                        0*6=0+(2*3)=6
     0,1=(fila+1), (col+1), numColum=6,->6(fila*numColumna*3)+(columna+1)*3
           0+ 1        3                        0*6=0+(3*3)=9
     0,2=(fila+1), (col+1), numColum=6,->9(fila*numColumna)+(columna+1)*3
...
          1+ 1         1                      1*6*3=18+((0+1)*3)=21
     1,0=(fila+1), (col+1), numColum=6,->(fila*numColumna)+(columna+1)*3
           1+1          2                       1*6*3=18+((1+1)*3)=24
     1,1=(fila+1), (col+1), numColum=6,->(fila*numColumna)+(columna+1)*3
            1+1        3                     1*6*3=18+((2+1)*3)=27
     1,2=(fila+1), (col+1), numColum=6,->(fila*numColumna)+(columna+1)*3
            2         3
     1,3=(fila+1), (col+1), numColum=6,->
...         3         1                    2*6*3=36+((0+1)*3)
     2,0=(fila+1), (col+1), numColum=6,->(fila*numColumna)+(columna+1)*3
            3         2
     2,1=(fila+1), (col+1), numColum=6,->
            3         3
    2,2 =(fila+1), (col+1), numColum=6,->

*///               (1+1)*3=6+18=24
    int bitFicha=((columna+1)*3)+(fila*(numColumnas*3));
    bitFicha=bitFicha-3;
    unsigned char letra = '\0';
    unsigned char temp = 0;

    switch ((bitFicha+3) % 8) {                                         //[0000 00xx] [x000 000]
    case 1: // 0.125 (bitFicha 9, 17, etc. donde 9%8 = 1) -> cruza byte [x] y [x+1]
        letra = tablero[bitFicha/8] <<1 ;// 0000 00xx->0000 0xx0
        temp = tablero[((bitFicha/8)+1)] >> 7;//x000 0000->0000 000x
        letra = letra ^ temp;//00000xx0 ^ 0000000x=00000xxx
        letra=letra & 0b00000111;//00000xxx
        cout << fichaID(letra);
        break;
        //                                                   
        //                                                [0000 000x]      [xx000000]
    case 2: // 0.25 (bitFicha 18, etc. donde 18%8 = 2) -> cruza byte [x] y [x+1]
        letra = tablero[bitFicha/8] << 2;//00000x->00000x00
        temp = tablero[((bitFicha/8)+1)] >> 6;//xx000000->000000xx
        letra = letra ^ temp;//00000x00 ^ 000000xx=00000xxx
        letra=letra & 0b00000111;//00000xxx
        cout << fichaID(letra);
        break;
    case 3: // 0.375 (bitFicha 3, 11, 19...) -> 3 bits completos en el byte
        //                                xxx00000
        letra = tablero[bitFicha/8] >> 5;//00000xxx
        letra=letra & 0b00000111;//00000xxx
        cout << fichaID(letra);
        break;
    case 4: // 0.5 (bitFicha 12, 20...) -> 
        letra = tablero[bitFicha/8] >> 4;//0xxx0000>>4->00000xxx
        letra=letra & 0b00000111;//00000xxx
        cout << fichaID(letra);
        break;
    case 5: // 0.625 (bitFicha 5, 13, 21...)
        letra = tablero[bitFicha/8] >> 3;
        letra=letra & 0b00000111;//00000xxx
        cout << fichaID(letra);
        break;
    case 6: // 0.75 (bitFicha 6, 14, 22...)
        letra = tablero[bitFicha/8] >> 2;//0000 0000
        letra=letra & 0b00000111;//00000xxx
        cout << fichaID(letra);
        break;
    case 7: // 0.875 (bitFicha 7, 15, 23...)
        letra = tablero[bitFicha/8] >> 1;
        letra=letra & 0b00000111;//00000xxx
        cout << fichaID(letra);
        break;
    case 0: // 1.0 / 0.0 (bitFicha 0, 8, 16, 24...)
        letra = tablero[bitFicha/8];//00000xxx
        letra=letra & 0b00000111;//00000xxx
        cout << fichaID(letra);
        break;
    default:
        std::cout << "El valor ingresado no es válido.\n";
        break;
    }
}
unsigned char FichaPorCoord (int fila, int columna,int numColumnas, unsigned char *& tablero) {
    int bitFicha=((columna+1)*3)+(fila*(numColumnas*3));
    bitFicha=bitFicha-3;
    unsigned char letra, temp;
    switch ((bitFicha+3) % 8) {                                         //[0000 00xx] [x000 000]
    case 1: // 0.125 (bitFicha 9, 17, etc. donde 9%8 = 1) -> cruza byte [x] y [x+1]
        letra = tablero[bitFicha/8] <<1 ;// 0000 00xx->0000 0xx0
        temp = tablero[((bitFicha/8)+1)] >> 7;//x000 0000->0000 000x
        letra = letra ^ temp;//00000xx0 ^ 0000000x=00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;//                                           [0000 000x]      [xx000000]
    case 2: // 0.25 (bitFicha 18, etc. donde 18%8 = 2) -> cruza byte [x] y [x+1]
        letra = tablero[bitFicha/8] << 2;//00000x->00000x00
        temp = tablero[((bitFicha/8)+1)] >> 6;//xx000000->000000xx
        letra = letra ^ temp;//00000x00 ^ 000000xx=00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 3: // 0.375 (bitFicha 3, 11, 19...) -> 3 bits completos en el byte
        //                                xxx00000
        letra = tablero[bitFicha/8] >> 5;//00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 4: // 0.5 (bitFicha 12, 20...) -> 
        letra = tablero[bitFicha/8] >> 4;//0xxx0000>>4->00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 5: // 0.625 (bitFicha 5, 13, 21...)
        letra = tablero[bitFicha/8] >> 3;
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 6: // 0.75 (bitFicha 6, 14, 22...)
        letra = tablero[bitFicha/8] >> 2;//0000 0000
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 7: // 0.875 (bitFicha 7, 15, 23...)
        letra = tablero[bitFicha/8] >> 1;
        letra=letra & 0b00000111;//00000xxx
        return letra;
    case 0: // 1.0 / 0.0 (bitFicha 0, 8, 16, 24...)
        letra = tablero[bitFicha/8];//00000xxx
        letra=letra & 0b00000111;//00000xxx
        return letra;
    default:
        std::cout << "El valor ingresado no es válido.\n";
        return 0;
    }
}
void coordenadasSegunBit(int bitFicha, int *&fila, int *&columna, int numColumnas) {
    int numBitsXColumnas =numColumnas*3; // Multiplica las columnas originales por 3 para obtener el total de bits por fila (ej. 6 * 3 = 18 bits).
    columna = new int(((bitFicha % numBitsXColumnas)/3)-1 ); // Calcula la columna dividiendo el residuo de la fila entre 3 (ya que cada columna ocupa 3 bits).
    bool seguir=true;
    if (*columna<= -1){
        *columna =(numColumnas-1);
        fila = new int(bitFicha / numBitsXColumnas);
        *fila=*fila-1;
        seguir=false;
    }
    if (seguir){
        fila = new int(bitFicha / numBitsXColumnas); // Calcula la fila dividiendo el bitFicha total entre el número de bits por fila.

    }
}
void imprimirTablero(int numFilas, int numColumnas, unsigned char *&tablero){
    int totalFichas = numFilas * numColumnas;
    int *fila(nullptr),*columna(nullptr);
    int *tableroPtr=nullptr;
    int bitFicha;
    // Justificación: Cada ficha salta exactamente 3 bits en el arreglo continuo.
    // Índices de bits: i=1 (bit 3), i=2 (bit 6), i=3 (bit 9)...
    for (int i = 3; i <= totalFichas*3;){
        bitFicha = i;
        coordenadasSegunBit(bitFicha,fila,columna,numColumnas);
      //  byteBinario(ByteFicha(*fila, *columna, numColumnas,tablero));
        cout << ' ';
        cout << fichaID(ByteFicha(*fila, *columna, numColumnas,tablero)) << ' ';
  //      imprimirTresBitsInferiores(ByteFicha(*fila, *columna, numColumnas,tablero));
        if (bitFicha%(numColumnas*3)==0){
            cout<<endl;
        }
        i+=3;
    }
    cout << endl;
    delete columna;
    delete fila;
}
void ImprimirTableroEnBits(int numFilas, int numColumnas, unsigned char *&tablero){
    int totalFichas = numFilas * numColumnas;
    int *fila(nullptr),*columna(nullptr);
    int *tableroPtr=nullptr;
    int bitFicha;
    // Justificación: Cada ficha salta exactamente 3 bits en el arreglo continuo.
    // Índices de bits: i=1 (bit 3), i=2 (bit 6), i=3 (bit 9)...
    for (int i = 3; i <= totalFichas*3;){
        bitFicha = i;
        coordenadasSegunBit(bitFicha,fila,columna,numColumnas);
        imprimirTresBitsInferiores(ByteFicha(*fila, *columna, numColumnas,tablero));
        if (bitFicha%(numColumnas*3)==0){
            cout<<endl;
        }
        i+=3;
    }
    cout << endl;
    delete columna;
    delete fila;
}
void borrarFicha(unsigned char* tablero,int fila, int columna, int numColumnas){
    int *byte_1=nullptr, *byte_2=nullptr;//x_1=x-1
    int bitPosicion;
    unsigned char *masc_1=nullptr,*masc_2=nullptr;
    bitPosicion=(((columna+1)*3)+(fila*(numColumnas*3)));//
                 //cuantos bits por columna + 
    mascaraIdFicha(0b111,bitPosicion,masc_1,masc_2);//

    indicesBytes(bitPosicion,byte_1,byte_2);
    unsigned char temp;
    if (byte_2 != nullptr) {//
        temp=(~*masc_1);
        tablero[*byte_1]&=temp;
        tablero[*byte_1]^=*masc_1;
        temp=(~*masc_2);
        tablero[*byte_2]&=temp;
        tablero[*byte_2]^=*masc_2;
        delete byte_1;
        delete byte_2;
        delete masc_1;
        delete masc_2;
    } else {
        temp=(~*masc_1);
        tablero[*byte_1]&=temp;
        tablero[*byte_1]^=*masc_1;
//cout<<"byte_1: "<<*byte_1<<endl;
//imprimirTresBitsInferiores(tablero[*byte_1]);
//cout <<tablero[*byte_1]<<endl;
        delete byte_1;
        delete byte_2;
        delete masc_1;
        delete masc_2;
    }


}
void aplicarGraverdad(unsigned char* tablero, int numFilas, int numColumnas) {
    for (int row = 0; row <  numFilas - 1;++row ) {
        for (int  col = 0;  col<numColumnas; ++col) {
            unsigned char fichaActual = FichaPorCoord(row, col, numColumnas, tablero);
            if (fichaActual == 0b00000111) { // Si la ficha actual está vacía
                for (int k = row - 1; k >= 0; --k) {
                    unsigned char fichaArriba = ByteFicha(k, col, numColumnas, tablero);
                    if (fichaArriba != 0b00000111) { // Si hay una ficha arriba
                        borrarFicha(tablero, k, col, numColumnas); // Borrar la ficha de arriba
                        InsertarFicha(fichaArriba, tablero, row, col, numColumnas); // Mover la ficha hacia abajo
                        break;
                    }
                }
            }
        }
    }
}
#endif // FUNCIONESSWEETCRUSH_H
