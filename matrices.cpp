#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 int main(){

 int num;
    int posX, posY, posYF;
    for(posY=0;posY<4;posY++){
        for(posX=0;posX<4;posX++){
            printf("|x: %d, y:%d",posX,posY);
        }
        printf("|\n");
    }
    printf("\n");


    for(posY=3; posY>=0; posY--){
        for(posX=3; posX>=0; posX--){
            printf("|x: %d, y:%d",posX,posY);
        }
        printf("|\n");
    }




    return 0;
 }





 /*
 
|x: 0, y:0|x: 1, y:0|x: 2, y:0|x: 3, y:0|
|x: 0, y:1|x: 1, y:1|x: 2, y:1|x: 3, y:1|
|x: 0, y:2|x: 1, y:2|x: 2, y:2|x: 3, y:2|
|x: 0, y:3|x: 1, y:3|x: 2, y:3|x: 3, y:3|

|x: 3, y:3|x: 2, y:3|x: 1, y:3|x: 0, y:3|
|x: 3, y:2|x: 2, y:2|x: 1, y:2|x: 0, y:2|
|x: 3, y:1|x: 2, y:1|x: 1, y:1|x: 0, y:1|
|x: 3, y:0|x: 2, y:0|x: 1, y:0|x: 0, y:0|

 */