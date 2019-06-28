#pragma clang diagnostic push
#pragma clang diagnostic pop
#pragma ide diagnostic ignored "cert-msc30-c"
#pragma ide diagnostic ignored "cert-err34-c"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define qnt 660000            // size of the struct of wordlist
#define leng 25               // vector for the picked word
#define clean_ system("cls"); // clean the terminal
#define sleep_1 sleep(1);     // make 1 second of delay

typedef struct
{
    char word[leng];
} dictionary;

dictionary ita[qnt];

int *dim_word = 0;

void display_word(char right[], int guessed[]);
void pick_word(dictionary ita[], char right[]);
void get_data(dictionary ita[qnt]);
int menu();
int main()
{
    int exit = 0, choice = 0;
    char right[leng];
    int try_available = 5;
    int *guessed;

    while (exit == 0)
    {
        printf("\nWelcome to the hangman game \n"
               " _                                             \n"
               "| |                                            \n"
               "| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __  \n"
               "| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n"
               "| | | | (_| | | | | (_| | | | | | | (_| | | | |\n"
               "|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"
               "                    __/ |                      \n"
               "                   |___/                     \n");
        sleep_1
            printf("\nPress enter to continue  \n");
        getchar();
        clean_
            choice = menu();
        switch (choice)
        {
        case 0:
            exit = 1;
            break;
        case 1:
            get_data(ita);
            pick_word(ita, right);           // pick a word that match the difficulty choosen by user
            guessed = malloc(*dim_word * 1); // array that marks what character have been guessed
            guessed[0] = 1;                  // zero and 1 are flag for what char has been guessed
            guessed[*dim_word - 1] = 1;

            while (try_available != 0)
            {
                try_available = 0;
            }
            break;
        default:
            printf("Scelta non valida");
            break;
        }
    }
    return 0;
}

int menu()
{
    int a = 0;
    printf("\nchoose the game mode \n "
           "\n0) exit the game "
           "\n1) the game choose a word and you pick it "
           "\n2) you choose the  word and the program try to guess it   :)  \n");
    scanf("%d", &a);
    sleep_1
        clean_ return a;
}

void get_data(dictionary ita[qnt])
{
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp != NULL)
    {
        for (int a = 0; a < qnt; a++)
        {
            fscanf(fp, "%s", ita[a].word);
            printf("Word  %s in position %d\n", ita[a].word, a);
        }
        fclose(fp);
        sleep_1
            clean_
    }
    else
    {
        printf("Error opening file \n");
    }
}

void pick_word(dictionary ita[], char right[])
{
    int difficulty = 3;
    int position;
    while (right != NULL)
    {

        srand((unsigned int)time(NULL));
        printf("Select the difficulty level \n"
               "\n0) Easy "
               "\n1) Medium  "
               "\n2) Hard \n");
        scanf("%d", &difficulty);

        switch (difficulty)
        {
        case 0:
            while (*dim_word > 3 && *dim_word < 5)
            {
                position = rand() % qnt;
                right = ita[position].word;
                *dim_word = (int)strlen(right);
            }
            break;
        case 1:
            while (*dim_word > 4 && *dim_word < 7)
            {
                position = rand() % qnt;
                right = ita[position].word;
                *dim_word = (int)strlen(right);
            }
            break;
        case 2:
            while (*dim_word > 6 && *dim_word < 12)
            {
                position = rand() % qnt;
                right = ita[position].word;
                *dim_word = (int)strlen(right);
            }
            break;
        default:
            break;
        }
    }
}

void display_word(char right[], int guessed[])
{
    for (int a = 0; a < *dim_word; a++)
    {
        break;
    }
}
