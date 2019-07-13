#define LOADINGBAR "=========="
#define LOADINGBARWIDTH 10
#include <stdio.h>
#include <unistd.h>
int main()
{
    int percentuale = 10;
    int barra = percentuale / LOADINGBARWIDTH;
    int spazi = LOADINGBARWIDTH - barra;
    printf("%3d%% [%.*s%*s]", percentuale, barra, LOADINGBAR, spazi, "");
    printf("\n");
    system("cls");
    return (0);
}