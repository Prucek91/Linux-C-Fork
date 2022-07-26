// gcc main.c
// ./a.out abcde

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define ROZMIAR 150

int main(int argc, char ** argv)
{
if(argc==1) {printf("Brak parametrow!\n"); return 0;}
else if (argc==2 && (int)strlen(argv[1]) == 1)
        {
        printf("%d %s\n", (int)getpid(), argv[1]);
        return 0;
        }
else if (argc==3 && (int)strlen(argv[1]) ==1)
        {
        printf("%d %s %s\n",(int)getpid(), argv[2], argv[1]);
        return 0;
        }

char * newString = calloc(ROZMIAR, sizeof(char));
int newLength = 1;
int argLength = strlen(argv[1]);
int skrocenie = 0;
while(newLength < argLength)
        {
        newLength = newLength * 2;
        }
if(newLength != argLength){ newLength = newLength / 2;skrocenie = 1;}
strncpy(newString, argv[1], newLength);

if(skrocenie==1) { printf("Skrocono do: %s\n", newString);}
//dlugosc string'a
if(argc!=3) printf("%d %s\n", (int)getpid(), newString);
else if (argc==3) printf("%d %s %s\n", (int)getpid(), argv[2], newString);


char * str1 = calloc(ROZMIAR, sizeof(char) );
char * tstr1 = calloc(ROZMIAR, sizeof(char) );
char * str2 = calloc(ROZMIAR, sizeof(char) );
char * tstr2 = calloc(ROZMIAR, sizeof(char) );

int half = (int)strlen(newString) / 2;
for(int i = 0; i < half; i++)
        {
        tstr1[i] = newString[i];
        tstr2[i] = newString[i+half];
        }
strncpy(str1, tstr1, half);
strncpy(str2, tstr2, half);
free(tstr1);
free(tstr2);
//polowienie string'a

char * hist = calloc(ROZMIAR, sizeof(char) );
char * hist2 = calloc(ROZMIAR, sizeof(char) );

//obsluga histori

if(argc==2)
        {
        strcpy(hist, newString);
        strcpy(hist2, newString);
        }
else if(argc==3)
        {
        strcpy(hist, argv[2]);
        strcpy(hist2, argv[2]);

        strcat(hist, " ");
        strcat(hist2, " ");

        strcat(hist, newString);
        strcat(hist2, newString);
        }
strcat(hist, " ");
strcat(hist2, " ");
        //forki
pid_t child, child2;
        if(strlen(str1)>0) {
                child = fork();
                if(child==-1) {
                        perror("fork()");
                        exit(EXIT_FAILURE);
                }
                if(child==0) {
                        execl("a.out", "a.out", str1, hist, NULL);
                        perror("execl error");
                        exit(EXIT_FAILURE);
                }
         }
        //perror - nieudane zaladowanie

if(strlen(str2)>0)
         {
                child2 = fork();
           child2 = fork();
                if(child2==-1) {
                        perror("fork()");
                        exit(EXIT_FAILURE);
                }
                if(child2==0) {
                        execl("a.out", "a.out", str2, hist, NULL);
                        perror("execl error");
                        exit(EXIT_FAILURE);
                }
         }

pid_t k;
int status; int status2;
        //waitpid(-1, &status, WNOHANG);
//        waitpid(-1, &status, 0);
        wait(&status);
        if(status < 0 ) perror("Error execl()\n");
        wait(&status2);
        if(status2 < 0 ) perror("Error execl()\n");



/* forki stop */


//free(hist);
//free(hist2);
// printf("\n");
if(argc==2) getchar();



return 0;


}

