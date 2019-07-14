#pragma clang diagnostic push
#pragma clang diagnostic pop
#pragma ide diagnostic ignored "cert-msc30-c"
#pragma ide diagnostic ignored "cert-err34-c" // delete these first 4 lines if you get any trouble

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

//! things important
// todo // this explain itself
//* debug / useless stuff

#define LOADINGBAR "===================="
#define LOADINGBARWIDTH 20
#define qnt 660000            //! size of the struct of wordlist
#define leng 25               // vector for the picked word
#define clean_ system("cls"); // clean the terminal
#define sleep_1 sleep(1)      // make 1 second of delay

typedef struct
{
    char word[leng];
} dictionary;
dictionary ita[qnt];

typedef struct
{
    char c[75];
} array;
array impiccati[6];

void loadtext();
void check_input(char char_try, char word_try[], char right[], int choise, int *try_available, int *dim_word, int guessed[], int *won);
int user_input(char *char_try, char word_try[]);                                  //  get the input for playing from the user
void pick_word(dictionary ita[], char right[], int *dim_word);                    //  pick a word from the struct
void display_word(char right[], int guessed[], int *dim_word, int try_available); // display the word what the user has been guessed
void pick_word_difficulty(dictionary ita[], char right[], int *dim_word);         // choose the word to play with
void get_data(dictionary ita[qnt]);                                               // get the struct from the txt file
int menu();
int main()
{
    int exit = 0, choice = 0;
    char right[leng];
    int try_available;
    int *guessed;
    int dim_word = 0;
    char char_try, word_try[leng];

    //*word_try2 = word_try;
    int won; //! 0 undefined  1 user has won 2 user has lost

    loadtext();
    get_data(ita);
    while (exit == 0)
    {
        printf("\n\tWelcome to the hangman game \n"
               "\t _                                             \n"
               "\t| |                                            \n"
               "\t| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __  \n"
               "\t| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n"
               "\t| | | | (_| | | | | (_| | | | | | | (_| | | | |\n"
               "\t|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"
               "\t                    __/ |                      \n"
               "\t                   |___/                     \n");
        sleep_1;
        printf("\n\tPress enter to continue  \n");
        getchar();
        clean_;
        choice = menu();

        switch (choice)
        {
        case 0:
            exit = 1;
            break;
        case 1:

            pick_word(ita, right, &dim_word);                //! pick a word that match the difficulty choosen by user
            guessed = (int *)malloc(dim_word * sizeof(int)); //! array that marks what character have been guessed;
            guessed[0] = 1;                                  //! zero and 1 are flag for what char has been guessed
            for (int a = 1; a < dim_word - 1; a++)
            {
                guessed[a] = 0;
            }

            guessed[dim_word - 1] = 1;
            try_available = 5;

            while (try_available != 0)
            {
                display_word(right, guessed, &dim_word, try_available);
                int choise = user_input(&char_try, word_try);
                check_input(char_try, word_try, right, choise, &try_available, &dim_word, guessed, &won);
                if (try_available == 0 && won == 0)
                {
                    won = 2;
                }
                if (won == 1)
                {
                    printf("Congratulation you have won \n");
                    try_available = 0;
                }
                else if (won == 2)
                {
                    printf("You lost , next time will be more lucky\n");
                }
            }
            break;
        case 2:
            get_data(ita);
            break;
        default:
            printf("Choice is invalid\n");
            break;
        }
    }
    return 0;
}

int menu()
{
    int a = 0;
    printf("\n\tchoose the game mode \n "
           "\n\t0) exit the game "
           "\n\t1) the game choose a word and you pick it "
           "\n\t2) you choose the  word and the program try to guess it   :)  \n");
    scanf("%d", &a);
    sleep_1;
    clean_;
    return (a);
}
void loadtext()
{
    strcpy(impiccati[0].c, "\t+---+\n"
                           "\t  |   |\n"
                           "\t  O   |\n"
                           "\t /|\\ |\n"
                           "\t / \\ |\n"
                           "\t      |\n"
                           "\t=========");
    strcpy(impiccati[1].c, "\t +---+\n"
                           "\t  |   |\n"
                           "\t  O   |\n"
                           "\t /|\\  |\n"
                           "\t /    |\n"
                           "\t      |\n"
                           "\t=========");
    strcpy(impiccati[2].c, "\t +---+\n"
                           "\t  |   |\n"
                           "\t  O   |\n"
                           "\t /|\\  |\n"
                           "\t      |\n"
                           "\t      |\n"
                           "\t=========");
    strcpy(impiccati[3].c, "\t+---+\n"
                           "\t  |   |\n"
                           "\t  O   |\n"
                           "\t /|   |\n"
                           "\t      |\n"
                           "\t      |\n"
                           "\t=========");
    strcpy(impiccati[4].c, "\t +---+\n"
                           "\t  |   |\n"
                           "\t  O   |\n"
                           "\t  |   |\n"
                           "\t      |\n"
                           "\t      |\n"
                           "\t=========");
    strcpy(impiccati[5].c, "\t+---+\n"
                           "\t  |   |\n"
                           "\t      |\n"
                           "\t      |\n"
                           "\t      |\n"
                           "\t      |\n"
                           "\t=========");
}
void get_data(dictionary ita[qnt])
{

    FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp != NULL)
    {
        int percentualprec = -1;
        for (int a = 0; a < qnt; a++)
        {
            int percentage = ((a * 100) / qnt) + 1;
            int barra = (percentage * LOADINGBARWIDTH) / 100;
            int spazi = LOADINGBARWIDTH - barra;
            if (percentualprec != percentage)
            {
                percentualprec = percentage;
                system("cls");
                printf("LOADING: %3d%% [%.*s%*s]", percentage, barra, LOADINGBAR, spazi, "");
            }
            fscanf(fp, "%s", ita[a].word);
        }
        fclose(fp);
        sleep_1;
        clean_;
    }
    else
    {
        printf("Error opening file \n");
    }
}

