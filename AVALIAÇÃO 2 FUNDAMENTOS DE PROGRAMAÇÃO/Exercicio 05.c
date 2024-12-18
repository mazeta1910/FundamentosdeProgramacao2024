#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h> // Declaração da biblioteca <stdbool.h>
#ifdef __linux__
    #include <unistd.h>
#else
    #include <windows.h>
#endif
#define SLEEPTIME 300
#define PARTICULAS 32
#define SIZE 10 // SIZE não havia sido declarada.

int main(){ // trocado para int main(), devido ao erro: warning: return type of 'main' is not 'int' [-Wmain]
    int mat[SIZE][SIZE];
    int x,y,j;    
    int i; // declaração da variável i, que tbm não havia sido variável

    srand(time(NULL));

    for(i=0;i<SIZE;i++){ // variável i ainda havia sido inicializada, e o { tbm estava faltando
        for(j=0;j<SIZE;j++){ // { adicionado
            mat[i][j] = 0;
        } // } adicionado
    } // } adicionado
    i = 0;
    while(i<PARTICULAS){
        x = rand()%SIZE;
        y = rand()%SIZE;
        if(mat[x][y] == 0){ // = trocado para ==
            mat[x][y] = 1;
            i++;
        }
    }
    mat[x][y] = -1;
    while(true){ // linha de códig estava incorreta devido a ausência da biblioteca stdbool.h   
        i = x;
        j = y;
        x = (x+(rand()%3)-1+SIZE)%(SIZE+1);
        y = (y+(rand()%3)-1+SIZE)%(SIZE+1);
        if(mat[x][y]==0){
            mat[i][j] = 0;
            mat[x][y] = -1;
        }else{
            x = i;
            y = j;
            continue;
        }
        #ifdef __linux__
            system("clear");
        #else
            system("cls");
        #endif
        
        for(i=0;i<SIZE;i++){
            printf("|");
            for(j=0;j<SIZE;j++){
                if(mat[i][j]==0)
                    printf("   ");
                else if(mat[i][j]==1)
                    printf(" # ");
                else
                    printf(" * ");
            }
            printf("|\n");
        }
        //faz o terminal parar por um instante
        #ifdef __linux__
            sleep(SLEEPTIME/1000); // na unistd eh em segundos
            usleep(1000*(SLEEPTIME%1000)); //para fracoes de segundos usamos usleep (em microsegundos)
        #else
            Sleep(SLEEPTIME);// na windows.h eh em milisegundos, note o S maiusculo
        #endif
    }
    return 0; // return 0 adicionado para retornar a int main a 0
}