#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int tablero[4][4];
char movimiento[10];//Arreglo para saber el movimiento del usuario
#define tamano 10 //Tama�o del bufeer de lo que lee el usuarui
int cantEspacio=16;//Espacios libres en el tablero
bool modifico=false;//Booleano que sirve para saber si se modifico una celda
//bool hayMovimiento=false;//Se llena el tablero pero todavia hay posibilidad de hacer un movimiento

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

/// Funcion para mover todos los valores hacia arriba
void movimiento_W();

///Funcion para mover todos los valores hacia abajo
void movimiento_S();

///Funcion para mover todos los valores hacia la izquierda
void movimiento_A();

///Funcion para mover todos los valores hacia la derecha
void movimiento_D();

///Funcion que sume en caso de tener dos casillas del mismo valor
void suma_W();

///Suma de valores hacia abajo
void suma_S();

///Suma de valores hacia la izquierda
void suma_A();

///Suma de valores hacia la derecha
void suma_D();

///Arreclo que recorre el tablero y devuelve la casilla con mayor valor
int puntaje_maximo();


bool hay_mov_disponible();

int main(){
    int cantVeces,puntMax,hayMov;
    bool puedoJugar=true;

    // Mensaje bienvenida
    msg_bienvenida();

    //Inicializacion tablero
    init_tablero();

    ///Inicializo posiciones random y numeros random
    cantVeces=2;
    posiciones_random(cantVeces);

    //Imprimo la matriz
    prnt_matriz();


    puntMax=puntaje_maximo();
    
    while(cantEspacio>=0&&puntMax<2048){

        //Test
        /*if(puedoJugar==true){        
            printf("Cantidad de espacios:%d, puntaje maximo:%d\n",cantEspacio,puntMax);
        }else{
            printf("puntaje maximo:%d, Cantidad de espacios:%d\n",puntMax,cantEspacio);
        }*/

        movimiento_usuario();

        //MOVIMINETO HACIA ARRIBA
        if (0 == strcmp(movimiento,"w")){
            movimiento_W();
            suma_W();
            movimiento_W();
            cantVeces=1;
            if(modifico){
                posiciones_random(cantVeces);
                modifico=false;
            }

        //MOVIMIENTO HACIA ABAJO
        }else if (0 == strcmp(movimiento,"s")){
            movimiento_S();
            suma_S();
            movimiento_S();
            cantVeces=1;
            if(modifico){
                posiciones_random(cantVeces);
                modifico=false;
            }

        //MOVIMIENTO HACIA LA IZQUIERDA
        }else if (0 == strcmp(movimiento,"a")){
            movimiento_A();
            suma_A();
            movimiento_A();
            cantVeces=1; ///por qu� afuera del if? (no me queda del todo claro pero funciona)
            if(modifico){
                posiciones_random(cantVeces);
                modifico=false;
            }

        //MOVIMIENTO HACIA LA DERECHA
        }else if(0 == strcmp(movimiento,"d")){
            movimiento_D();
            suma_D();
            movimiento_D();
            cantVeces=1;
            if(modifico){
                posiciones_random(cantVeces);
                modifico=false;
            }
        //En caso de no ingresar un comando valido
        }else
            printf("Entrada invalida, vuelva a intentarlo\n");

        //printf("Cantidad de espacio:%d\n",cantEspacio);
        if(cantEspacio==0){
            hayMov=hay_mov_disponible();
            /*if(hayMov==true){
                printf("Soy true\n");
                
            }*/
            if(hayMov==false){
                cantEspacio=-1;
                //printf("Hola estoy adentro de hay mov\n");
            }
        }

        //Una vez que se ejecuta el movimiento del usuario, se vuelve a imprimir matriz y se busca el valor más alto
        prnt_matriz();
        puntMax=puntaje_maximo();
    }

    //Una vex que termina partida mostrarle al usuario si gano o perdio
    if(puntMax>=2048){
        printf("“Ganaste, lograste un puntaje de 2048”\n");
    } else{
        printf("Perdiste, lograste un puntaje de %d\n",puntMax);
    }

    return 0;
}

/// Inicializacion de la partida
void msg_bienvenida(){
    ///Mensaje de bienvenida
    printf("Bienvenido a 2048!!\n");
    printf("\n");
}

void init_tablero(){
    int posX,posY;

    for(posY=0;posY<4;posY++){
        for(posX=0;posX<4;posX++)
            tablero[posX][posY]=0;
            tablero[2][2]=1024;
            tablero[2][1]=1024;
    }
}

void prnt_matriz(){
    int posX,posY;

    ///Imprimo el tablero
    for(posY=0;posY<4;posY++){
        for(posX=0;posX<4;posX++)
            printf(" | %4d",tablero[posX][posY]);

        printf("|\n");
    }
}

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