void pick_word(dictionary ita[], char right[], int *dim_word)
{
    int position = 0;
    srand(time(NULL));

    position = rand() % qnt;

    strcpy(right, ita[position].word);
    printf("\nthe choosen word is  %s \n", right);

    *dim_word = strlen(right);
    printf("dim word is %d in pick word \n", *dim_word);
}

void display_word(char right[], int guessed[], int *dim_word, int try_available)
{
    printf("%s", impiccati[try_available].c);
    printf("\n\n\n\t");
    for (int a = 0; a < *dim_word; a++)
    {
        if (guessed[a] == 1)
        {
            printf("%c", right[a]);
        }
        else if (guessed[a] == 0)
        {
            printf("_");
        }
    }
    printf("\n\n");
    if (try_available != 0)
    {
        printf("you have %d try left\n", try_available);
    }
    else if (try_available == 0)
    {
        printf("you have lost \n ");
        printf("the correct word was \n ", right);
    }
}

// todo / fix the diffuculty system
void pick_word_difficulty(dictionary ita[], char right[], int *dim_word)
{
    int difficulty = 3;
    int position;
    *dim_word = 0;
    while (right != NULL)
    {
        printf("\n\n\tGuide to difficulty\n"
               "\n\tEasy are word from 3 to 5 character \n"
               "\n\tMedium are word from 4 to 7 character\n"
               "\n\tHard are word from 6 to 12 character\n");
        srand((unsigned int)time(NULL));
        printf("\tSelect the difficulty level \n"
               "\n\t0) Easy "
               "\n\t1) Medium  "
               "\n\t2) Hard \n");
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
        printf("\n\tthe choosen word is  %s \n", right);
    }
}

int user_input(char *char_try, char word_try[])
{
    //char_try = 0;
    //word_try = NULL;
    int input = 2;
    do
    {
        printf("!make a choice "
               "\n0) try to guess if a char is in the word"
               "\n1) try to guess the entire word\n ");
        scanf("%d", &input);
        fflush(stdin);
        switch (input)
        {
        case 0:
            printf("write down a char you think is in the word\n");
            scanf("%c", char_try);
            break;
        case 1:
            printf("write down what do you think is the correct word \n");
            //fflush(stdin);
            scanf("%s", word_try);
            break;
        default:
            printf("you can only choose 0 or 1 ");
            break;
        }
    } while (input != 0 && input != 1);
    return input;
}

void check_input(char char_try, char word_try[], char right[], int choise, int *try_available, int *dim_word, int guessed[], int *won)
{
    int flag = 0;
    int count = 0;
    switch (choise)
    {
    case 0:
        for (int a = 0; a < *dim_word; a++)
        {
            if (char_try == right[a])
            {
                count++;
                flag = 1;
                guessed[a] = 1;
            }
        }
        if (flag == 0)
        {
            printf("char %c not found in word \n", char_try);
            (*try_available)--;
        }
        else
        {
            printf("%d char has been guessed\n", count);
            int num = 0;
            for (int a = 0; a < *dim_word; a++)
            {
                num += guessed[a];
            }
            if (num == *dim_word)
                *won = 1;
        }
        break;
    case 1:
        if (strcmp(word_try, right) == 0)
        {
            printf("Congratulation you have guessed the word\n");
            *won = 1;
        }
        else
        {
            printf("the word you have entered is incorrect\n");
            (*try_available)--;
        }
        break;
    default:
        break;
    }
}