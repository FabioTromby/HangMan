#pragma clang diagnostic push
#pragma clang diagnostic pop
#pragma ide diagnostic ignored "cert-msc30-c"
#pragma ide diagnostic ignored "cert-err34-c"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define qnt 660000 // size of the struct of wordlist
#define length 25 // vector for the picked word
#define pulisci system("clear");
#define dormi1 sleep(1);


typedef struct
{
    char parola[length];
}dizionario;

dizionario ita[qnt];

int *dim_word=0;


void display_word(char right[],int guessed[]);
void pick_word(dizionario ita[],char right[]);
void get_data(dizionario ita[qnt]);
int menu();
int main()
{
    int exit=0,scelta=0;
    char right[length];
    int tentavi[5];


    while(exit==0)
    {
        printf("Benvenuto nel gioco dell'impiccato"
               " _                                             \n"
               "| |                                            \n"
               "| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __  \n"
               "| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n"
               "| | | | (_| | | | | (_| | | | | | | (_| | | | |\n"
               "|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"
               "                    __/ |                      \n"
               "                   |___/                     ");
        dormi1 // declared above under pre proccessing directories
        printf("\nPremi invio per continuare e giocare\n");
        getchar();
        pulisci

        scelta=menu();
        switch(scelta)
        {
            case 0:
                exit=1;
                break;
            case 1:
                get_data(ita);
                pick_word(ita,right); // pick a word that match the difficulty choosen by the end user
                int guessed[*dim_word]; // array that marks what character have been guessed
                guessed[0]=1;  // 1 mean that the char have been guessed
                guessed[*dim_word-1]=1;

                while(tentavi != 0)
                {


                }
                break;
            /*default:
                printf("Scelta non valida");
                break;*/
        }
    }

    return 0;
}

int menu(){
    int a=0;
    printf("Benvenuto nel gioco dell'impiccato "
           "Scegli come vuoi giocare "
           "\n0) termina il programma"
           "\n1) il programma sceglie la parola te la indovini"
           "\n2) tu scegli la parola e il programma la indovina  :)  \n");
    scanf("%d",&a);
    dormi1
    pulisci
    return (a);

}


void get_data(dizionario ita[qnt])
{
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp != NULL)
    {
        for(int a = 0 ; a < qnt ; a++ )
        {
            fscanf(fp,"%s",ita[a].parola);
            printf("Parola %s in posizione %d\n",ita[a].parola,a);
        }
        fclose(fp);
        dormi1
        pulisci
    }
    else
    {
        printf("Errore di apertura del file \n");
    }

}


void pick_word(dizionario ita[],char right[])
{
    int difficulty=3;
    int position;
    while(right != NULL) {

        srand((unsigned int) time(NULL));
            printf("Scegli il livello di difficoltà "
                   "\n0) facile "
                   "\n1) media "
                   "\n2) difficile \n");
            scanf("%d", &difficulty);

        switch (difficulty) {
            case 0:
                while (*dim_word > 3 && *dim_word < 5) {
                    position = rand() % qnt;
                    right = ita[position].parola;
                    *dim_word = (int) strlen(right);
                }
                break;
            case 1:
                while (*dim_word > 4 && *dim_word < 7) {
                    position = rand() % qnt;
                    right = ita[position].parola;
                    *dim_word = (int) strlen(right);
                }
                break;
            case 2:
                while (*dim_word > 6 && *dim_word < 12) {
                    position = rand() % qnt;
                    right = ita[position].parola;
                    *dim_word = (int) strlen(right);
                }
                break;
            default:
                break;
        }
    }
}

void display_word(char right[],int guessed[])
{
    for(int a = 0 ; a < *dim_word ; a++  )
    {

    }
}

