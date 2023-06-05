#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/// Mensaje bienvenida
void msg_bienvenida();

///Inicializacion tablero
void init_tablero(int matriz[][4]);

///Imprimo la matriz
void prnt_matriz(int matriz[][4]);

void msg_bienvenida(){
    ///Mensaje de bienvenida
    printf("Bienvenido a 2048!!\n");
    printf("Para poder jugar usa los comandos: (A)Izquierda, (D)Derecha, (W)Arriba, (S)Abajo\n");
    printf("\n");
}

/// Inicializo la matriz
void init_tablero(int matriz[][4]){
    int posX,posY;

    for(posX=0;posX<4;posX++){
        for(posY=0;posY<4;posY++)
            matriz[posX][posY]=0;//Preguntar profe como inicializarlo vacio
    }
}

/// Imprimo matriz en pantalla
void prnt_matriz(int matriz[][4]){
    int posX,posY;

    ///Imprimo el tablero
    for(posX=0;posX<4;posX++){
        for(posY=0;posY<4;posY++)
            printf(" | %4d",matriz[posX][posY]);

        printf("|\n");
    }
}

int main(){
    srand(time(NULL));
    int matriz[4][4];
    int posX,posY,posXR,posYR,cont=0,cantVeces=2,sigNum,valor,valor2;
    char mov,buffer[10];

    msg_bienvenida();
    //init_tablero();
    //prnt_matriz();

    for(posX=0;posX<4;posX++){
        for(posY=0;posY<4;posY++)
            matriz[posX][posY]=0;//Preguntar profe como inicializarlo vacio
    }

    ///Genero valores random para la posicion y para insertar un 2 o 4
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
        if(matriz[posXR][posYR]==0){
            matriz[posXR][posYR]=sigNum;
            cont++;
            printf("%d",sigNum);
        }
    }

    ///Imprimo la matriz
    for(posX=0;posX<4;posX++){
        for(posY=0;posY<4;posY++)
            printf(" | %d",matriz[posX][posY]);//Preguntar profe como imprimir 4 espacion en cada celda

        printf("|\n");
    }


    ///Comparo los valores de las celdas, para mover o sumar
    //Hacia arriba

    
    for(posX=0;posX<4;posX++){
        for(posY=0;posY<4;posY++){
            valor=matriz[posX][posY];
            valor2=matriz[posX][posY+1];//Comparaciones con booleans, en el while del loop

           /* if(valor2==0){
                matriz[posX][posY]=0;
                matriz[posX][posY+1];
            }*/

            //si la posicion a mover tiene el mismo valor
            if(valor!=0&&valor2==valor){
                matriz[posX][posY]=valor*2;
                matriz[posX][posY+1]=0;
            }
        }
    }



char letra;
char arreglo[10];
int taman;
    //Interaccion con el usuario
    printf("Ingrese movimiento");//Usar leer_linera() del ejercicio 45 e imagen del cel!!
    cont=0;

    do{
        letra=getchar();
        arreglo[cont]=letra;
        cont++;
    }while (letra!='\n'&&cont<taman);

    while (letra!='\n'){
        arreglo[cont-1]='\0';
        letra=getchar();
    }

    arreglo[cont]='\0';














    while(mov!='\n'){
        mov=getchar();
        buffer[cont]=mov;
        cont++;
    }
/*
    for(pos=0; pos<5;pos+=1){
        letras[pos]=getchar();
    }
*/
    printf("%d",buffer);

}