#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int tablero[4][4];
char movimiento[10];//Arreglo para saber el movimiento del usuario
#define tamano 10 //Tamaño del bufeer de lo que lee el usuarui
int cantEspacio=16;//Espacios libres en el tablero
bool modifico=false;//Booleano que sirve para saber si se modifico una celda

/// Mensaje bienvenida
void msg_bienvenida();

///Inicializacion tablero
void init_tablero();

///Imprimo la matriz
void prnt_matriz();

///Inicializo posiciones random y numeros random
void posiciones_random(int cantVeces);

///Pido al usuario ingresar el movimiento
void movimiento_usuario();

void movimiento_W();
void suma_W();
int puntaje_maximo();

int main(){
    int cantVeces,puntMax;

    // Mensaje bienvenida
    msg_bienvenida();

    //Inicializacion tablero
    init_tablero();

    /*tablero[0][0]=2;
    tablero[0][1]=2;
    tablero[0][3]=4;*/
    ///Inicializo posiciones random y numeros random
    cantVeces=2;
    posiciones_random(cantVeces);

    //Imprimo la matriz
    prnt_matriz();

    do{
        puntMax=puntaje_maximo();
        movimiento_usuario();
        //printf("%s\n",movimiento);
        if (0 == strcmp(movimiento,"w")){
       //printf("\nentro");
        movimiento_W();
        suma_W();
        movimiento_W();
        cantVeces=1;
        if(modifico){
            posiciones_random(cantVeces);
            modifico=false;
        }
        prnt_matriz();
    }
    }while(puntMax<2048&&cantEspacio>0);
}


void msg_bienvenida(){
    ///Mensaje de bienvenida
    printf("Bienvenido a 2048!!\n");
    printf("Para poder jugar usa los comandos: (A)Izquierda, (D)Derecha, (W)Arriba, (S)Abajo\n");
    printf("\n");
}

/// Inicializo la matriz
void init_tablero(){
    int posX,posY;

    for(posX=0;posX<4;posX++){
        for(posY=0;posY<4;posY++)
            tablero[posX][posY]=0;//Preguntar profe como inicializarlo vacio
    }
}

/// Imprimo matriz en pantalla
void prnt_matriz(){
    int posX,posY;

    ///Imprimo el tablero
    for(posY=0;posY<4;posY++){
        for(posX=0;posX<4;posX++)
            printf(" | %4d",tablero[posX][posY]);

        printf("|\n");
    }
}

//Genera una posicion random y un numero random para colocar
void posiciones_random(int cantVeces){
    int cont=0,sigNum,posXR,posYR;
    srand(time(NULL));

    while(cont<cantVeces){
        //Variables random para la poscion en la cual insertar el valor
        posXR=rand()%4;
        posYR=rand()%4;

        //Sorteo del valor entre 2 o 4 a insertar
        sigNum=rand()%2;
        if(sigNum==0){
            sigNum=2;
        }else{
            sigNum=4;
        }

        //Se Guarda en la matriz el valor sorteado, en la posicion random
        if(tablero[posXR][posYR]==0){
            tablero[posXR][posYR]=sigNum;
            cont++;
            cantEspacio--;
        }
    }
}

//Pido al usuario ingresar el movimiento
void movimiento_usuario(){
    char letra;
    int cont;

    printf("Ingrese movimiento: ");
    cont=0;

    do{
        letra=getchar();
        movimiento[cont]=letra;
        cont++;
    }while (letra!='\n' && cont<tamano);

    while (letra!='\n'){
        movimiento[cont-1]='\0';
        letra=getchar();
    }

    movimiento[cont-1]='\0';
}

void movimiento_W(){
    int num;
    int posX, posY, posYF;
    for(posX=0; posX<4; posX++){
        for(posY=1; posY<4; posY++){
            if(tablero[posX][posY]!=0){
                num = tablero[posX][posY];
                posYF=posY;
                ///Evaluo si hacia arriba hay un espacio o un numero

                while((posYF-1)>=0 && tablero[posX][posYF-1] == 0){
                    tablero[posX][posYF]=0;
                    posYF--;

                }
                tablero[posX][posYF]=num;
                modifico=true;
            }
        }
    }

}

void suma_W(){
    int valor, valorF;
    int posX, posY;

    for(posX=0; posX<4; posX++){
        for(posY=1; posY<4; posY++){

            valor = tablero[posX][posY];
            valorF = tablero[posX][posY-1];

            if(valor!=0 && valor == valorF){
                tablero[posX][posY-1]=valorF*2;
                tablero[posX][posY]=0;
                modifico=true;
                cantEspacio++;
            }
        }
    }
}


int puntaje_maximo(){
    char letra;
    int cont;

    printf("Ingrese movimiento: ");
    cont=0;

    do{
        letra=getchar();
        movimiento[cont]=letra;
        cont++;
    }while (letra!='\n'&&cont<tamano);

    while (letra!='\n'){
        movimiento[cont-1]='\0';
        letra=getchar();
    }

    movimiento[cont]='\0';
}