/// Input para el usuario
void movimiento_usuario(){
    char letra;
    int cont;

    printf("Nuevo movimiento, Subir(W), Bajar(S), Izquierda(A), Derecha(D):\n");
    printf("\n");
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

/// Funciones de las aciones dependiendo del comando que ingrese el usuario
void movimiento_W(){
    int num;
    int posX, posY, posYF;
    for(posY=1; posY<4; posY++){
        for(posX=0; posX<4; posX++){
            if(tablero[posX][posY]!=0){
                num = tablero[posX][posY];
                posYF=posY;
                ///Evaluo si hacia arriba hay un espacio o un numero

                while((posYF-1)>=0 && tablero[posX][posYF-1] == 0){
                    tablero[posX][posYF]=0;
                    posYF--;
                    modifico=true;
                }
                tablero[posX][posYF]=num;

            }
        }
    }
}

void suma_W(){
    int valor, valorF;
    int posX, posY;

    for(posY=1; posY<4; posY++){
        for(posX=0; posX<4; posX++){

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

void movimiento_S(){
    int num;
    int posX, posY, posYF;
    for(posY=2; posY>=0; posY--){
        for(posX=3; posX>=0; posX--){
            if(tablero[posX][posY]!=0){
                num = tablero[posX][posY];
                posYF=posY;
                ///Evaluo si hacia Abajo hay un espacio o un numero

                while((posYF+1)<=3 && tablero[posX][posYF+1] == 0){
                    tablero[posX][posYF]=0;
                    posYF++;
                    modifico=true;
                }
                tablero[posX][posYF]=num;
                //revisar en que momento se ejecuta IDEM para w
            }
        }
    }
}

void suma_S(){
    int valor, valorF;
    int posX, posY;

    for(posY=2; posY>=0; posY--){
        for(posX=3; posX>=0; posX--){

            valor = tablero[posX][posY];
            valorF = tablero[posX][posY+1];

            if(valor!=0 && valor == valorF){
                tablero[posX][posY+1]=valorF*2;
                tablero[posX][posY]=0;
                modifico=true;//Revisar en que momento se ejecuta IDEM para w
                cantEspacio++;
            }
        }
    }
}

void movimiento_A(){
    int num;
    int posX, posY, posXF;
    for(posY=0; posY<4; posY++){
        for(posX=1; posX<4; posX++){
            if(tablero[posX][posY]!=0){
                num = tablero[posX][posY];
                posXF=posX;

                while(posXF-1>=0 && tablero[posXF-1][posY] == 0){
                    tablero[posXF][posY]=0;
                    posXF--;
                    modifico=true;
                }

                tablero[posXF][posY]=num;
            }
        }
    }
}

void suma_A(){
    int valor, valorF;
    int posX, posY;
    for(posY=0; posY<4; posY++){
        for(posX=1; posX<4; posX++){

            valor = tablero[posX][posY];
            valorF = tablero[posX-1][posY];

            if(valor!=0 && valor == valorF){
                tablero[posX-1][posY]=valorF*2;
                tablero[posX][posY]=0;
                modifico=true;
                cantEspacio++;
            }
        }
    }
}

void movimiento_D(){
    int num;
    int posX, posXF, posY;
    for(posY=3; posY>=0; posY--){
        for(posX=2; posX>=0; posX--){
            if(tablero[posX][posY]!=0){
                num = tablero[posX][posY];
                posXF=posX;

                while((posXF+1)<=3 && tablero[posXF+1][posY] == 0){
                    tablero[posXF][posY]=0;
                    posXF++;
                    modifico=true;

                }
                tablero[posXF][posY]=num;
            }
        }
    }
}

void suma_D(){
    int valor, valorF;
    int posX, posY;

    for(posY=3; posY>=0; posY--){
        for(posX=2; posX>=0; posX--){
            valor = tablero[posX][posY];
            valorF = tablero[posX+1][posY];

            if(valor!=0 && valor == valorF){
                tablero[posX+1][posY]=valorF*2;
                tablero[posX][posY]=0;
                modifico=true;//Revisar en que momento se ejecuta IDEM para w
                cantEspacio++;
            }
        }
    }
}

///Se calcula el puntaje maximo que hay en el tablero
int puntaje_maximo(){
    int posX,posY,max;

    max=tablero[0][0];
    for(posY=0;posY<4;posY++){
        for(posX=0;posX<4;posX++){
            if(tablero[posX][posY]>max){
                max=tablero[posX][posY];
            }
        }
    }
    return max;
}


bool hay_mov_disponible(){
    int posX,posY,lugares=0;
    bool hayMovimiento=false;

    for(posY=0; posY<3;posY++){
        for(posX=0;posX<4;posX++){
            if(tablero[posX][posY+1]==tablero[posX][posY]){
                lugares++;
            }
        }
    }
    for(posY=0; posY<4;posY++){
        for(posX=0;posX<3;posX++){
            if(tablero[posX+1][posY]==tablero[posX][posY]){
                lugares++;
            }
        }
    }
    if(lugares!=0){
        printf("lugares %d\n",lugares);
        hayMovimiento=true;
    }
    return hayMovimiento;
}