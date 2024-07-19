#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int matriz[3][3];
int fd[2];
int result1,result2;

void filho1()
{
    close(fd[0]);
    printf("\nFilho1: calculando\n");
    result1 =   matriz[0][0] * matriz[1][1] * matriz[2][2] +
                matriz[0][1] * matriz[1][2] * matriz[2][0] +
                matriz[0][2] * matriz[1][0] * matriz[2][1];
    printf("Filho1: resultado: %d\n",result1);
    write(fd[1], &result1, sizeof(result1));
    close(fd[1]);
    exit(0);
}

void filho2()
{
    close(fd[0]);
    printf("\nFilho2: calculando\n");
    result2 =  (matriz[0][2] * matriz[1][1] * matriz[2][0] +
        	matriz[0][0] * matriz[1][2] * matriz[2][1] +
                matriz[0][1] * matriz[1][0] * matriz[2][2]) * -1;
    printf("Filho2: resultado: %d\n",result2);
    write(fd[1], &result2, sizeof(result2));
    close(fd[1]);
    exit(0);
}

int main(int argc, char *argv[])
{
    FILE *file = fopen("matriz.txt", "r");
    char line[20];
    fgets(line, sizeof(line), file);
    char *token = strtok(line, " ");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matriz[i][j] = atoi(token);
            token = strtok(NULL, " ");
        }
    }
    fclose(file);

    printf("Matriz: ");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n\t");
    }

    pipe(fd);
    pid_t filho1_pid, filho2_pid;

    if ((filho1_pid = fork()) == 0)
    {
        filho1();
    }
    else if ((filho2_pid = fork()) == 0)
    {
        filho2();
    }
    else
    {

        close(fd[1]);

	waitpid(filho1_pid, NULL, 0);
      	read(fd[0], &result1, sizeof(result1));
	
	waitpid(filho2_pid, NULL, 0);
        read(fd[0], &result2, sizeof(result2));

        close(fd[0]);

        int determinante = result1 + result2;
        printf("\nO determinante da matriz: %d\n", determinante);

    }
    return 0;
}
