
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    //FUNZIONA
    FILE *fPtr = fopen("utenti.csv", "r");
    char *token;
    char *line;

    fscanf(fPtr, "%s", line);

    token = strtok(line, ",");
    printf("Linea: %s\n\nToken: %s\n", line, token);

    while( token = strtok(NULL, ",")){
        printf("Token: %s\n", token);
    }
}

